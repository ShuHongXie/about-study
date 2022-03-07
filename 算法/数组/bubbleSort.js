/*
 * @Author: 谢树宏
 * @Date: 2022-02-08 11:47:57
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-08 11:55:06
 * @FilePath: /about-study/算法/bubbleSort.js
 */
const arr = [3, 5, 4, 1, 2, 6];

// 冒泡排序
for (let i = 0; i < arr.length - 1; i++) {
  for (let j = 0; j < arr.length - i - 1; j++) {
    if (arr[j] > arr[j + 1]) {
      const num = arr[j];
      arr[j] = arr[j + 1];
      arr[j + 1] = num;
      console.log(arr);
    }
  }
}

console.log(arr);
