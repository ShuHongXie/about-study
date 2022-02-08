/*
 * @Author: 谢树宏
 * @Date: 2022-02-08 16:27:55
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-08 16:53:48
 * @FilePath: /about-study/算法/insertSort.js
 */
const arr = [3, 5, 4, 1, 2, 6];

// 插入排序 后一个前一个不断对比
for (let i = 0; i < arr.length - 1; i++) {
  let value = arr[i];
  let j = i - 1;
  for (; j >= 0; --j) {
    if (arr[j] > value) {
      arr[j + 1] = arr[j];
    } else {
      break;
    }
  }
  arr[j + 1] = value;
}

console.log(arr);

// 选择排序  两端对比
