<!--
 * @Author: 谢树宏
 * @Date: 2022-02-08 10:24:32
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-09 15:15:21
 * @FilePath: /about-study/webpack.md
-->

1. bundle 和 chunks 的区别 chunk 指 webpack 打包时的文件总称，bundle 是 webpack 打包完成后的文件总称
2. css-loader 和 style-loader 的区别，style-loader 是负责把 css 插入 dom， css-loader 被用来解析@import 和 url()这种 css 引入方式
3. loaders 和 plugins 的区别，webpack 只能处理 js 文件，laoder 能对其他类型的资源进行转译的预处理，转换成 js。plugins 可以扩展 Webpack 的功能，在 Webpack 运行的生命周期中会广播出许多事件，Plugin 可以监听这些事件，在合适的时机通过 Webpack 提供的 API 改变输出结果。

4. 构建优化手段

   1. dll 动态打包库打包第三方包
   2. thread-loader 开启多进程打包，
   3. 缩小 loader 的打包范围
   4. 利用缓存充分利用缓存提升二次构建速度 babel-loader 开启缓存， cache-loader

5. 线上优化手段

   1. externals 提取 cdn
   2. splitChunks 分离， https://webpack.docschina.org/guides/caching/
   3. import 动态导入

6. 线上更新配置，文件指纹策略
   1. hash：任何一个文件改动，整个项目的构建 hash 值都会改变；文件只要改动，父文件和子文件的 hash 都会引起变化，这样会造成，更新之后所有的 http 缓存会失效
   2. chunkhash：文件的改动只会影响其所在 chunk 的 hash 值；
   3. contenthash：每个文件都有单独的 hash 值，文件的改动只会影响自身的 hash 值；
      假如文件引入的子文件发生变化，那么当前文件的 contentHash 也会发生变化，但是如果当前文件变了，子引用不会发生变化，这对于 http 缓存是最好的选择，保存了当前的文件缓存

### 相关插件

1.FriendlyErrorsWebpackPlugin：去除 webpack-dev-server 控制台打印
