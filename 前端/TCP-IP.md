<!--
 * @Author: 谢树宏
 * @Date: 2022-02-25 15:43:15
 * @LastEditors: 谢树宏 384180258@qq.com
 * @LastEditTime: 2022-07-21
 * @FilePath: /about-study/TCP-IP.md
-->

### 请求过程

当应用程序序用 TCP 传送数据时，数据会被送入一个协议栈中，从上到下经过每一层都会携带该层的首部信息，通过每一层后，最终会被当作一串比特流送入网络，这个比特流叫做帧（大小为 46-1500 字节之间）。

![](https://www.xiesmallxie.cn/20220225155805.png)

UDP 数据与 TCP 数据基本一致。唯一的不同是 UDP 传给 IP 的信息单元称作 UDP 数据报（UDP datagram），而且 UDP 的首部长为 8 字节

### TCP 和 UDP 的区别

**TCP**

1. TCP 是面向字节流的
2. TCP 面向可靠连接，保证传输的数据，无差错、不丢失、不重复、并且按序到达
3. TCP 是可以有拥塞控制的
4. TCP 其实是一个有状态服务

TCP 头内容
![](https://www.xiesmallxie.cn/20220721160316.png)

**UDP**

1. UDP 继承了 IP 包的特性，不保证不丢失，不保证按顺序到达
2. UDP 没有拥塞控制
