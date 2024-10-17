/*
 * @Author: 谢树宏
 * @Date: 2022-02-08 16:54:58
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-08 17:30:38
 * @FilePath: /about-study/算法/mergeSort.js
 */
const arr = [5, 4, 3, 1, 2, 6];

// 归并排序 分而治之思想 复杂度O(nlogn)
function mergeSort(arr) {
  let len = arr.length;
  if (len < 2) {
    return arr;
  }
  let middle = Math.floor(len / 2),
    left = arr.slice(0, middle),
    right = arr.slice(middle);
  return merge(mergeSort(left), mergeSort(right));
}
function merge(left, right) {
  let result = [];
  console.log(left, right);
  while (left.length > 0 && right.length > 0) {
    if (left[0] <= right[0]) {
      result.push(left.shift());
    } else {
      result.push(right.shift());
    }
  }
  while (left.length) result.push(left.shift());
  while (right.length) result.push(right.shift());
  return result;
}

console.log(mergeSort(arr));
