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

function ListNode(val, next) {
  this.val = val === undefined ? 0 : val;
  this.next = next === undefined ? null : next;
}
