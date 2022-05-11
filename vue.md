<!--
 * @Author: 谢树宏
 * @Date: 2022-02-14 14:02:43
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-15 16:53:22
 * @FilePath: /about-study/vue.md
-->

### vue-router 路由守卫触发方式

从外到内

初始化：全局 beforeEach -> 组件挂载参数的 beforeEnter -> 组件内 beforeRouteEnter -> 全局 router.afterEach -> 传统生命周期(beforeCreate.....)

离开时: beforeRouteLeave -> beforeEach -> afterEach

### 依赖收集

把数据传入 data 之中，vue 用 object.definedProperty 遍历属性，转换成 getter 和 setter，每个属性都配置一个消息订阅器 dep。当 render 函数渲染时，会读取到当前的属性，触发属性上 dep 的 depend 方法，把当前的 dep 当如 watcher 的 depList 里面，同事 dep 也把当前 watcher 加入内部的 watcher 队列，当属性更新时调用 dep 内部 watcher 队列里面每一个 watcher 的 update 方法,重新执行一遍 render 更新 dom

computed 内部实际上也是执行了一个 lazy 形式的 watcher，当配置一个 computed 时，同样会用 object.definedProperty 遍历属性，当 getter 获取时会调用 get 方法把依赖项的 dep 加入当前 watcher 中，把当前 wathcer 加入 dep 的 watcher 队列里面，更新 watcher 的 value 值，返回 value。当依赖项更新是，当前 computed 的 watcher 会被调用，因为是 lazy，所以不进行主动计算，因为依赖项更新时会引起 render 的重新刷新，会重新拿到 computed 的值，自动进行更新

watch 内部也是创建了一个 watcher 实例，只不过 get 方法在调用时返回了监测内容，当监测 computed 属性时，会将 computed 的 key 的所有依赖项的 dep 里面的 wathcer 队列加入当前 watcher，最后调用 run 时，如果前后数据不一致就直接调用 callback 方法

### diff 算法

1. 定义四个指针，如果新旧两个数据的两端指针交错，就说明对比完成
2. 首先对比旧新开始节点，再对比旧新结束节点，再对比旧开始和新结束，在对比旧结束和新开始
3. 上面 4 组对比如果没有出结果下面会衍生会 2 种情况

4. 新旧的在没有绑定 key 的情况下，会去旧的列表里面找看看有没有跟当前 newVnode 相同的元素，如果没有就在旧的前面插入当前 newVnode。如果旧列表里面有当前元素，会拿当前 newVnode 和旧列表中的相同元素做对比，如果相同，就会在当前 oldStartIndex 前插入 newVnode，旧的相同元素置为 undefined, 如果不同，也会在当前 oldStartIndex 前插入 newVnode。同时下标前进一位

5. 当下标不断收缩时，如果旧开始标位大于旧结束标为时，说明旧的已经对比完成了,如增加新数据的 newStartIdx,newEndIdx 中的数据，如果新开始标位大于新结束标位，那说明有删除项，就把 oldStartIdx 到 oldEndIdx 之中的数据删除

### 虚拟相关

> 正常⽣命周期：beforeRouteEnter --> created --> mounted --> updated -->destroyed

使⽤ keepAlive 后⽣命周期：

> ⾸次进⼊缓存页⾯：beforeRouteEnter --> created --> mounted --> activated --> deactivated

> 再次进⼊缓存页⾯：beforeRouteEnter --> activated --> deactivated
