# Vite全链路优化指南（开发+构建+运行时）

Vite 的优化可分为「开发阶段优化」（启动/热更新速度）、「构建阶段优化」（产物体积/加载性能）、「运行时优化」（代码执行/资源加载）三大维度，覆盖项目全生命周期。本指南整理了除 `manualChunk` 之外的核心优化方法，包含可直接落地的配置示例、效果说明及避坑要点，助力提升Vite项目性能。

# 一、开发阶段优化（提升启动/热更新速度）

开发阶段核心痛点是「启动慢、热更新卡顿」，优化目标是减少Vite处理文件、依赖的耗时，提升开发体验。

## 1. 优化依赖预构建（optimizeDeps）

Vite启动时会对 `node_modules` 中的依赖做预构建（转为ESM格式），通过配置 `optimizeDeps` 可减少预构建耗时，避免重复构建。

```javascript
// vite.config.js
export default defineConfig({
  optimizeDeps: {
    // 1. 强制预构建指定依赖（解决部分依赖未被自动检测的问题）
    include: ['vue', 'vue-router', 'axios'],
    // 2. 排除不需要预构建的依赖（如纯ESM依赖、CDN引入的依赖）
    exclude: ['lodash-es'], // lodash-es本身是ESM，无需预构建
    // 3. 自定义预构建入口（解决monorepo/复杂项目依赖检测不全）
    entries: ['src/main.js'],
    // 4. 缓存预构建结果（默认开启，指定缓存目录，避免重复构建）
    cacheDir: '.vite/deps' 
  },
  // 5. 减少文件系统检查开销
  server: {
    fs: {
      strict: false, // 关闭严格的文件系统检查（开发环境可临时关闭）
      allow: ['../src'] // 允许Vite访问的目录，缩小检查范围
    },
    watch: {
      ignored: ['**/node_modules/**', '**/dist/**'] // 忽略无需监听的目录
    }
  }
});
```

**优化效果**：减少预构建的依赖数量，避免重复构建，启动速度提升30%~50%。

## 2. 禁用不必要的插件

开发阶段无需启用「构建专属插件」（如压缩、CDN、图片优化插件），仅保留核心插件（如Vue插件、ESLint插件），减少插件初始化耗时。

```javascript
// vite.config.js
import { defineConfig, loadEnv } from 'vite';

export default defineConfig(({ mode }) => {
  const env = loadEnv(mode, process.cwd());
  return {
    plugins: [
      // 仅生产环境启用压缩插件
      mode === 'production' ? compression() : null,
      // 仅生产环境启用图片压缩
      mode === 'production' ? imagemin() : null
    ].filter(Boolean) // 过滤null插件，避免报错
  };
});
```

**优化效果**：减少插件初始化耗时，热更新响应速度显著提升。

## 3. 调整ESBuild配置（编译提速）

Vite使用ESBuild处理JS/TS编译、语法降级，通过配置可减少编译开销，提升开发阶段编译速度。

```javascript
export default defineConfig(({ mode }) => {
  return {
    esbuild: {
      // 1. 开发环境禁用语法降级（仅生产环境降级，减少编译耗时）
      target: mode === 'production' ? 'es2015' : 'esnext',
      // 2. 忽略TS类型检查（交给IDE/单独的tsc命令，加速编译）
      tsconfigRaw: {
        compilerOptions: {
          skipLibCheck: true,
          noEmit: true
        }
      }
    }
  };
});
```

**优化效果**：开发环境跳过类型检查、语法降级步骤，编译速度大幅提升。

# 二、构建阶段优化（减小产物体积/提升加载性能）

构建阶段核心目标是「减小产物体积、降低资源传输耗时」，以下是性价比最高的优化项，可直接落地使用。

## 1. 基础构建配置优化

通过调整Vite构建核心配置，实现代码压缩、sourcemap控制，减少无用代码，优化产物体积。

```javascript
export default defineConfig(({ mode }) => {
  return {
    build: {
      // 1. 代码压缩（生产环境默认开启，自定义配置提升压缩率）
      minify: 'terser', // 替代默认的esbuild（压缩率更高，支持删除console）
      terserOptions: {
        compress: {
          drop_console: true, // 删除所有console语句
          drop_debugger: true, // 删除debugger语句
          pure_funcs: ['console.log'] // 清除指定函数调用（如单独保留console.warn）
        }
      },
      // 2. CSS压缩（默认开启，指定压缩器提升压缩率）
      cssMinify: 'csso', // 比默认的esbuild压缩率更高
      // 3. 控制sourcemap（生产环境关闭或用hidden模式，避免暴露源码）
      sourcemap: mode === 'production' ? false : 'inline',
      // 4. 调整chunk体积警告阈值（避免不必要的警告，根据项目调整）
      chunkSizeWarningLimit: 1000, // 阈值从500KB调整为1000KB
      // 5. 禁用brotli压缩（如需单独配置，用插件更灵活）
      brotliSize: false,
      // 6. 启用按需加载polyfill（仅对需要的浏览器注入，减少冗余）
      target: ['es2015', 'chrome64', 'safari11']
    }
  };
});
```

**优化效果**：产物体积减少10%~30%，清除无用代码（console/debugger），避免源码暴露。

## 2. 静态资源优化

### （1）内联小资源，减少请求数

将小体积静态资源（图片、字体）内联为base64，减少HTTP请求数，注意控制阈值避免增加JS/CSS体积。

```javascript
export default defineConfig({
  build: {
    assetsInlineLimit: 4 * 1024, // 4KB以下的资源（图片/字体）内联为base64
  }
});
```

**注意**：阈值建议设置为2~8KB，过大的base64会增加JS/CSS体积，反而降低加载速度。

### （2）图片压缩（vite-plugin-imagemin）

通过插件压缩图片资源，减少图片体积，是静态资源优化的核心手段。

安装插件：

```bash
npm i vite-plugin-imagemin -D
```

配置示例：

```javascript
import imagemin from 'vite-plugin-imagemin';

export default defineConfig({
  plugins: [
    imagemin({
      gifsicle: { optimizationLevel: 3 }, // gif压缩（优化等级1-3，越高压缩率越高）
      optipng: { optimizationLevel: 7 }, // png压缩（优化等级0-7）
      mozjpeg: { quality: 80 }, // jpg压缩（质量70-90，越高越清晰）
      webp: { quality: 80 } // 转为webp格式（体积减少50%+，需浏览器支持）
    })
  ]
});
```

**优化效果**：图片体积减少30%~70%，大幅降低静态资源加载耗时。

### （3）字体/图标优化

- 字体：将小字体文件内联（通过`assetsInlineLimit`），大字体文件添加 `font-display: swap`，避免页面加载时字体闪烁。

- 图标：使用SVG图标（`vite-plugin-svg-icons`）替代字体图标，实现按需加载，减少无用图标体积。

## 3. 开启Gzip/Brotli压缩（vite-plugin-compression）

压缩产物体积（JS/CSS/HTML），浏览器下载后自动解压，减少网络传输耗时，需配合服务器配置生效。

安装插件：

```bash
npm i vite-plugin-compression -D
```

配置示例：

```javascript
import compression from 'vite-plugin-compression';

export default defineConfig({
  plugins: [
    // 开启gzip压缩（兼容性好，推荐优先启用）
    compression({
      algorithm: 'gzip',
      threshold: 10 * 1024, // 10KB以上的文件才压缩（小文件压缩收益低）
      deleteOriginFile: false // 不删除原文件（兼容不支持gzip的浏览器）
    }),
    // 可选：开启brotli压缩（压缩率更高，需服务器支持）
    compression({
      algorithm: 'brotliCompress',
      ext: '.br',
      threshold: 10 * 1024
    })
  ]
});
```

**注意**：需在Nginx/Apache服务器配置「返回压缩文件」，否则无法生效；建议优先启用gzip，brotli作为补充。

**优化效果**：JS/CSS文件体积减少60%~80%，网络传输耗时大幅降低。

## 4. 外部化依赖（CDN引入，减小打包体积）

将大体积依赖（如vue、echarts、element-plus）通过CDN引入，不打包到产物中，减少产物体积，同时利用CDN加速加载。

```javascript
// vite.config.js
import { defineConfig } from 'vite';
import { createHtmlPlugin } from 'vite-plugin-html'; // 用于注入CDN链接

export default defineConfig({
  // 1. 标记为外部依赖，不打包到产物中
  build: {
    rollupOptions: {
      external: ['vue', 'echarts'] // 不打包vue、echarts
    }
  },
  // 2. 在HTML中注入CDN链接（确保版本与项目依赖一致）
  plugins: [
    createHtmlPlugin({
      inject: {
        data: {
          cdn: {
            js: [
              'https://cdn.jsdelivr.net/npm/vue@3.4.0/dist/vue.global.prod.js',
              'https://cdn.jsdelivr.net/npm/echarts@5.4.0/dist/echarts.min.js'
            ]
          }
        }
      },
      minify: true // 压缩HTML文件
    })
  ]
});
```

**注意**：CDN版本需与项目依赖版本完全一致，避免兼容性问题；仅对「非核心依赖/大体积依赖」使用，核心依赖（如vue）需确保CDN稳定性。

## 5. 开启Tree-Shaking（清除无用代码）

Vite基于Rollup实现Tree-Shaking，生产环境默认开启，可通过显式配置确保生效，清除未使用的组件、函数、依赖。

```javascript
export default defineConfig({
  build: {
    rollupOptions: {
      output: {
        manualChunks, // 配合自定义chunk拆分，提升Tree-Shaking效果
        preserveModules: false // 生产环境关闭，确保代码被合并优化
      }
    },
    // 强制开启Tree-Shaking，确保无用代码被清除
    terserOptions: {
      module: true
    }
  }
});
```

**优化效果**：清除未使用的组件/函数/依赖，产物体积减少10%~20%。

# 三、运行时优化（提升页面加载/执行速度）

运行时优化聚焦于「页面加载速度、代码执行效率」，核心是“错峰加载资源、减少冗余代码”，提升用户体验。

## 1. 路由懒加载（配合manualChunk）

这是最核心的运行时优化，确保首屏只加载必需的路由代码，非首屏路由按需加载，大幅减少首屏体积。

```javascript
// router/index.js
const routes = [
  {
    path: '/',
    component: () => import('@/views/home/index.vue') // 首屏加载，核心路由
  },
  {
    path: '/report',
    // 懒加载 + 自定义chunk名称（配合manualChunk，优化chunk拆分）
    component: () => import(/* webpackChunkName: "chunk-report" */ '@/views/report/index.vue')
  },
  {
    path: '/user',
    component: () => import(/* webpackChunkName: "chunk-user" */ '@/views/user/index.vue')
  }
];
```

**优化效果**：首屏JS体积减少50%+，首屏渲染速度显著提升，非首屏路由点击时才加载对应代码。

## 2. 预加载/预取（Preload/Prefetch）

Vite自动为异步chunk生成`preload`链接，可通过配置优化预加载策略，提前加载可能需要的资源，减少用户操作后的等待时间。

```javascript
export default defineConfig({
  build: {
    preloadChunks: true, // 自动为异步chunk生成preload链接（首屏必需的异步资源）
    prefetch: true, // 预取可能需要的chunk（如用户可能点击的路由、组件）
    preloadPrefix: '' // 自定义preload资源前缀（如CDN地址）
  }
});
```

**优化效果**：提前加载潜在需要的资源，用户点击路由、打开组件时，资源已缓存，响应速度更快。

## 3. 按需引入第三方库（如UI库）

避免全量引入UI库（如Element Plus、Ant Design Vue），只引入项目中使用的组件，减少冗余代码。

```javascript
// main.js
import { createApp } from 'vue';
// 只引入使用的组件，而非全量引入
import { ElButton, ElTable } from 'element-plus';
// 只引入对应组件的样式，避免加载全量样式
import 'element-plus/es/components/button/style/css';
import 'element-plus/es/components/table/style/css';

const app = createApp(App);
app.use(ElButton).use(ElTable); // 注册引入的组件
```

**优化效果**：UI库体积从几百KB降至几十KB，大幅减少首屏加载体积和执行耗时。

## 4. 静态资源CDN部署

将打包后的静态资源（图片、字体、JS/CSS）部署到CDN，利用CDN边缘节点加速，减少服务器带宽压力，提升资源加载速度。

```javascript
// vite.config.js
export default defineConfig({
  base: 'https://cdn.example.com/your-project/', // 静态资源前缀（CDN地址）
  build: {
    assetsDir: 'assets', // 静态资源目录（部署后对应CDN路径）
    outDir: 'dist' // 构建输出目录
  }
});
```

**优化效果**：静态资源加载速度提升50%+，尤其针对跨地域用户，加载延迟大幅降低。

# 四、通用避坑点（避免优化反效果）

- **不要过度拆分chunk**：HTTP/1.1环境下，chunk数量建议≤10个；HTTP/2环境下≤20个。过多chunk会增加请求协商成本，反而降低加载速度。

- **CDN引入需注意兼容性**：外部化的依赖（如vue、echarts），CDN版本必须与项目依赖版本一致，否则会出现兼容性报错。

- **图片内联阈值不宜过大**：超过8KB的图片内联会增加JS/CSS体积，导致首屏加载变慢，建议阈值控制在2~8KB。

- **开发环境禁用压缩/图片优化**：压缩、图片优化等操作会增加构建耗时，仅在生产环境启用，避免影响开发效率。

- **避免盲目外部化依赖**：核心依赖（如vue、vue-router）不建议外部化，避免CDN宕机导致项目无法运行。

# 五、优化总结

Vite优化的核心逻辑是「减少处理范围、降低产物体积、错峰加载资源」，不同阶段的优化重点不同：

1. **开发阶段**：优化依赖预构建、减少插件/文件监听范围，核心目标是提升启动/热更新速度，改善开发体验。

2. **构建阶段**：通过代码/资源压缩、Tree-Shaking、CDN外部化、静态资源优化，核心目标是减小产物体积，降低传输耗时。

3. **运行阶段**：通过路由懒加载、按需引入、预加载，核心目标是错峰加载资源，提升页面加载和代码执行速度。

优先落地「路由懒加载 + manualChunk + 图片压缩 + Gzip」这4个优化项，可解决80%的Vite项目性能问题；其余优化项可根据项目规模（如大型项目增加CDN部署、UI库按需引入）逐步迭代，平衡优化成本与效果。
> （注：文档部分内容可能由 AI 生成）