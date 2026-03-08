/*
 * @Author: 谢树宏
 * @Date: 2021-10-28 10:18:43
 * @LastEditors: 谢树宏
 * @LastEditTime: 2021-10-29 09:29:56
 * @FilePath: /Vue2.6双向绑定/compile.js
 */

// 是否是文本节点
const isTextNode = (node) => node.nodeType === 3;

// 是否是元素节点
const isElementNode = (node) => node.nodeType === 1;
// 模板匹配
const textReg = /\{\{(.*)\}\}/;

// 指令解析
const filterAttr = {
  // 是否是v-model指令
  isModel: (attr) => attr.localName.indexOf("v-model") !== -1,
  // 是否是事件
  isEvent: (attr) => attr.localName.indexOf("v-on") !== -1,
  // 是否是点击事件
  isClickEvent: (attr) =>
    attr.localName === "v-on:click" || attr.localName === "@click",
};

// 获取data里面的值
function getValue(vm, key) {
  const keyArray = key.split(".");
  let value = vm;
  keyArray.forEach((key) => {
    value = value[key];
  });
  return value;
}

// 设置data里面的值
function setValue(vm, key, newValue) {
  const keyArray = key.split(".");
  let value = vm;
  keyArray.forEach((key, index) => {
    if (index < keyArray.length - 1) {
      value = value[key];
    } else {
      console.log(value, key, newValue);
      value[key] = newValue;
    }
  });
}

const compileUtils = {
  text(vm, node, key) {
    node.textContent = getValue(vm, key);
  },
  input(vm, node, key) {
    // 获取值
    let value = getValue(vm, key);
    node.value = value;
    const updateFn = (e) => {
      console.log(e);
      setValue(vm, key, e.target.value);
    };
    node.removeEventListener("input", updateFn);
    node.addEventListener("input", updateFn);
  },
};

class Complie {
  constructor(vm, el) {
    this.el = el;
    this.vm = vm;
    this.init(el);
  }

  init(el) {
    el.childNodes.forEach((node) => {
      // 编译文本节点
      if (isTextNode && textReg.test(node.textContent)) {
        this.compileText(node, RegExp.$1.trim());
        // 编译标签元素节点
      } else if (isElementNode(node)) {
        this.compileElement(node);
      }
      if (node.childNodes.length) {
        this.init(node.childNodes);
      }
    });
  }

  compileText(node, key) {
    compileUtils.text(this.vm, node, key);
  }

  compileElement(node) {
    const { attributes } = node;
    for (const attr of attributes) {
      if (filterAttr.isModel(attr)) {
        node.removeAttribute(attr.localName);
        compileUtils.input(this.vm, node, attr.value);
      }
    }
  }

  parseContent() {}
}
