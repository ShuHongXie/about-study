## 前言

令人惊讶的事情发生了，618 懂表帝小程序访问量突然间过万，老板马不停蹄地让我们识表模块改版，再次记录下改版后代码中遇到的问题。

### 改写的第三方 canvas_drawer 绘图插件竟然有 bug，而且还不只一个

插件原地址：https://ext.dcloud.net.cn/plugin?id=14

因为把海报绘制模块重写了一遍。期间发现了 3 个问题。

**第一个 bug 是我自己改写后的问题，**

1. 图片有可能还没获取完，就直接绘图，造成图片缺失。

![](http://www.xiesmallxie.cn/20220624183756.png)

```js
// 直接修改成以下样式
async getImagesInfo(views) {
  const imageList = []
  for (let i = 0; i < views.length; i++) {
    if (views[i].type === 'image') {
      // 增加await
      imageList.push(await this.getImageInfo(views[i].url))
    }
  }
}
```

2. 插件本身的问题，插件本身只要超过 10 个网络图片，剩余图片就会无法渲染
