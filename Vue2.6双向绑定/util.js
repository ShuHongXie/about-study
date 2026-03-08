/*
 * @Author: 谢树宏
 * @Date: 2021-10-28 10:24:10
 * @LastEditors: 谢树宏
 * @LastEditTime: 2021-10-28 16:55:27
 * @FilePath: /Vue2.6双向绑定/util.js
 */

const inBrowser = typeof window !== "undefined";

// 获取dom元素
const querySelector = (el) => document.querySelector(el);

// 判断是否是对象
const isObject = (val) => typeof val === "object";

// 判断是否是数组
const isArray = (arr) => Array.isArray(arr);

// 移除数组的某一项
const removeItem = (arr, item) => {
  if (arr.length) {
    const index = arr.indexOf(item);
    if (index > -1) {
      return arr.splice(index, 1);
    }
  }
};

// 判断当前值是否已定义
function isDef(val) {
  return val !== undefined && val !== null;
}

// 无效的函数
const noop = () => {};
