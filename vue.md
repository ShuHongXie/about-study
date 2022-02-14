<!--
 * @Author: 谢树宏
 * @Date: 2022-02-14 14:02:43
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-14 14:02:43
 * @FilePath: /about-study/vue.md
-->

### vue-router 路由守卫触发方式

从外到内

初始化：全局 beforeEach -> 组件挂载参数的 beforeEnter -> 组件内 beforeRouteEnter -> 全局 router.afterEach -> 传统生命周期(beforeCreate.....)

离开时: beforeRouteLeave -> beforeEach -> afterEach

### diff 算法

1. 定义四个指针，如果新旧两个数据的两端指针交错，就说明对比完成
2. 首先对比旧新开始节点，再对比旧新结束节点，再对比旧开始和新结束，在对比旧结束和新开始
3. 上面 4 组对比如果没有出结果下面会衍生会 2 种情况

4. 新旧的在没有绑定 key 的情况下，会去旧的列表里面找看看有没有跟当前 newVnode 相同的元素，如果没有就在旧的前面插入当前 newVnode。如果旧列表里面有当前元素，会拿当前 newVnode 和旧列表中的相同元素做对比，如果相同，就会在当前 oldStartIndex 前插入 newVnode，旧的相同元素置为 undefined, 如果不同，也会在当前 oldStartIndex 前插入 newVnode。同时下标前进一位

5. 当下标不断收缩时，如果旧开始标位大于旧结束标为时，说明旧的已经对比完成了,如
