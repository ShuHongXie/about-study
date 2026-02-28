/**
 * @description: 顺序表查询 查找指定key的所在位置 a为数组 n为要童找的数组个数 key为要渣找的关键字
 * @param {*} a
 * @param {*} n
 * @param {*} key
 * @return {*}
 */

// 普通查找 复杂度 O(n)
function search1(a, n, key) {
  let i;
  for (i = 0; i < n; i++) {
    if (a[i] === key) {
      return i;
    }
  }
}

console.log(search1([1, 4, 5, 6, 7, 9], 6, 6));

// 优化上面的例子 上面例子每次都要i<n 性能不够友好

// 大话数据结构里面的算法有bug 或者可能是因为语言原因，假如第一个刚好为
// key，那么在n的长度里面的是可以找到的，返回0不代表找不到

/**
function search2(a, n, key) {
  let i = n;
  // 设置一个哨兵 如果i = 0 那说明查找不到
  a[0] = key;
  while (a[i] !== key) {
    i--;
  }
  return i;
}

console.log(search2([1, 4, 5, 6, 7, 9], 6, 1));
 */

// 二分查找法 Olog(n) 只适合顺序表
console.log("search3开始");
function search3(a, n, key) {
  let min = 0;
  let max = n;
  while (min <= max) {
    mid = (max + min) / 2;
    console.log(mid);
    if (a[mid] < key) {
      min = mid + 1;
      console.log("min=", min);
    } else if (a[mid] > key) {
      max = mid - 1;
      console.log("max=", max);
    } else {
      return mid;
    }
  }
}

let arr3 = [1, 4, 5, 6, 7, 9, 19];
console.log("result:", search3(arr3, arr3.length - 1, 9));
