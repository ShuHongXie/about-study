<!--
 * @Author: 谢树宏
 * @Date: 2022-05-12 16:09:47
 * @LastEditors: 谢树宏 384180258@qq.com
 * @LastEditTime: 2022-06-14
 * @FilePath: /about-study/Lerna.md
-->

### 一些概念

Multirepo：多库。传统的按照职责划分为多个代码仓库进行管理
Monorepo：单裤。要求我们只用一个代码仓库来管理一个大项目的所有资源、子项目

### 简介 lerna 管理 monorepo 问题

将大型代码库库拆分为独立版本的包对代码共享有很大的帮助，但是多个分开的代码库会变得难以追踪，跨存储库之间的测试会变得非常麻烦，Lerna 旨在解决这种问题。

### 创建仓库

lerna create 包名称 包地址

```js
lerna create cli packages/@fat
```

### 增加包

lerna add <package>[@version] [--dev] [--exact] [--peer]

1. --dev：只安装在 devDependencies

```js
// Adds the module-1 package to the packages in the 'prefix-' prefixed folders
lerna add module-1 packages/prefix-*

// Install module-1 to module-2
lerna add module-1 --scope=module-2

// Install module-1 to module-2 in devDependencies
lerna add module-1 --scope=module-2 --dev

// Install module-1 to module-2 in peerDependencies
lerna add module-1 --scope=module-2 --peer

// Install module-1 in all modules except module-1
lerna add module-1

// Install babel-core in all modules
lerna add babel-core
```

### 链接本地的包 重新下载依赖

lerna bootstrap

### 查看当前包下面仓库

lerna ls 查看简略的包信息
lerna ll 查看具体包信息，包括版本号，路径等

### 查看当前包差异

lerna diff

### 发布 lerna 包

lerna publish --canary
然后进入子包 npm publish
