/*
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
*/

/*
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
示例 2：
输入：l1 = [0], l2 = [0]
输出：[0]
示例 3：
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
*/

// 两数相加

/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
// 数组表示
/*
var addTwoNumbers = function (l1, l2) {
  var maxArray = l1.length >= l2.length ? l1 : l2;
  var minArray = l1.length < l2.length ? l1 : l2;
  var result = [];
  var isOver = 0;
  for (var i = 0; i < maxArray.length; i++) {
    minArray[i] = minArray[i] || 0;
    result.push((minArray[i] + maxArray[i] + isOver) % 10);
    isOver = minArray[i] + maxArray[i] + isOver >= 10 ? 1 : 0;
    if (i === maxArray.length - 1 && isOver) {
      result.push(isOver);
    }
  }
  return result;
};

console.log(addTwoNumbers([9, 9, 9, 9, 9, 9, 9], [9, 9, 9, 9]));
console.log(addTwoNumbers([2, 4, 3], [5, 6, 4]));
console.log(addTwoNumbers([0], [0]));

 */

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
// 初始化链表
class ListNode {
  constructor(val, next) {
    this.val = val === undefined ? 0 : val;
    this.next = next === undefined ? null : next;
  }
}
const a1 = [9, 9, 9, 9, 9, 9, 9],
  a2 = [9, 9, 9, 9];
// 数组转链表
let l1, l2;
let next1, next2;
for (let i = 0; i < a1.length; i++) {
  if (!l1) {
    l1 = new ListNode(a1[i], null);
    next1 = l1;
  } else {
    let nextNode = new ListNode(a1[i], null);
    while (next1.next) {
      next1 = next1.next;
    }
    next1.next = nextNode;
  }
}
for (let i = 0; i < a2.length; i++) {
  if (!l2) {
    l2 = new ListNode(a2[i], null);
    next2 = l2;
  } else {
    let nextNode = new ListNode(a2[i], null);
    while (next2.next) {
      next2 = next2.next;
    }
    next2.next = nextNode;
  }
}
console.log(l1, l2);
// 开始计算
/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function (l1, l2) {
  var isOver = 0;
  var result;
  var next;
  while (l1 || l2) {
    // console.log("l1=", l1, "l2=", l2);
    l1 = l1 || new ListNode(0);
    l2 = l2 || new ListNode(0);
    // console.log("result", result);
    if (result) {
      // console.log((l1.val + l2.val + isOver) % 10);
      next.next = new ListNode((l1.val + l2.val + isOver) % 10);
      console.log(next.next.val);
      next = next.next;
      console.log(next);
    } else {
      result = new ListNode((l1.val + l2.val + isOver) % 10);
      next = result;
    }
    isOver = l1.val + l2.val + isOver >= 10 ? 1 : 0;
    l1 = l1.next;
    l2 = l2.next;
  }
  if (isOver) {
    next.next = new ListNode(isOver);
  }
  return result;
};

console.log(addTwoNumbers(l1, l2));
