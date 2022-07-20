// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

/*
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/

/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLongestSubstring = function (s) {
  var list = [];
  let num = 1;
  let start = 0;
  for (var i = 0, len = s.length; i < len; i++) {
    const initStr = s.substring(start, start + num);
    const cutStr = s.substring(start + num, s.length);
    const arr = initStr.split("");
    // console.log(initStr, cutStr);
    let flag = 0;
    if (cutStr.length) {
      arr.forEach((key, idx) => {
        let index = cutStr.indexOf(key);
        console.log(index, key, initStr, cutStr);
        if (index === 0) {
          start += idx + 1;
          flag++;
          num = 1;
          list.push(initStr.length);
        }
      });
    } else {
      list.push(initStr.length);
    }

    if (flag === 0) {
      num++;
    }
    if (i === len - 1) {
      list = list.length ? list : [s.length];
    }
    // console.log(list);
    if (!cutStr) break;
  }
  // console.log(list);
  return list.length ? Math.max.call(this, ...list) : list.length;
};

// console.log(lengthOfLongestSubstring("pwwkew"));
// console.log(lengthOfLongestSubstring("abcabcbb"));
// console.log(lengthOfLongestSubstring("bbb"));
console.log(lengthOfLongestSubstring("asdvd"));
// console.log(lengthOfLongestSubstring("aab"));
// console.log(lengthOfLongestSubstring(""));
// console.log(lengthOfLongestSubstring(" "));
// console.log(lengthOfLongestSubstring("dvdf"));
// console.log(" ".length);
