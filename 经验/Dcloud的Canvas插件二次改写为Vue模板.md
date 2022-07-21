## 前言

由于公司用的海报图插件都是使用的[canvas_drawer](https://ext.dcloud.net.cn/plugin?id=14)插件来绘制海报图，由于是 18 年的插件，且只支持微信小程序原生语法。如果有其他客户端小程序的要求下是无法兼容的，对此我将他改造成 vue 组件形式来适配 uni-app 的多客户端需求

## 改造要点

1. 部分 setData 语法存在异步情况，可能会导致逻辑问题
2. 旧文件里面使用的 promise.then 语法太过于冗杂，更换成 async await 语法兼容
3. 旧的 triggerEvent 更换成 emit
4. **字节小程序**同时进行 2 次渲染会导致渲染重叠，传入的 id 实例不能重复

/more

下面看主要改造后的代码

```vue
<template>
  <view>
    <canvas
      :canvas-id="name"
      :style="{ width: width + 'px', height: height + 'px' }"
      class="board"
      v-if="showCanvas"
    ></canvas>
  </view>
</template>

<script>
export default {
  props: {
    painting: {
      type: Object,
    },
    name: {
      type: String,
    },
  },
  data() {
    return {
      showCanvas: false,
      width: 100,
      height: 100,
      tempFileList: [],
      isPainting: false,
      ctx: null,
      cache: Array(),
    };
  },
  watch: {
    painting(newVal, oldVal) {
      if (!this.isPainting) {
        if (JSON.stringify(newVal) !== JSON.stringify(oldVal)) {
          if (newVal && newVal.width && newVal.height) {
            this.showCanvas = true;
            this.isPainting = true;

            this.readyPigment();
          }
        } else {
          if (newVal && newVal.mode !== "same") {
            // this.triggerEvent('getImage', {errMsg: 'canvasdrawer:samme params'})
            this.$emit("getImage", { errMsg: "canvasdrawer:samme params" });
          }
        }
      }
    },
  },
  onReady() {
    uni.removeStorageSync("canvasdrawer_pic_cache");
    this.ctx = uni.createCanvasContext(this.name, this);
  },
  methods: {
    readyPigment() {
      const width = this.painting.width;
      const height = this.painting.height;
      const views = this.painting.views;
      this.width = width;
      this.height = height;

      const inter = setInterval(() => {
        if (this.ctx) {
          clearInterval(inter);
          // this.ctx.clearActions()
          this.ctx.save();
          this.getImagesInfo(views);
        }
      }, 100);
    },
    async getImagesInfo(views) {
      const imageList = [];
      for (let i = 0; i < views.length; i++) {
        if (views[i].type === "image") {
          imageList.push(await this.getImageInfo(views[i].url));
        }
      }
      this.tempFileList = imageList;
      this.startPainting();
    },
    startPainting() {
      const tempFileList = this.tempFileList;
      const views = this.painting.views;
      // const { tempFileList, painting: { views } } = this.$data
      for (let i = 0, imageIndex = 0; i < views.length; i++) {
        if (views[i].type === "image") {
          this.drawImage({
            ...views[i],
            url: tempFileList[imageIndex],
          });
          imageIndex++;
        } else if (views[i].type === "text") {
          if (!this.ctx.measureText) {
            uni.showModal({
              title: "提示",
              content:
                "当前版本过低，无法使用 measureText 功能，请升级到最新微信版本后重试。",
            });
            // this.triggerEvent('getImage', {errMsg: 'canvasdrawer:version too low'})
            this.$emit("getImage", { errMsg: "canvasdrawer:version too low" });
            return;
          } else {
            this.drawText(views[i]);
          }
        } else if (views[i].type === "rect") {
          this.drawRect(views[i]);
        }
      }
      this.ctx.draw(false, () => {
        uni.setStorageSync("canvasdrawer_pic_cache", this.cache);
        const system = uni.getSystemInfoSync().system;
        if (/ios/i.test(system)) {
          this.saveImageToLocal();
        } else {
          // 延迟保存图片，解决安卓生成图片错位bug。
          setTimeout(() => {
            this.saveImageToLocal();
          }, 800);
        }
      });
    },
    drawImage(params) {
      this.ctx.save();
      const {
        url,
        top = 0,
        left = 0,
        width = 0,
        height = 0,
        borderRadius = 0,
        deg = 0,
      } = params;
      if (deg !== 0) {
        this.ctx.translate(left + width / 2, top + height / 2);
        this.ctx.rotate((deg * Math.PI) / 180);
        this.ctx.drawImage(url, -width / 2, -height / 2, width, height);
      } else {
        this.ctx.beginPath();

        this.ctx.arc(left, top, borderRadius, 0, 2 * Math.PI, false);

        this.ctx.fillStyle = "#9fd9ef";

        this.ctx.fill();

        this.ctx.lineWidth = 1;

        this.ctx.strokeStyle = "#00477d";

        this.ctx.stroke();
        this.ctx.drawImage(url, left, top, width, height);
      }

      this.ctx.restore();
    },
    drawText(params) {
      this.ctx.save();
      const {
        MaxLineNumber = 2,
        breakWord = false,
        color = "black",
        content = "",
        fontSize = 16,
        top = 0,
        left = 0,
        lineHeight = 20,
        textAlign = "left",
        width,
        bolder = false,
        textDecoration = "none",
      } = params;

      this.ctx.beginPath();
      this.ctx.setTextBaseline("top");
      this.ctx.setTextAlign(textAlign);
      this.ctx.setFillStyle(color);
      this.ctx.setFontSize(fontSize);

      if (!breakWord) {
        this.ctx.fillText(content, left, top, width);
        this.drawTextLine(left, top, textDecoration, color, fontSize, content);
      } else {
        let fillText = "";
        let fillTop = top;
        let lineNum = 1;
        for (let i = 0; i < content.length; i++) {
          fillText += [content[i]];
          if (this.ctx.measureText(fillText).width > width) {
            if (lineNum === MaxLineNumber) {
              if (i !== content.length) {
                fillText = fillText.substring(0, fillText.length - 1) + "...";
                this.ctx.fillText(fillText, left, fillTop);
                this.drawTextLine(
                  left,
                  fillTop,
                  textDecoration,
                  color,
                  fontSize,
                  fillText
                );
                fillText = "";
                break;
              }
            }
            this.ctx.fillText(fillText, left, fillTop);
            this.drawTextLine(
              left,
              fillTop,
              textDecoration,
              color,
              fontSize,
              fillText
            );
            fillText = "";
            fillTop += lineHeight;
            lineNum++;
          }
        }
        this.ctx.fillText(fillText, left, fillTop);
        this.drawTextLine(
          left,
          fillTop,
          textDecoration,
          color,
          fontSize,
          fillText
        );
      }

      this.ctx.restore();

      if (bolder) {
        this.drawText({
          ...params,
          left: left + 0.3,
          top: top + 0.3,
          bolder: false,
          textDecoration: "none",
        });
      }
    },
    drawTextLine(left, top, textDecoration, color, fontSize, content) {
      if (textDecoration === "underline") {
        this.drawRect({
          background: color,
          top: top + fontSize * 1.2,
          left: left - 1,
          width: this.ctx.measureText(content).width + 3,
          height: 1,
        });
      } else if (textDecoration === "line-through") {
        this.drawRect({
          background: color,
          top: top + fontSize * 0.6,
          left: left - 1,
          width: this.ctx.measureText(content).width + 3,
          height: 1,
        });
      }
    },
    drawRect(params) {
      this.ctx.save();
      const { background, top = 0, left = 0, width = 0, height = 0 } = params;
      this.ctx.setFillStyle(background);
      this.ctx.fillRect(left, top, width, height);
      this.ctx.restore();
    },
    getImageInfo(url) {
      return new Promise((resolve, reject) => {
        if (this.cache[url]) {
          resolve(this.cache[url]);
        } else {
          const objExp = new RegExp(
            /^http(s)?:\/\/([\w-]+\.)+[\w-]+(\/[\w- .\/?%&=]*)?/
          );
          if (objExp.test(url)) {
            uni.getImageInfo({
              src: url,
              complete: (res) => {
                if (res.errMsg === "getImageInfo:ok") {
                  this.cache[url] = res.path;
                  resolve(res.path);
                } else {
                  // this.triggerEvent('getImage', {errMsg: 'canvasdrawer:download fail'})
                  this.$emit("getImage", {
                    errMsg: "canvasdrawer:download fail",
                  });
                  reject(new Error("getImageInfo fail"));
                }
              },
            });
          } else {
            this.cache[url] = url;
            resolve(url);
          }
        }
      });
    },
    saveImageToLocal() {
      const width = this.width;
      const height = this.height;
      uni.canvasToTempFilePath(
        {
          x: 0,
          y: 0,
          width,
          height,
          canvasId: this.name,
          complete: (res) => {
            if (res.errMsg === "canvasToTempFilePath:ok") {
              this.showCanvas = false;
              this.isPainting = false;
              this.tempFileList = [];
              this.$emit("getImage", {
                tempFilePath: res.tempFilePath,
                errMsg: "canvasdrawer:ok",
              });
            } else {
              this.$emit("getImage", { errMsg: "canvasdrawer:fail" });
            }
          },
        },
        this
      );
    },
  },
};
</script>

<style>
.board {
  position: fixed;
  top: 2000rpx;
}
</style>
```
