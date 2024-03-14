## 总结

总结下自己前一段时间公司项目使用 Better-scroll 进行总体封装，集成下拉刷新,上拉加载等

```js
<template>
  <div class="wrapper" :ref="refUuid">
    <div class="wrapper--content" :ref="`${refUuid}Content`">
      <div class="pulldown-wrapper" v-if="pulldown">
        <div v-show="beforePullDown"><span>下拉刷新</span></div>
        <div v-show="!beforePullDown">
          <div v-show="isPullingDown">
            <van-loading size="24px" type="spinner">加载中...</van-loading>
          </div>
          <div v-show="!isPullingDown"><span>刷新成功</span></div>
        </div>
      </div>
      <slot></slot>
      <div
        class="pullup-wrapper"
        v-if="pullup && showPullup && showHasMoreScreen"
      >
        <div v-if="!isPullUpLoad" class="before-trigger">
          <span class="pullup-txt">上拉刷新</span>
        </div>
        <div v-else class="after-trigger">
          <van-loading size="24px" type="spinner" v-if="hasMore"
            >加载中...</van-loading
          >
          <span v-else>没有更多了。。。。。</span>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import BScroll from "better-scroll";
import { v4 as uuidv4 } from "uuid";
export default {
  data() {
    return {
      scroll: null,
      refUuid: uuidv4(),
      showPullup: true, // 是否展示加载更多栏目
    };
  },
  props: {
    /**
     * 1 滚动的时候会派发scroll事件，会截流。
     * 2 滚动的时候实时派发scroll事件，不会截流。
     * 3 除了实时派发scroll事件，在swipe的情况下仍然能实时派发scroll事件
     */
    probeType: { type: Number, default: 1 }, // 点击列表是否派发click事件
    click: { type: Boolean, default: true }, // 是否开启横向滚动
    scrollX: { type: Boolean, default: false }, // 是否派发滚动到底部的事件，用于上拉加载
    pullup: { type: Boolean, default: false }, // 是否派发顶部下拉的事件，用于下拉刷新
    pulldown: { type: Boolean, default: false }, // 刷新的时延
    refreshDelay: { type: Number, default: 20 }, // 数据源
    data: { type: [Array, Object], default: null }, // 开始下拉
    beforePullDown: { type: Boolean, default: true }, // 下拉中
    isPullingDown: { type: Boolean, default: false }, // 上拉中
    isPullUpLoad: { type: Boolean, default: false }, // 是否有更多数据
    hasMore: { type: Boolean, default: true }, // 是否展示底部的加载更多数据
    showHasMoreScreen: { type: Boolean, default: true },
  },
  mounted() {
    this.$nextTick(() => {
      setTimeout(() => {
        this.initBetterScroll();
        this.refreshPullRegion();
        this.refreshScrollXRegion();
      }, 10);
      setTimeout(() => {
        this.initcroll();
      }, 10);
    });
  },
  watch: {
    // 监听数据的变化，延时 refreshDelay 时间后调用 refresh 方法重新计算，保证滚动效果正常
    data() {
      setTimeout(() => {
        this.refresh();
      }, this.refreshDelay);
    },
  },
  methods: {
    // 判断滚动区域是否大于呈现区域 如果大于 就不可能出现上拉刷新显示区
    refreshPullRegion() {
      if (
        this.$refs[this.refUuid].clientHeight >
        this.$refs[`${this.refUuid}Content`].clientHeight
      ) {
        this.showPullup = false;
      } else {
        this.showPullup = true;
      }
      console.log("----结束", this.showPullup);
    },
    refreshScrollXRegion() {
      if (this.scrollX) {
        this.$refs[`${this.refUuid}Content`].style.position = "absolute";
      }
    },
    initBetterScroll() {
      // 没有就为空
      if (!this.$refs[this.refUuid]) return;
      const config = {};
      if (this.pulldown) {
        config.pullDownRefresh = { stop: 56, threshold: 70 };
      }
      if (this.pullup) {
        config.pullUpLoad = true;
      }
      if (this.scrollX) {
        config.scrollX = true;
      }
      // 开始初始化
      this.scroll = new BScroll(this.$refs[this.refUuid], {
        click: true,
        scrollY: true,
        observeDOM: true,
        ...config,
      });
      // 如果有开启下拉 就监听下拉事件
      if (this.pulldown) {
        this.scroll.on("pullingDown", async () => {
          this.$emit("pulldown");
        });
      }
      // 如果有开启上拉 就监听上拉事件
      if (this.pullup) {
        this.scroll.on("pullingUp", async () => {
          this.$emit("pullup");
        });
      }
    },
    refresh() {
      if (this.pullup) {
        this.scroll.finishPullUp();
      }
      this.scroll && this.scroll.refresh();
      this.refreshPullRegion();
      this.refreshScrollXRegion();
    },
  },
};
</script>

<style lang="scss" scoped>
.wrapper {
  flex: 1;
  overflow: hidden;
  position: relative;
  &--content {
    z-index: 2;
    .pulldown-wrapper {
      position: absolute;
      width: 100%;
      padding: 20px;
      box-sizing: border-box;
      transform: translateY(-100%) translateZ(0);
      text-align: center;
      color: #999;
    }
    .pullup-wrapper {
      padding: 20px;
      text-align: center;
      color: #999;
    }
  }
}
</style>
```
