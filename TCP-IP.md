<!--
 * @Author: 谢树宏
 * @Date: 2022-02-25 15:43:15
 * @LastEditors: 谢树宏
 * @LastEditTime: 2022-02-25 16:04:53
 * @FilePath: /about-study/TCP-IP.md
-->

### 请求过程

当应用程序序用 TCP 传送数据时，数据会被送入一个协议栈中，从上到下经过每一层都会携带该层的首部信息，通过每一层后，最终会被当作一串比特流送入网络，这个比特流叫做帧（大小为 46-1500 字节之间）。

![](https://www.xiesmallxie.cn/20220225155805.png)

UDP 数据与 TCP 数据基本一致。唯一的不同是 UDP 传给 IP 的信息单元称作 UDP 数据报（UDP datagram），而且 UDP 的首部长为 8 字节
