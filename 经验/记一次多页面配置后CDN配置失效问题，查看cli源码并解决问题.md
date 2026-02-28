### 前言

某天的某天，产品总监突然给我一个任务，让我在主站加一个页面。由于主站之前已经是 nodeJs 了，在原有基础上进行原生页面编写费时费力，且没有很大的 SEO 需求。所以我使用了上次商家入驻，在 Vue3 SPA 原来的基础上进行多页面开发。

### SPA 多页面配置的好处

1. 共享项目逻辑：作为新增加的页面，可以无缝地使用之前不相关业务的基建逻辑，如公用封装方法等。
2. chunk 分离，业务分离，减少包大小：如果是在单入口的情况下增加一个新的路由，在主入口的 js 文件中势必会带上原有的部分业务逻辑，组件等。这样会增加请求时的包大小。
3. 自定义入口 TDK 有效，SEO 优化更精确

### 开始配置

这里主要是通过 vue.config.js 入口进行配置

```js
// vue.config.js增加新配置项
pages: {
  // 旧的商家入驻入口
  index: {
    entry: 'src/main.ts',
    template: 'public/index.html',
    filename: 'index.html',
    title: 'Index Page',
    chunks: ['chunk-vendors', 'chunk-common', 'index']
  },
  share: {
    entry: 'src/share.ts',
    template: 'public/share.html',
    filename: 'share.html',
    title: '',
    chunks: ['chunk-vendors', 'chunk-common', 'share']
  }
},
chainWebpack: config => {
  const cdn = { .... }
  config
    .plugin('html')
    .use(HtmlWebpackPlugin)
    .tap(args => {
      console.log(args);
      args[0].cdn = cdn
      args[0].chunksSortMode = 'none'
      // args.cdn = assetsCDN.assets;
      return args
    })
}

```

当我信誓旦旦地准备看到绿色打印时，却报了一个 **TypeError: Cannot set properties of undefined (setting 'cdn')**的错误，
于是，我打印了 args 的值，发现打印出来了一个空的数组。此时我做了一个猜想，重新使用了 HtmlWebpackPlugin 插件，会不会导致原有的配置被清空？

### 带着疑问解决问题。于是，我看了看 vue-cli4 的源码

```js
// 当我们运行vue-cli-service run serve 相当于直接调用以下指令
new Service(...).run('serve')
// 下面是主要运行过程的简化版代码
module.exports = class Service {
  constructor (context, { plugins, pkg, inlineOptions, useBuiltIn } = {}) {
    process.VUE_CLI_SERVICE = this
    // 初始化chainWebpack链式调用配置，存储所有的chainWebapck配置链
    this.webpackChainFns = []
    // 初始化webpackConfigure配置
    this.webpackRawConfigFns = []
    // 初始化所有的webpackChain链式
    this.plugins = this.resolvePlugins(plugins, useBuiltIn)

  }
  async run (name, args = {}, rawArgv = []) {
    this.init()
    // 当指令为serve时 其实是调用了/vue-cli-4/packages/@vue/cli-service/lib/commands/serve.js里面的运行逻辑
    const { fn } = command
    return fn(args, rawArgv)
  }
  init(mode) {
    // 应用所有plugins数组的插件插件
    this.plugins.forEach(({ id, apply }) => {
      if (this.pluginsToSkip.has(id)) return
      apply(new PluginAPI(id, this), this.projectOptions)
    })
    if (this.projectOptions.chainWebpack) {
      this.webpackChainFns.push(this.projectOptions.chainWebpack)
    }
  }
  resolvePlugins (inlinePlugins, useBuiltIn) {
    const idToPlugin = id => ({
      id: id.replace(/^.\//, 'built-in:'),
      apply: require(id)
    })

    let plugins
    // 每一个内置的js都按顺序require一次
    const builtInPlugins = [
      './commands/serve',
      '...', // 其他插件省略
      './config/app'
    ].map(idToPlugin)

    // 引入所有的内置插件文件，最后存储在this.plugins数组里面
    const projectPlugins = Object.keys(this.pkg.devDependencies || {})
      .concat(Object.keys(this.pkg.dependencies || {}))
      .filter(isPlugin)
      .map(id => {
        if (
          this.pkg.optionalDependencies &&
          id in this.pkg.optionalDependencies
        ) {
          let apply = () => {}
          try {
            apply = require(id)
          } catch (e) {
            warn(`Optional dependency ${id} is not installed.`)
          }

          return { id, apply }
        } else {
          return idToPlugin(id)
        }
      })
    plugins = builtInPlugins.concat(projectPlugins)


    return plugins
  }
  // 解析webpackChain
  resolveChainableWebpackConfig () {
    const chainableConfig = new Config()
    // config作为实例，链式调用所有方法，应用所有WebpackChain配置
    this.webpackChainFns.forEach(fn => fn(chainableConfig))
    return te
  }
  // 在混合/vue-cli-4/packages/@vue/cli-service/lib/commands下的所有配置
  resolveWebpackConfig (chainableConfig = this.resolveChainableWebpackConfig()) {
    // 所有chainWebpack配置初始化成webpackCompiler(options)模式
    let config = chainableConfig.toConfig()
    const original = config
    // 和configureWebapck混合
    this.webpackRawConfigFns.forEach(fn => {
      if (typeof fn === 'function') {
        // function with optional return value
        const res = fn(config)
        if (res) config = merge(config, res)
      } else if (fn) {
        // merge literal values
        config = merge(config, fn)
      }
    })

    return config
  }
}
// packages/@vue/cli-service/lib/PluginAPI.js
class PluginAPI {
  constructor (id, service) {
    this.id = id
    this.service = service
  }
  resolveWebpackConfig (chainableConfig) {
    return this.service.resolveWebpackConfig(chainableConfig)
  }
  chainWebpack (fn) {
    this.service.webpackChainFns.push(fn)
  }
}


// vue-cli4/packages/@vue/cli-service/lib/commands/serve.js
// 上面Sevice类的run方法最终调用了当前类的serve方法，在这里调用了新增Plugins的resolveWebpackConfig
// 也就是Service类的resolveWebpackConfig方法
module.exports = (api, options) => {
  api.registerCommand('serve', {
    ...
    }
  }, async function serve (args) {
    // resolve webpack config
    const webpackConfig = api.resolveWebpackConfig()

  })
}

module.exports.defaultModes = {
  serve: 'development'
}

```

从上面代码就可以分析到，vue-cli 是按以下顺序来执行的，

1. Vue-cli 初始化时会使用所有/cli-service/lib/commands，/cli-service/lib/config 内的顺序来获取 webpackChain 的配置，塞入 Service 实例的 webpackChainFns 中。
2. /cli-service/lib/commands 内的插件一般是作为运行插件的，并不会像/cli-service/lib/commands 内的插件一样，一直接调用就直接塞入 webpackChainFns，
   而是在 Plugins 具体调用内部函数的 registerCommand('serve')注册为启动函数后，才会最终调用。
3. 我们在 vue.config.js 配置的 webpackChain 配置在代码逻辑中是在/cli-service/lib/config 的 webpackChain 配置收集完才推入 webpackChainFns 中，这也印证了为什么我们的 html-webpack-plugin 配置之后，原来的多页/单页配置会被覆盖掉。

### 解决办法

说了这么多，那究竟该怎么配置呢，有 2 种办法。

1. 一种就是在原来的 pages 项上加入 cdn 这个 key

```js
// vue.config.js增加新配置项
module.exports = {
  pages: {
    // 旧的商家入驻入口
    index: {
      entry: "src/main.ts",
      ...其他参数省略,
      cdn: {
        js: [
          "https://static.wbiao.co/libs/cdn/vue.global@3.0.11.js",
          "https://static.wbiao.co/libs/cdn/vue-router.global@4.0.6.js",
          "https://static.wbiao.co/libs/cdn/vuex.global@4.0.0.js",
          "https://static.wbiao.co/libs/cdn/axios.min.js",
        ],
      },
    },
    share: {
      entry: "src/share.ts",
      ...其他参数省略,
      cdn: {
        js: [
          "https://static.wbiao.co/libs/cdn/vue.global@3.0.11.js",
          "https://static.wbiao.co/libs/cdn/vue-router.global@4.0.6.js",
          "https://static.wbiao.co/libs/cdn/vuex.global@4.0.0.js",
          "https://static.wbiao.co/libs/cdn/axios.min.js",
        ],
      },
    },
  },
};
```

2. 第二种种就是重写 html-webpack-plugins 的 entry 的模板配置

```js
module.exports = {
  pages: {
    index: {
      entry: "src/main.ts",
      chunks: ["chunk-vendors", "chunk-common", "index"],
    },
    share: {
      entry: "src/share.ts",
      chunks: ["chunk-vendors", "chunk-common", "share"],
    },
  },
  chainWebpack: (config) => {
    const cdn = {
      js: [
        "https://static.wbiao.co/libs/cdn/vue.global@3.0.11.js",
        "https://static.wbiao.co/libs/cdn/vue-router.global@4.0.6.js",
        "https://static.wbiao.co/libs/cdn/vuex.global@4.0.0.js",
        "https://static.wbiao.co/libs/cdn/axios.min.js",
      ],
    };
    config
      .plugin("html")
      .use(HtmlWebpackPlugin)
      .tap((args) => {
        args[0] = {
          title: "wanbiao",
          cdn: cdn,
          minify: {
            removeComments: true,
            collapseWhitespace: true,
            collapseBooleanAttributes: true,
            removeScriptTypeAttributes: true,
          },
          template: path.resolve(__dirname, "./public/index.html"),
        };
        args[1] = {
          title: "wb2",
          cdn: cdn,
          minify: {
            removeComments: true,
            collapseWhitespace: true,
            collapseBooleanAttributes: true,
            removeScriptTypeAttributes: true,
          },
          template: path.resolve(__dirname, "./public/share.html"),
        };
        args[0].cdn = cdn;
        args[0].chunksSortMode = "none";
        // args.cdn = assetsCDN.assets;
        return args;
      });
  },
};
```

### 基础模板展示

```html
<!DOCTYPE html>
<html lang="">
  <head>
    <meta charset="utf-8" />
    <meta name="renderer" content="webkit" />
    <meta name="force-rendering" content="webkit" />
    <meta http-equiv="X-UA-Compatible" content="IE=Edge,chrome=1" />
    <link rel="icon" href="/favicon.ico" />
    <title><%= process.env.VUE_APP_TITLE %></title>
    <!-- 使用CDN的CSS文件 -->
    <% for (var i in htmlWebpackPlugin.options.cdn &&
    htmlWebpackPlugin.options.cdn.css) { %>
    <link rel="stylesheet" href="<%= htmlWebpackPlugin.options.cdn.css[i] %>" />
    <% } %>
    <!-- 使用CDN的JS文件 -->
    <% for (var i in htmlWebpackPlugin.options.cdn &&
    htmlWebpackPlugin.options.cdn.js) { %>
    <script
      type="text/javascript"
      src="<%= htmlWebpackPlugin.options.cdn.js[i] %>"
    ></script>
    <% } %>
  </head>
  <body>
    <noscript>
      <strong
        >We're sorry but <%= htmlWebpackPlugin.options.title %> doesn't work
        properly without JavaScript enabled. Please enable it to
        continue.</strong
      >
    </noscript>
    <div id="app"></div>
    <!-- built files will be auto injected -->
  </body>
</html>
```
