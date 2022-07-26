<!--
 * @Author: 谢树宏
 * @Date: 2022-02-08 10:24:32
 * @LastEditors: 谢树宏 384180258@qq.com
 * @LastEditTime: 2022-07-26
 * @FilePath: /about-study/webpack.md
-->

1. bundle 和 chunks 的区别 chunk 指 webpack 打包时的文件总称，bundle 是 webpack 打包完成后的文件总称
2. css-loader 和 style-loader 的区别，style-loader 是负责把 css 插入 dom， css-loader 被用来解析@import 和 url()这种 css 引入方式
3. loaders 和 plugins 的区别，webpack 只能处理 js 文件，laoder 能对其他类型的资源进行转译的预处理，转换成 js。plugins 可以扩展 Webpack 的功能，在 Webpack 运行的生命周期中会广播出许多事件，Plugin 可以监听这些事件，在合适的时机通过 Webpack 提供的 API 改变输出结果。
4. file-loader 和 url-loader 的区别：file-loader：返回的是图片的 public URL。url-loader 是对 file-loader 的再封装，可以设置一个最小值通过，小于该最小值的图片可以返回 base64,减少 http 请求

5. 构建优化手段

   1. dll 动态打包库打包第三方包
   2. thread-loader 开启多进程打包，
   3. 缩小 loader 的打包范围
   4. 利用缓存充分利用缓存提升二次构建速度 babel-loader， cache-loader 等内置了缓存功能
   5. webpack5 持久化缓存 cache,将首次构建的过程和结果数据久化保存到本地文件系统，在下次执行构建时跳过解析、链接、编译，复用上次的对象，下次编译时直接对比每个文件的内容哈希或时间戳，未发生变化的文件跳过编译操作，直接使用缓存副本，减少重复计算；发生变更的模块则重新执行编译流程。
   6. 约束 loader 的执行范围，babel-loader、eslint-loader、vue-loader 等，需要反复执行代码到 AST，AST 到代码的转换。使用 module.rules.include、module.rules.exclude 等配置项，限定 Loader 的执行范围 —— 通常可以排除 node_module 文件夹。
   7. noParse 跳过文件编译，缺点：1.由于跳过了 ast 的分析，所以无法发现文件中可能存在的语法错误 2.由于跳过了依赖分析，所以文件中最好不要依赖 import/export/require/define 等语法 3.由于跳过了内容分析，也就无法 tree-shaking
   8. 跳过 TS 类型检查，ts 类型检查涉及 AST 解析、遍历以及其它非常消耗 CPU 的操作。1.可以借助编译器 2.使用 fork-ts-checker-webpack-plugin 插件将类型检查能力剥离到 子进程 执行.
   9. eslint-webpack-plugin 替代 eslint-loader,两者差异在于，eslint-webpack-plugin 在模块构建完毕（compilation.hooks.succeedModule 钩子）后执行检查，不会阻断文件加载流程，性能更优.
   10. 图像优化：雪碧图合并(webpack-spritesmith)，响应式图片生成(resize-image-loader)，图片压缩(image-webpack-loader)

6. 线上优化手段

   1. externals 提取 cdn
   2. splitChunks 设置缓存组， https://webpack.docschina.org/guides/caching/
   3. import 动态导入

7. 线上更新配置，文件指纹策略
   1. hash：任何一个文件改动，整个项目的构建 hash 值都会改变；文件只要改动，父文件和子文件的 hash 都会引起变化，这样会造成，更新之后所有的 http 缓存会失效
   2. chunkhash：文件的改动只会影响其所在 chunk 的 hash 值；
   3. contenthash：每个文件都有单独的 hash 值，文件的改动只会影响自身的 hash 值；
      假如文件引入的子文件发生变化，那么当前文件的 contentHash 也会发生变化，但是如果当前文件变了，子引用不会发生变化，这对于 http 缓存是最好的选择，保存了当前的文件缓存

### 概念

chunk 有两种形式

1. Initial Chunk(初始化 chunk), entry 所配置的 chunk，由 output.filename 来决定名称
2. Async Chunk,non-initial, 可以延迟加载的模块，比如 import('./xx.js') 引入的 由 output.chunkFilename 来决定名称

### 相关插件

1.FriendlyErrorsWebpackPlugin：去除 webpack-dev-server 控制台打印
2.speed-measure-webpack-plugin：输出 webpack 的构建时间
3.html-webpack-plugin: 输出 html

https://zhuanlan.zhihu.com/p/410714465
