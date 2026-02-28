## 前言

最近在做公司项目的时候遇到了一个很奇怪的 bug, 当前页为一个 better-scroll 页面 当跳转到下一个页面再返回再跳转时 一次点击事件触发了 2 次。原因: better-scroll 第二次初始化时第一次的实例未卸载导致

## 解决思路 在第二次重新初始化时把 click 配置项改为 false

```js
export default {
  methods: {
    _initScroll(bool) {
      const _self = this;
      _self.listBscroll = new BScroll(".list-wrapper", {
        probeType: 1,
        click: bool,
        pullUpLoad: { threshold: -30 },
      });
    },
  },
};
```
