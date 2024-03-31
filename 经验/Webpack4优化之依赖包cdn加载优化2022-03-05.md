## 前言

记录一下自己项目使用 cdn 加速的具体过程，就是分离外部库的包(包括 vue, vue-router, vuex 等)，尽量只保留主要逻辑

## 准备工作

首先确定一下哪些包需要进行分离，这里我们主要 Vue 的周边库，利用 html-plugin-webpack 插件，插入到 script 标签之中

## 开始配置 webpack

首先配置 html-webpack-plugin 和 webpack 的 externals 属性，防止打包时将要分离的库一起打包进去，这里使用 chainWebpack 插件，

```js
const HtmlWebpackPlugin = require("html-webpack-plugin");

config.externals({ vue: "Vue", "vue-router": "VueRouter", vuex: "Vuex" });
config.plugin("html-webpack-plugin").use(
  new HtmlWebpackPlugin({
    cdnJsModule: [
      "https://lib.baomitu.com/vue/3.0.7/vue.runtime.global.js",
      "https://lib.baomitu.com/vue-router/4.0.4/vue-router.global.prod.js",
      "https://lib.baomitu.com/vuex/4.0.0/vuex.global.prod.min.js",
    ],
    template: "template/loading.html", // 重写div=app
  })
);
```

可以看到 htmlwebpackplugin 配置了 cdnjsModule 这个属性，后续在定制的 loading.html 模板里面写入

```js

<head>
<meta charset="UTF-8" />
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<% for (var i in htmlWebpackPlugin.options.cdnJsModule) { %>
<script src="<%= htmlWebpackPlugin.options.cdnJsModule[i] %>"></script>
<% } %>
</head> ...

```

## 打包对比 现在看看，配置前后的打包情况，可见减少了差不多 100K 左右的大小

```js

// 未配置前
server/js/chunk-vendors.3e815d2d.js 144.96 KiB   52.24 KiB
server/js/app.3ad30f1e.js 46.88 KiB        12.06 KiB
// 配置后
server/js/app.941edfa5.js   50.58 KiB 12.30 KiB
server/js/chunk-vendors.0c15f71f.js    50.22 KiB    18.02 KiB
```
