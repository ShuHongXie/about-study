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
  let start = 0;
  let arr = [];
  let str = "";
  for (let i = 0, len = s.length; i < len; i++) {
    str = s[i];
    for (let j = i + 1; j < len; j++) {
      if (str.indexOf(s[j]) !== -1 || j < arr.length) {
        break;
      }
      if (s[i] === s[j]) {
        break;
      } else {
        str += s[j];
      }
    }
    // console.log(str);
    arr.push(str.length);
    str = "";
  }
  return arr.length ? Math.max.call(this, ...arr) : arr.length;
};

console.log(lengthOfLongestSubstring("pwwkew"));
console.log(lengthOfLongestSubstring("abcabcbb"));
console.log(lengthOfLongestSubstring("bbb"));
console.log(lengthOfLongestSubstring("pwwkew"));
console.log(lengthOfLongestSubstring("aab"));
console.log(lengthOfLongestSubstring(""));
console.log(lengthOfLongestSubstring(" "));
console.log(lengthOfLongestSubstring("dvdf"));
console.log(" ".length);
