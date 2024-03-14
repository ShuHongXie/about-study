### 前言

对于公司级组件库来说，服务于业务的组件存在着参数较多，参数经常记不住问题。而且，脆弱的在线调试也为组件使用产生了很大的不便，好在出现了 StoryBook 这个神器，弥补了这个不足之处。

### 为 Vue 使用 storybook，基于 Vue-cli 环境搭建

> 集成 storybook 依赖

```js
npx storybook init
```

执行之后会在根目录生成**storybook**项目文件，如下图

![](https://www.xiesmallxie.cn/20220708174827.png?imageMogr2/thumbnail/600x300)

> 为你的组件库组件/方法/指令提供全局注册，继承 Vue 实例行为，修改.storybook/preview.js

```js
export const parameters = {
  actions: { argTypesRegex: "^on[A-Z].*" },
  controls: {
    matchers: {
      color: /(background|color)$/i,
      date: /Date$/,
    },
  },
};

import { app } from "@storybook/vue3";
// app相当于main.js文件中引入的Vue实例
// Vue3示例操作，增加全局方法/变量
app.config.globalProperties.OSS = config.OSS["production"];
app.config.globalProperties.OSS_STATIC = config.OSS.static;
app.config.globalProperties.ERROR_IMG = config.PIC.errorPage;
```

配置主入口，为 storybook 自有文件提供解析

```js
const path = require("path");

module.exports = {
  // glob模式匹配文件
  stories: ["../src/package/*/*.(js|jsx|ts|tsx)"],
  // 相关库支持
  addons: [
    "@storybook/addon-links",
    "@storybook/addon-essentials",
    "@storybook/addon-interactions",
    "@storybook/preset-scss", // scss语法支持
  ],
  // 自定义webpack配置，相当于vue.config.js里面的configureWebpack选项
  webpackFinal: async (config, { configType }) => {
    config.resolve.alias["@"] = path.resolve(__dirname, "../src");
    config.resolve.alias["@wb-ui"] = path.resolve(__dirname, "../src");
    return config;
  },
  // 依赖的主包
  framework: "@storybook/vue3",
  core: {
    builder: "@storybook/builder-webpack5",
  },
};
```

> 修改文件模板行为，配置你的组件样式，居中显示

细心的你在预览的时候可能会看到下面的情况，预览始终不居中

![](https://www.xiesmallxie.cn/20220708174826.png?imageMogr2/thumbnail/600x)

**增加 preview-body.html**

```html
<style>
  #root {
    display: flex;
    justify-content: center;
    align-items: center;
  }
</style>
```

> 为业务组件增加 iconfont 支持

万表相关组件是使用的阿里字体图标，在.storybook 文件夹下增加 preview-head.html

```html
<link rel="stylesheet" href="//at.alicdn.com/t/link.css" />
```

> 为组件编写组件描述文件

官方文档参考：https://storybook.js.org/docs/vue/writing-stories/introduction

```ts
// 引入组件
import WbList from "./index";
import { Meta, StoryFn } from "@storybook/vue3";

export default {
  // 组件名称
  title: "wb-list",
  // 组件实例
  component: WbList,
  // 编辑props描述
  argTypes: {
    status: {
      description:
        "状态常量 NO_MORE: 没有更多/LOAD：加载中/END：到底/ERROR：错误",
      required: true,
    },
    total: {
      description: "数据总体长度",
    },
    enableFlex: {
      description: "是否开启flex布局",
    },
    emptyText: {
      description: "数据为空时的文本",
    },
    emptyStyle: {
      description: "数据为空时的文本样式",
    },
    emptyImageStyle: {
      description: "数据为空时的图片样式",
    },
  },
} as Meta<typeof WbList>;

// 配置显示模板
const Template: StoryFn<typeof WbList> = (args) => ({
  components: { WbList },
  setup() {
    return { args };
  },
  template: `<wb-list v-bind="args" :status="status" :total="0" enable-flex >
    <div style="width:200px;height:200px;background: red;margin-right:10px;" v-for="item in [1, 2, 3, 4]" :key="item">213</div>
  </wb-list>`,
});

Template.storyName = "图片组件";

// 配置组件的不同状态
export const Normal = Template.bind({});
Normal.args = {
  status: "LOAD",
  total: 100,
};
```

> 打包 storybook 项目

```js
npm run build-storybook
```
