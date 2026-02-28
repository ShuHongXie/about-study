import type { AddressInfo } from 'node:net'
import { resolve, relative, normalize } from 'pathe'
import chokidar from 'chokidar'
import { debounce } from 'perfect-debounce'
import type { Nuxt } from '@nuxt/schema'
import consola from 'consola'
import { withTrailingSlash } from 'ufo'
import { setupDotenv } from 'c12'
import { showBanner } from '../utils/banner'
import { writeTypes } from '../utils/prepare'
import { loadKit } from '../utils/kit'
import { importModule } from '../utils/cjs'
import { overrideEnv } from '../utils/env'
import { writeNuxtManifest, loadNuxtManifest, cleanupNuxtDirs } from '../utils/nuxt'
import { defineNuxtCommand } from './index'

export default defineNuxtCommand({
  meta: {
    name: 'dev',
    usage: 'npx nuxi dev [rootDir] [--clipboard] [--open, -o] [--port, -p] [--host, -h] [--https] [--ssl-cert] [--ssl-key]',
    description: 'Run nuxt development server'
  },
  async invoke (args) {
    overrideEnv('development')

    const { listen } = await import('listhen')
    let currentHandler
    let loadingMessage = 'Nuxt is starting...'
    const loadingHandler = async (_req, res) => {
      const { loading: loadingTemplate } = await importModule('@nuxt/ui-templates')
      res.setHeader('Content-Type', 'text/html; charset=UTF-8')
      res.statusCode = 503 // Service Unavailable
      res.end(loadingTemplate({ loading: loadingMessage }))
    }
    const  (req, res) => {
      return currentHandler ? currentHandler(req, res) : loadingHandler(req, res)
    }

    const rootDir = resolve(args._[0] || '.')
    // 全局变量设置
    await setupDotenv({ cwd: rootDir })
    // 初始化监听器类似于http.createServer
    const listener = await listen(serverHandler, {
      showURL: false,
      clipboard: args.clipboard,
      open: args.open || args.o,
      port: args.port || args.p || process.env.NUXT_PORT,
      hostname: args.host || args.h || process.env.NUXT_HOST,
      https: Boolean(args.https),
      certificate: (args['ssl-cert'] && args['ssl-key']) && {
        cert: args['ssl-cert'],
        key: args['ssl-key']
      }
    })

    const { loadNuxt, buildNuxt } = await loadKit(rootDir)

    let currentNuxt: Nuxt
    // 在cli上显示baseURL消息
    const showURL = () => {
      listener.showURL({
        // TODO: Normalize URL with trailing slash within schema
        baseURL: withTrailingSlash(currentNuxt?.options.app.baseURL) || '/'
      })
    }

    // 初始化加载函数 isRestart：是否重新刷新后的标识 reason: 刷新的原因
    // consola是一个优雅的日志打印工具 提供报错路径历史回溯功能
    const load = async (isRestart: boolean, reason?: string) => {
      try {
        loadingMessage = `${reason ? reason + '. ' : ''}${isRestart ? 'Restarting' : 'Starting'} nuxt...`
        currentHandler = null
        // 如果是刷新过的 那么就在cli上显示刷新原因
        if (isRestart) {
          consola.info(loadingMessage)
        }
        // 如果当前nuxt实例已经存在，那么就关闭当前实例
        if (currentNuxt) {
          await currentNuxt.close()
        }
        // 函数地址 packages/nuxt/src/core/nuxt.ts
        currentNuxt = await loadNuxt({ rootDir, dev: true, ready: false })
        // 第一次显示初始化的根目录地址
        if (!isRestart) {
          showURL()
        }

        // Write manifest and also check if we need cache invalidation
        if (!isRestart) {
          // 加载.nuxt/nuxt.json文件
          const previousManifest = await loadNuxtManifest(currentNuxt.options.buildDir)
          // 新写入一个.nuxt/nuxt.json
          const newManifest = await writeNuxtManifest(currentNuxt)
          // 如果两个json存在并且hash不相同的话 就删除文件夹
          // 判断hash是否相同的关键在于配置的根目录地址和nuxt版本号是否相同，有一个变动，其他都要变动
          if (previousManifest && newManifest && previousManifest._hash !== newManifest._hash) {
            /*
            删除
            '.nuxt',
            '.output',
            'dist',
            'node_modules/.vite',
            'node_modules/.cache'
            */
            await cleanupNuxtDirs(currentNuxt.options.rootDir)
          }
        }

        await currentNuxt.ready()

        await currentNuxt.hooks.callHook('listen', listener.server, listener)
        const address = listener.server.address() as AddressInfo
        currentNuxt.options.server.port = address.port
        currentNuxt.options.server.host = address.address

        await Promise.all([
          writeTypes(currentNuxt).catch(console.error),
          buildNuxt(currentNuxt)
        ])
        currentHandler = currentNuxt.server.app
        if (isRestart && args.clear !== false) {
          showBanner()
          showURL()
        }
      } catch (err) {
        consola.error(`Cannot ${isRestart ? 'restart' : 'start'} nuxt: `, err)
        currentHandler = null
        loadingMessage = 'Error while loading nuxt. Please check console and fix errors.'
      }
    }

    // Watch for config changes
    // TODO: Watcher service, modules, and requireTree
    // 对load方法进行函数防抖
    const dLoad = debounce(load)
    // chokidar文件监听器 类似fs.watch  depth: 限值遍历的子目录等级
    const watcher = chokidar.watch([rootDir], { ignoreInitial: true, depth: 1 })
    watcher.on('all', (event, _file) => {
      // 如果有当前没有Nuxt实例 就直接返回空
      if (!currentNuxt) { return }
      const file = normalize(_file)
      const buildDir = withTrailingSlash(normalize(currentNuxt.options.buildDir))
      // 如果是当前build的文件夹发生改变，则不进行监听改动
      if (file.startsWith(buildDir)) { return }
      const relativePath = relative(rootDir, file)
      // 匹配配相关配置文件夹，如果相关配置文件夹改动了的话 那么就更新
      if (file.match(/(nuxt\.config\.(js|ts|mjs|cjs)|\.nuxtignore|\.env|\.nuxtrc)$/)) {
        dLoad(true, `${relativePath} updated`)
      }
      // 增加/删除文件夹的事件
      const isDirChange = ['addDir', 'unlinkDir'].includes(event)
      // 增加/删除文件的事件
      const isFileChange = ['add', 'unlink'].includes(event)
      // 塞入currentNuxt.options.dir.pages, 'components', 'composables'中的所有文件
      const reloadDirs = [currentNuxt.options.dir.pages, 'components', 'composables']
        .map(d => resolve(currentNuxt.options.srcDir, d))
      // 文件或文件夹的增删操作 只要匹配到了 就进行提示
      if (isDirChange) {
        if (reloadDirs.includes(file)) {
          dLoad(true, `Directory \`${relativePath}/\` ${event === 'addDir' ? 'created' : 'removed'}`)
        }
      } else if (isFileChange) {
        if (file.match(/(app|error|app\.config)\.(js|ts|mjs|jsx|tsx|vue)$/)) {
          dLoad(true, `\`${relativePath}\` ${event === 'add' ? 'created' : 'removed'}`)
        }
      }
    })

    await load(false)

    return 'wait' as const
  }
})
