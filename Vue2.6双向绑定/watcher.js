/*
 * @Author: 谢树宏
 * @Date: 2021-10-28 09:46:01
 * @LastEditors: chl123-eng 1326090238@qq.com
 * @LastEditTime: 2024-07-18 21:59:11
 * @FilePath: /Vue2.6双向绑定/watcher.js
 */

// 一个key生成一个dep订阅，在watcher里面维护一个dep订阅的队列，
// 如果当前watcher里面的dep队列里面不存在这个东西，那就把当前watcher
// 加入dep的sub队列 表示要进行更新

let id = 0;

// 获取data里面的值
function createExpOrFn(vm, key) {
  console.log(key);
  return function () {
    const keyArray = key.split(".");
    let value = vm;
    keyArray.forEach((key) => {
      value = value[key];
    });
    return value;
  };
}

class Watcher {
  constructor(vm, expOrFn, cb, options) {
    this.id = ++id;
    this.vm = vm;
    this.expOrFn = expOrFn;
    this.cb = cb;
    this.lazy = options.lazy || false;
    this.dirty = options.lazy || false;
    // 新旧队列
    this.newDepIdList = [];
    this.depIdList = [];
    this.newDepList = new Set();
    this.depList = new Set();
    console.log(expOrFn);
    this.getter =
      typeof this.expOrFn === "function"
        ? this.expOrFn
        : createExpOrFn(this.vm, this.expOrFn);
    console.log(this.getter);
    this.value = this.lazy ? "" : this.get();
  }

  addDep(dep) {
    // 收集最新的依赖
    if (!this.newDepIdList.includes(dep.id)) {
      this.newDepIdList.push(dep.id);
      this.newDepList.add(dep);
      // 如果队列里面没有
      if (!this.depIdList.includes(dep.id)) {
        dep.addSub(this);
      }
    }
    console.log(dep);
  }
  // 单纯获取最新的值
  get() {
    let value;
    try {
      pushTarget(this);
      value = this.getter.call(this.vm);
    } catch (e) {
    } finally {
      this.cleanDepQueue();
      popTarget();
      console.log("清除了", value, this.getter);
    }
    return value;
  }
  // 更新
  update() {
    if (this.lazy) {
      this.dirty = true;
    } else {
      queueWatcher(this);
    }
  }

  run() {
    console.log("更新了");
    const value = this.get();
    if (value !== this.value) {
      const oldValue = this.value;
      this.cb.call(this.vm, value, oldValue);
      this.value = value;
    }
  }

  depend() {
    console.log("-xxx");
    for (const dep of this.depList) {
      dep.depend();
    }
  }

  cleanDepQueue() {
    // 收集了新的依赖 如果新的依赖里面没有旧的 那就从旧的依赖里面去掉
    // 试想一下 页面的绑定了一个值,并且设置了一个v-if指令，在下一次渲染之后，
    //         v-if="false"不渲染了 但是上一个的依赖却已经被追踪了

    for (const dep of this.depList) {
      if (!this.newDepList.has(dep)) {
        dep.removeSub(this);
      }
    }
    // 新的赋值给旧的  清空新依赖列表 新旧对比
    let current = this.depList;
    this.depList = this.newDepList;
    this.newDepList = current;
    this.newDepList.clear();

    current = this.depIdList;
    this.depIdList = this.newDepIdList;
    this.newDepIdList = current;
    this.newDepIdList.length = 0;
  }

  excuteLazy() {
    this.dirty = false;
    this.value = this.get();
  }
}
