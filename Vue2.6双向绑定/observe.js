/*
 * @Author: 谢树宏
 * @Date: 2021-10-28 09:45:52
 * @LastEditors: chl123-eng 1326090238@qq.com
 * @LastEditTime: 2024-07-18 21:54:24
 * @FilePath: /Vue2.6双向绑定/observe.js
 */
function observe(data) {
  let ob;
  if (isObject(data)) {
    new Observer(data);
  }
  return ob;
}

class Observer {
  constructor(data) {
    const dep = new Dep();
    if (Array.isArray(data)) {
    } else {
      this.walk(data);
    }
  }

  walk(data) {
    const keyList = Object.keys(data);
    for (let i = 0; i < keyList.length; i++) {
      defineReactive(data, keyList[i]);
    }
  }
}

function defineReactive(data, key, value) {
  const dep = new Dep();
  // 没有传value时默认初始化value
  if (arguments.length === 2) {
    value = data[key];
  }
  // 遍历子项
  let child = observe(data[key]);
  Object.defineProperty(data, key, {
    enumerable: true, // 可枚举
    configurable: false, // 不能再define
    get() {
      console.log("触发了getter", Dep.target);
      if (Dep.target) {
        dep.depend();
        if (child) {
          child.dep.depend();
        }
        // if (isArray(value)) {
        //   dependArray();
        // }
      }
      return value;
    },
    set(newValue) {
      console.log("触发了setter");
      if (newValue !== value) {
        value = newValue;
        child = observe(data[key]);
        dep.notify();
      }
    },
  });
}
