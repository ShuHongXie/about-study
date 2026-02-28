<!--
 * @Author: 谢树宏
 * @Date: 2022-02-14 14:40:22
 * @LastEditors: 谢树宏 384180258@qq.com
 * @LastEditTime: 2023-06-08
 * @FilePath: /about-study/ES6.md
-->

### let 和 const 对比 var


1. 新增了块级作用域
2. let const 未定义前使用会报错，这就是暂时性死区
3. let const 不允许重复声明
4. let和const不存在变量提升，var存在
5. const一旦声明就无法进行重复更改

### 箭头函数

1. 箭头函数没有自己的this, 它从作用域的上一层继承this
2. 箭头函数不能作为构造函数
3. 没有arguments，prototype