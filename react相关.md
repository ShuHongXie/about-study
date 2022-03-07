<!--
 * @Author: 谢树宏
 * @Date: 2022-03-07 16:36:58
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-03-07 17:44:53
 * @FilePath: /about-study/react相关.md
-->

### 入门相关概念

1. 受控组件，当前组件的 state 由父级以上组件控制。
2. 不可变数据的力量，当进行代码优化时 如果直接修改源数据，那么在 shouldCompoentUpdate 阶段，新旧的 state 或 props 可能一致当时没有更新。
   官方例子：https://react.docschina.org/docs/optimizing-performance.html#examples
3. pureCompoent 优化相关介绍：https://juejin.cn/post/6844904094021206024
