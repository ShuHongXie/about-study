/*
 * @Author: 谢树宏
 * @Date: 2021-10-28 09:46:04
 * @LastEditors: 谢树宏
 * @LastEditTime: 2021-10-28 19:46:34
 * @FilePath: /Vue2.6双向绑定/dep.js
 */

let uid = 0;

function remove(list, item) {
  const index = list.indexOf(item);
  list.splice(index, 1);
}

class Dep {
  constructor() {
    this.id = uid++;
    this.sub = [];
  }
  // 订阅所有依赖
  depend() {
    console.log(this);
    if (Dep.target) {
      console.log(Dep.target);
      Dep.target.addDep(this);
    }
  }

  addSub(watcher) {
    this.sub.push(watcher);
  }

  removeSub(watcher) {
    remove(this.sub, watcher);
  }

  notify() {
    console.log(this.sub);
    this.sub.forEach((watcher) => watcher.update());
  }
}

Dep.taget = null;

const targetStack = [];
// 赋值Dep.target主要是为了禁止某些getter依赖项触发到
// Dep.target有值时才能触发depend方法
function pushTarget(watcher) {
  console.log("推进watcher");
  Dep.target = watcher;
  targetStack.push(watcher);
  console.log(targetStack);
}

function popTarget() {
  console.log("清除watcher");
  targetStack.pop();
  Dep.target = targetStack[targetStack.length - 1];
}
