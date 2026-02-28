### 基础介绍

1. useCallback(fn, deps) ≈ useMemo(() => fn, deps)
2. useCallback返回函数
3. useMemo返回除函数外的其他类型
4. useRef返回可变的ref对象，其.current属性被初始化为传入的参数（initialValue）。返回的ref对象在组件的整个生命周期内保持不变。useRef() 和 useState() 的最大区别是 useRef() 不会触发组件重新渲染，而 useState() 会触发组件重新渲染。
5.

### watchEffect副作用

#### 主作用

根据 props + state → 计算出要渲染的 JSX → 画出页面

#### 副作用

副作用 = 不是为了渲染 UI、却在组件里做的「额外操作」，比如：

- 发请求（fetch /axios）
- 操作 DOM（focus、scroll、获取宽高、修改样式）
- 定时器（setTimeout /setInterval）
- 事件监听 / 订阅（addEventListener）
- 读写 localStorage /sessionStorage/cookie
- 操作外部变量、修改全局状态
- 日志上报、埋点

useEffect 做的事只有 3 个：

1. 把副作用 “收起来”，不让它乱执行
2. 控制执行时机（挂载？id 变？卸载？）
3. 提供清理机制（清除定时器、取消请求、移除监听）

#### 总结

主作用：只管画页面。
副作用：画页面之外，所有跟外界打交道的操作。
useEffect：专门管这些操作，不让它们乱执行。

### setState更新

```js
const handleClick = () => {
  setNumber(number + 5); // 第1次更新：直接值
  setNumber((n) => n + 1); // 第2次更新：函数式
  setNumber(number + 5); // 第3次更新：直接值
  setNumber(number + 5); // 第4次更新：直接值
};

/*
第 1 次：setNumber(number + 5) → 基于快照number=0，计算目标值5，队列记录「设为 5」；
第 2 次：setNumber(n => n + 1) → 函数式更新，队列记录「执行函数 n=>n+1」（暂不计算，等前一次结果）；
第 3 次：setNumber(number + 5) → 基于快照number=0，计算目标值5，队列记录「设为 5」；
第 4 次：setNumber(number + 5) → 基于快照number=0，计算目标值5，队列记录「设为 5」。
*/
```

```js
const handleClick = () => {
  setNumber(number + 5); // 第1次更新：直接值
  setNumber((n) => n + 1); // 第2次更新：函数式
  setNumber(number + 5); // 第3次更新：直接值
  setNumber(number + 6); // 第4次更新：直接值 最终为6
};
```

#### 直接值更新和函数式更新在 React 批处理机制下的执行逻辑差异。

1. 直接值更新：setNumber(number + 5); 基于快照
2. 函数式更新：基于上一个值setNumber(n => n + 1);

### React的更新过程

阶段 执行时机 核心操作 是否允许副作用

1. 渲染阶段（Reconciliation） 状态 / 属性变化后立即触发 执行组件函数（返回 JSX）、生成虚拟 DOM、计算 DOM 差异 ❌ 不允许（纯函数，无 DOM 操作 / 网络请求等）
2. 提交阶段（Commit） 渲染阶段完成后 更新真实 DOM（把虚拟 DOM 同步到页面） ✅ 仅允许 DOM 操作（但 React 推荐放副作用钩子）
3. 副作用阶段 提交阶段完成后 执行useEffect（异步）、useLayoutEffect（同步） ✅ 所有副作用（请求、监听、ref 更新等）
