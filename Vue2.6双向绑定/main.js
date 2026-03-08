/*
 * @Author: 谢树宏
 * @Date: 2021-10-28 09:46:28
 * @LastEditors: chl123-eng 1326090238@qq.com
 * @LastEditTime: 2024-07-18 21:59:52
 * @FilePath: /Vue2.6双向绑定/main.js
 */

// 数据获取
function getData(data, vm) {
  return data.call(vm, vm);
}

// 挂载
function mountComponent(el, vm) {
  vm.$el = el;
  const updateComponent = () => {
    vm.render();
  };
  new Watcher(vm, updateComponent, noop, {});
}

function definedComputed(vm, obj, key) {
  console.log(vm, obj, key);
  const computedObj = {
    get: function () {
      const watcher = vm._computedWatchers[key];
      console.log("???", watcher);
      if (watcher.dirty) {
        value = watcher.excuteLazy();
      }
      console.log(Dep.target);
      // 加入当前依赖
      if (Dep.target) {
        watcher.depend();
      }
      return watcher.value;
    },
    set: typeof obj[key] === "function" ? noop : obj[key].set,
  };
  Object.defineProperty(vm, key, {
    enumerable: true, // 可枚举
    configurable: false, // 不能再define
    ...computedObj,
  });
  // for(const watcher of watcherList) {
  //   watcher.excuteLazy()
  // }
}

// Vue实例
function Vue(options) {
  this.options = options;
  this._init();
}
installHelp(Vue.prototype);
Vue.prototype._init = function () {
  const vm = this;
  // 初始化data
  let { data, el, computed, watch } = vm.options;
  if (data) {
    data = vm._data = typeof data === "function" ? getData(data, vm) : data;
    // 把所有key代理到this
    const keys = Object.keys(data);
    let i = keys.length;
    while (i--) {
      const key = keys[i];
      Object.defineProperty(vm, key, {
        configurable: false,
        enumerable: true,
        get() {
          return vm._data[key];
        },
        set(val) {
          vm._data[key] = val;
        },
      });
    }
    // 订阅所有属性
    observe(data);
  }
  // 初始化计算属性
  if (computed) {
    const watcherList = (vm._computedWatchers = {});
    for (const key in computed) {
      const get =
        typeof computed[key] === "function" ? computed[key] : computed[key].get;
      watcherList[key] = new Watcher(vm, get, noop, { lazy: true });
      definedComputed(vm, computed, key);
    }
  }
  // 初始化watch监听
  if (watch) {
    for (const key in watch) {
      new Watcher(vm, key, watch[key], {});
    }
  }
  // // 挂载dom
  if (el) {
    el = typeof el === "string" ? querySelector(el) : el;
    mountComponent(el, vm);
  }
};

// 新旧对比更新
Vue.prototype._update = function (el) {
  const vm = this;
  const prevEl = vm.$el; // mountComponent方法第一行里面挂载的
  const prevVnode = vm._vnode; // 初始化init阶段为空 更新阶段被赋值为当前实例的vnode

  // this._vnode = vnode;
  // if (!prevVnode) {
  //   vm.$el = vm.patch(vm.$el);
  // } else {
  //   // updates更新时进入
  //   vm.$el = vm.patch(prevVnode, vnode);
  // }
};

Vue.prototype._c = function (tag, data, children) {
  return new VNode(tag, data, children, undefined, undefined, this);
};

Vue.prototype.formatVnode = function (vnode, el, parent) {
  vnode.elm = el;
  const elm = el;
  if (vnode.data) {
    if (vnode.data.attrs) {
      for (const key in vnode.data.attrs) {
        elm.setAttribute(key, vnode.data.attrs[key]);
      }
    }
    if (vnode.data.on && vnode.data.on.input) {
      elm.removeEventListener("input", vnode.data.on.input);
      elm.addEventListener("input", vnode.data.on.input);
      elm.value = vnode.data.domProps.value;
    }
    if (Array.isArray(vnode.data)) {
      elm.innerText = vnode.data[0].text;
    }
  }
  if (vnode.children) {
    for (const child of vnode.children) {
      for (const childNode of elm.childNodes) {
        if (child.tag === childNode.localName) {
          this.formatVnode(child, childNode, elm);
        }
      }
    }
  }
  return elm;
};

Vue.prototype.render = function () {
  const vnode = render.call(this);
  // this.$el.parentNode.innerHTML = "";
  this.formatVnode(vnode, this.$el, this.$el.parentNode);
  return vnode;
};

Vue.prototype.patch = initPatch();
