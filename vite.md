### vite 对比 webpack

1. vite 不需要做全量打包，webpack 需要
2. vite 在解析模块依赖时使用 esbuild(使用 go 编写)，比 javascript 编写的天然快 10-100 倍
3. 按需加载：模块之间的依赖关系由浏览器实现，vite 只需要在浏览器请求源码时进行转换
4. vite 源码模块使用 304 协商缓存，依赖模块请求通过 Cache-control:max-age 进行强缓存

### vite 对比 webpack 的优点

1. 更快的冷启动
2. 更快的热更新

### vite 对比 webpack 的缺点

1. 开发环境下首屏加载变慢
2. 开发环境下懒加载变慢
3. webpack 生态比 vite 完善
