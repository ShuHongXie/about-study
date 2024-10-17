/*
 * @Author: 谢树宏
 * @Date: 2022-03-02 16:52:37
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-03-02 16:55:40
 * @FilePath: /about-study/设计模式/iterator.js
 */
var iteratorUploadObj = function () {
  for (var i = 0, fn; (fn = arguments[i++]); ) {
    var uploadObj = fn();
    if (uploadObj !== false) {
      return uploadObj;
    }
  }
};
