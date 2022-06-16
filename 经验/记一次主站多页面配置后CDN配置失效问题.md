### 前言

某天的某天，产品总监突然给我一个任务，让我在主站加一个页面。由于主站之前已经是 nodeJs 了，所以我使用了上次商家入驻，在原来的基础上进行多页面开发。因为多页面的好处有很多。

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
于是，我打印了 args 的值，发现打印出来了一个空的对象。此时我做了一个猜想，重新使用了 HtmlWebpackPlugin 插件，会不会导致原有的配置被清空？

### 带着疑问解决问题。于是，我看了看 vue-cli4 的源码
