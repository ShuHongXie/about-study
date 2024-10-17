## 区别

WeakMap 和 WeakSet 内部的值是弱引用 只要该值没有被外部的其他常量或变量所引用，那该值就会自动被垃圾回收

Set 和 Map 是强引用，内部的对象和数组会一直引用着，只要当前对象不为 null，就不会被垃圾回收

## Reflect 作用

1. Reflect 反射对象，在 Vue3 源码中主要是为了弥补对象代理，如 Object.definedProperty 或 Proxy 对一个不可写且不可配置的属性进行 getter 或 setter 时会抛出 TypeError，Reflect 则不会
2. this 指向问题，代理对象返回的 this 是 proxy，而不是原本

```js
const obj = { name: "鲨鱼辣椒" };
Object.defineProperty(obj, "age", {
  value: 25,
  writable: false,
  configurable: false,
});
console.log(obj.age); // 25
Object.defineProperty(obj, "age", {
  get() {
    return;
  },
});
console.log(obj.age); // TypeError
```

```js
const obj = { name: "鲨鱼辣椒" };
Object.defineProperty(obj, "age", {
  value: 25,
  writable: false,
  configurable: false,
});
console.log(obj.age); // 25
console.log(
  Reflect.defineProperty(obj, "age", {
    get() {
      return;
    },
  })
); // false
console.log(obj.age); // 25
```
