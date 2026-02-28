<!--
 * @Author: 谢树宏
 * @Date: 2022-03-01 11:34:12
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-03-01 17:02:19
 * @FilePath: /about-study/js设计模式.md
-->

开闭原则：：当需要改变一个程序的功能或者给这个程序增加新功
能的时候，可以使用增加代码的方式，但是不允许改动程序的源代码

### 单例模式

单例模式的定义是：保证一个类仅有一个实例，并提供一个访问它的全局访问点

### 策略模式

多用于表单校验判断，代码复用，不用一个一个区判断

```js
// 维护权限列表
const jobList = ["FE", "BE"];

// 策略
var strategies = {
  checkRole: function (value) {
    return value === "juejin";
  },
  checkGrade: function (value) {
    return value >= 1;
  },
  checkJob: function (value) {
    return jobList.indexOf(value) > 1;
  },
  checkEatType: function (value) {
    return value === "eat melons";
  },
};

// 校验规则
var Validator = function () {
  this.cache = [];

  // 添加策略事件
  this.add = function (value, method) {
    this.cache.push(function () {
      return strategies[method](value);
    });
  };

  // 检查
  this.check = function () {
    for (let i = 0; i < this.cache.length; i++) {
      let valiFn = this.cache[i];
      var data = valiFn(); // 开始检查
      if (!data) {
        return false;
      }
    }
    return true;
  };
};
```

### 发布订阅模式

比如 dom 请求

### 装饰器模式

### 职责链模式
