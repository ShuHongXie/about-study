<!--
 * @Author: 谢树宏
 * @Date: 2022-02-14 14:02:43
 * @LastEditors: chl123-eng 1326090238@qq.com
 * @LastEditTime: 2023-04-10 17:08:44
 * @FilePath: /about-study/vue.md
-->

### vue-router 路由守卫触发方式

从外到内

初始化：全局 beforeEach -> 组件挂载参数的 beforeEnter -> 组件内 beforeRouteEnter -> 全局 router.afterEach -> 传统生命周期(beforeCreate.....)

离开时: beforeRouteLeave -> beforeEach -> afterEach

### 依赖收集

把数据传入 data 之中，vue 用 object.definedProperty 遍历属性，转换成 getter 和 setter，每个属性都配置一个消息订阅器 dep。当 render 函数渲染时，会读取到当前的属性，触发属性上 dep 的 depend 方法，把当前的 dep 当如 watcher 的 depList 里面，同时 dep 也把当前 watcher 加入内部的 watcher 队列，当属性更新时调用 dep 内部 watcher 队列里面每一个 watcher 的 update 方法,重新执行一遍 render 更新 dom

computed 内部实际上也是执行了一个 lazy 形式的 watcher，当配置一个 computed 时，同样会用 object.definedProperty 遍历属性，当 getter 获取时会调用 get 方法把依赖项的 dep 加入当前 watcher 中，把当前 wathcer 加入 dep 的 watcher 队列里面，更新 watcher 的 value 值，返回 value。当依赖项更新是，当前 computed 的 watcher 会被调用，因为是 lazy，所以不进行主动计算，因为依赖项更新时会引起 render 的重新刷新，会重新拿到 computed 的值，自动进行更新

watch 内部也是创建了一个 watcher 实例，只不过 get 方法在调用时返回了监测内容，当监测 computed 属性时，会将 computed 的 key 的所有依赖项的 dep 里面的 wathcer 队列加入当前 watcher，最后调用 run 时，如果前后数据不一致就直接调用 callback 方法

### diff 算法

1. 定义四个指针，如果新旧两个数据的两端指针交错，就说明对比完成
2. 首先对比旧新开始节点，再对比旧新结束节点，再对比旧开始和新结束，在对比旧结束和新开始
3. 上面 4 组对比如果没有出结果下面会衍生会 2 种情况

4. 新旧的在没有绑定 key 的情况下，会去旧的列表里面找看看有没有跟当前 newVnode 相同的元素，如果没有就在旧的前面插入当前 newVnode。如果旧列表里面有当前元素，会拿当前 newVnode 和旧列表中的相同元素做对比，如果相同，就会在当前 oldStartIndex 前插入 newVnode，旧的相同元素置为 undefined, 如果不同，也会在当前 oldStartIndex 前插入 newVnode。同时下标前进一位

5. 当下标不断收缩时，如果旧开始标位大于旧结束标为时，说明旧的已经对比完成了,如增加新数据的 newStartIdx,newEndIdx 中的数据，如果新开始标位大于新结束标位，那说明有删除项，就把 oldStartIdx 到 oldEndIdx 之中的数据删除

“Vue Diff 中，当首尾双指针匹配不上时，会为新列表剩余节点构建 key 到索引的映射表。这个表的核心作用是将原本 O (n) 的遍历查找优化为 O (1) 的哈希查找，快速判断旧列表剩余节点是否存在于新列表中、以及在新列表的位置，从而高效决定节点是删除、复用还是移动，这也是 Vue Diff 高效的关键优化点。”

### 虚拟相关

> 正常⽣命周期：beforeRouteEnter --> created --> mounted --> updated -->destroyed

使⽤ keepAlive 后⽣命周期：

> ⾸次进⼊缓存页⾯：beforeRouteEnter --> created --> mounted --> activated --> deactivated

> 再次进⼊缓存页⾯：beforeRouteEnter --> activated --> deactivated

### Vue3 优化点

1. proxy替换object.defineProperty
1. 静态标记：v2 版本 diff 是全量对比，v3 只对有 patchFlag 的节点进行 diff 对比
1. 静态提升：对不变的 dom 打标记，减少渲染成本
1. 事件监听缓存：对绑定的事件进行监听缓存
1. SSR 服务端渲染：Vue 3.0 会将静态标签直接转化为文本，相比 React 先将 jsx 转化为虚拟 DOM，再将虚拟 DOM 转化为 HTML，Vue3 更方便快捷


### vue和react

第一层：先讲核心设计理念（定调，体现底层认知）
“React 和 Vue 的核心差异源于设计理念不同：
React 是「函数式编程」思想，强调「单向数据流」「状态不可变」，通过 JSX 将视图和逻辑完全融合，更侧重 “用代码的方式描述 UI”；
Vue 是「渐进式框架」，兼顾「响应式编程」和「模板化」，提供模板语法 + 选项式 API，更贴近传统前端开发习惯，上手成本更低。
这一理念差异，直接导致两者在语法、响应式、Diff 等层面的不同。”
第二层：分核心维度对比（抓重点，不贪多，选 4-5 个核心维度）
维度	React 核心特点	Vue 核心特点
语法 / 模板	纯 JSX 编写（HTML 融入 JS），灵活度高，需手写更多逻辑（如条件 / 循环）	模板语法（HTML 为主）+ 指令（v-if/v-for），更直观，内置常用功能减少手写
响应式原理	基于「状态更新触发重新渲染」（setState/useState 触发重渲染），需手动优化（memo/useMemo）	Vue2 基于 Object.defineProperty，Vue3 基于 Proxy，自动依赖收集，精准更新变化节点
Diff 算法	同层顺序遍历 + key 映射，无首尾双指针优化	首尾双指针前置匹配 + key 映射，列表对比更高效，减少遍历次数
组件复用	以 Hooks（useState/useEffect 等）为核心，函数组件复用逻辑	支持 Options API（选项式）和 Composition API，Mixin / 组合式函数均可复用逻辑
生态 / 定位	更偏向 “全栈框架”，生态庞大（Next.js/Remix），适合大型复杂应用	渐进式，可按需引入（核心库 + 路由 + 状态管理），中小项目落地更快
面试口语化表述（不用背表格，按维度说）：
“具体来看，几个核心差异：
语法上：React 用 JSX 把 HTML 写在 JS 里，灵活但需要手写循环 / 条件；Vue 是模板语法 + 指令，更贴近 HTML，比如 v-for/v-if 直接用，不用像 React 那样写 map / 三元表达式；
响应式：React 是状态变了就触发组件重渲染，需要用 memo、useMemo 避免不必要更新；Vue 是自动收集依赖，只更新变化的节点，比如修改一个数据，只有用到这个数据的 DOM 会更更新；
Diff 算法：两者都遵循同层对比，但 Vue 多了首尾双指针优化，比如列表 abcd 变 ebca 时，Vue 会先匹配 b、c，再处理 a、d、e，比 React 纯顺序遍历更高效；
上手和生态：Vue 渐进式，学一点用一点，中小项目快；React 灵活度高，适合大型复杂应用，生态更全（比如 Next.js 做服务端渲染很成熟）。”
第三层：补充场景化选择（体现落地思考，加分项）
“没有绝对的好坏，主要看场景：
中小项目、团队更熟悉传统前端开发 → 选 Vue，上手快、开发效率高；
大型复杂应用、需要强类型 / 跨端（React Native）→ 选 React，灵活度和生态更适配；
另外，Vue3 引入的 Composition API 也借鉴了 React Hooks 的思想，两者现在也在互相融合，核心是看团队技术栈和业务场景。”