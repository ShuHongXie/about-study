# 微信小程序页面请求前置优化方案（基于FastOpen单例）

# 一、页面加载生命周期及优化背景

小程序页面加载的完整生命周期流程：

1. 视图层初始化，同时逻辑层页面实例创建，触发`onLoad`和`onShow`事件；

2. 等待视图层初始化完成的通知，逻辑层发送页面初始数据；

3. 视图层接收初始数据，完成首次渲染并通知逻辑层，逻辑层触发`onReady`事件，页面首次渲染完成，可与视图层交互；

4. 后续逻辑层调用`setData`，触发视图层再次渲染，视图层回调通知逻辑层，完成一次数据渲染。

常规做法：将数据请求放在`onLoad`事件中，待请求返回数据后，调用`setData`渲染页面。

优化空间：将前置请求提前到页面打开之前（页面跳转时），可更早接收请求返回数据，缩短页面跳转至`onLoad`事件之间的延迟（经测试，该延迟约100~300ms，iPhoneX需150+ms，小米MIX2需200+ms）。

# 二、核心疑问与解决方案原理

## 2.1 核心疑问

页面跳转时，目标页面实例尚未创建，如何发起请求？若将目标页面的请求代码耦合到当前页面，会导致业务逻辑耦合度过高，不利于维护。

## 2.2 解决方案原理

小程序的页面机制支持在页面未创建实例前，获取页面对象的各个方法：

- 小程序启动时，会调用`Page`函数注册所有页面；

- 运行时可获取所有页面原型，页面被访问时，会基于该原型创建实例。

核心思路：包装注册页面的`Page`函数，收集页面原型引用，从而获取页面中的方法，通过单例对象管理前置请求逻辑，避免代码耦合。

# 三、FastOpen单例对象设计

FastOpen单例对象用于处理所有请求前置跳转的逻辑，其核心结构及方法如下：

- `pageList`：存储每个页面的关键信息，包括页面名称、原型引用、获取前置请求数据的方法；

- `register`：用于注册页面，通过包装原生`Page`函数为`CommonPage`，在页面注册时，将页面名称、原型等信息存入`pageList`（业务页面需实现`initQuery`方法，用于定义前置请求）；

- `initPage`：调用目标页面的`initQuery`方法，发起前置请求，并将请求Promise赋值给目标页面的`initDataPromise`；

- `getDataPromise`：目标页面加载完成后，调用该方法获取前置请求返回的数据。

# 四、完整实现代码

## 4.1 封装FastOpen单例（utils/fastOpen.js）

```javascript
// utils/fastOpen.js
class FastOpen {
  constructor() {
    // 单例防重复创建
    if (FastOpen.instance) return FastOpen.instance;
    // 存储页面列表：[{ pageName: 页面路径, prototype: 页面原型, initQuery: 前置请求方法 }]
    this.pageList = [];
    FastOpen.instance = this;
  }

  /**
   * 注册页面（包装Page时调用）
   * @param {string} pageName 页面路径（如/pages/detail/detail）
   * @param {Object} pageProto 页面原型（Page函数的配置对象）
   */
  register(pageName, pageProto) {
    // 避免重复注册
    const exists = this.pageList.some((item) => item.pageName === pageName);
    if (!exists) {
      this.pageList.push({
        pageName,
        prototype: pageProto,
        // 提取页面定义的initQuery方法（前置请求逻辑）
        initQuery: pageProto.initQuery || (() => Promise.resolve({})),
      });
    }
  }

  /**
   * 初始化目标页面的前置请求
   * @param {string} pageName 目标页面路径
   * @param {Object} query 页面跳转的参数（如id、type等）
   * @returns {Promise} 请求Promise
   */
  initPage(pageName, query = {}) {
    const pageItem = this.pageList.find((item) => item.pageName === pageName);
    if (!pageItem) {
      console.warn(`FastOpen: 页面${pageName}未注册`);
      return Promise.reject(new Error(`页面${pageName}未注册`));
    }

    // 执行前置请求，并把Promise挂载到页面项上
    const dataPromise = pageItem.initQuery(query);
    pageItem.initDataPromise = dataPromise;
    return dataPromise;
  }

  /**
   * 获取目标页面的前置请求数据
   * @param {string} pageName 目标页面路径
   * @returns {Promise} 包含前置请求数据的Promise
   */
  getDataPromise(pageName) {
    const pageItem = this.pageList.find((item) => item.pageName === pageName);
    if (!pageItem || !pageItem.initDataPromise) {
      return Promise.resolve({});
    }
    return pageItem.initDataPromise;
  }
}

// 导出单例
const fastOpen = new FastOpen();

/**
 * 包装Page函数，实现页面自动注册到FastOpen
 * @param {string} pageName 页面路径（需在每个页面手动传入，如__dirname）
 * @param {Object} pageConfig 原Page配置对象
 */
function CommonPage(pageName, pageConfig) {
  // 1. 注册到FastOpen
  fastOpen.register(pageName, pageConfig);

  // 2. 执行原生Page函数（保留原有生命周期）
  Page(pageConfig);
}

// 导出核心方法
module.exports = {
  fastOpen,
  CommonPage,
};
```

## 4.2 页面使用示例（完整流程）

### 步骤1：目标页面（pages/detail/detail.js）

```javascript
// pages/detail/detail.js
const { CommonPage } = require("../../utils/fastOpen.js");

// 用CommonPage替代原生Page，第一个参数是页面路径（必填）
CommonPage("pages/detail/detail", {
  // 【核心】前置请求方法：定义需要提前发的请求
  initQuery(query) {
    // query是跳转时传入的参数（如商品id）
    console.log("前置请求-接收参数：", query);
    // 模拟接口请求（替换为你的真实接口）
    return new Promise((resolve) => {
      setTimeout(() => {
        resolve({
          goodsId: query.id,
          goodsName: "前置请求获取的商品名称",
          price: 99.9,
        });
      }, 500); // 模拟接口耗时
    });
  },

  // 原有生命周期
  onLoad(options) {
    const that = this;
    // 获取前置请求的数据（无需再发请求，直接拿结果）
    this.fastOpen.getDataPromise("pages/detail/detail").then((res) => {
      console.log("onLoad中获取前置请求数据：", res);
      that.setData({
        goodsInfo: res,
      });
    });
  },

  onShow() {},
  onReady() {},
});
```

### 步骤2：跳转页面（pages/index/index.js）

```javascript
// pages/index/index.js
const { fastOpen } = require("../../utils/fastOpen.js");

Page({
  // 点击跳转按钮触发
  goToDetail() {
    const targetPage = "pages/detail/detail";
    const query = { id: "123456" }; // 跳转参数

    // 【关键】跳转前先执行目标页面的前置请求
    fastOpen
      .initPage(targetPage, query)
      .then((res) => {
        console.log("前置请求已完成，数据：", res);
      })
      .catch((err) => {
        console.error("前置请求失败：", err);
      });

    // 执行页面跳转（保留原有跳转逻辑）
    wx.navigateTo({
      url: `/pages/detail/detail?id=${query.id}`,
    });
  },
});
```

# 五、关键代码解释

1. **FastOpen单例**：
   - `register`：包装`Page`时自动注册页面，收集页面路径、原型和`initQuery`方法，避免重复注册；

   - `initPage`：页面跳转时调用，执行目标页面的前置请求，并缓存请求Promise；

   - `getDataPromise`：目标页面`onLoad`时调用，获取前置请求结果，直接用于页面渲染。

2. **CommonPage函数**：替代原生`Page`函数，实现页面自动注册到FastOpen，无侵入式改造原有页面逻辑，不影响页面原有生命周期。

3. **initQuery方法**：每个需要前置请求的页面自行定义，包含具体的接口请求逻辑，入参为页面跳转时传入的参数。

# 六、注意事项

- 前置请求失败处理：若前置请求失败（如网络错误），需在`getDataPromise`的`catch`中做降级处理（例如重新发起请求），避免页面渲染异常；

- 页面路径统一：注册页面和调用方法时，页面路径需保持一致（如`pages/detail/detail`），避免因路径不一致导致无法获取页面原型；

- 接口耗时优化：该方案仅优化“请求发起时间”，接口本身的耗时仍需通过接口优化（如数据缓存、接口压缩）进一步提升；

- 避免重复请求：可在`initQuery`中添加请求防抖/节流逻辑，防止多次跳转触发重复请求。

# 七、总结

1. **核心优化点**：将页面`onLoad`中的请求前置到“页面跳转时”，减少100~300ms的请求延迟，提升页面加载体验；

2. **实现关键**：利用小程序页面原型机制，包装`Page`函数收集页面原型，通过FastOpen单例提前执行目标页面的`initQuery`方法，避免代码耦合；

3. **使用方式**：目标页面用`CommonPage`替代`Page`并定义`initQuery`；跳转页调用`fastOpen.initPage`触发前置请求；目标页`onLoad`中调用`getDataPromise`获取数据并渲染。

该方案无侵入式改造原有代码，兼顾代码可维护性和页面加载性能，是小程序页面加载优化的实用方案。
