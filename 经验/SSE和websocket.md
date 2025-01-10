### 前言

随着 chatgpt3，4 版本的推出，AI 应用的崛起态势已非常明显，当我看到 AI 应用回答我提问的时候，我非常好奇 AI 应用是如何做到不卡的，毕竟有那么多文字，如果一个一个轮询的话效率会非常慢，需要频繁请求。于是我搜了搜相关技术，发现了 SSE 这个服务器主动推送的东西，这不免让我想到了 Websocket。那这两者有什么区别呢？

### **SSE 流式传输**

如标题所言，通过 SSE 流式传输的方式可以让我们不再通过轮询的方式获取服务端返回的结果，进而提升前端页面的性能。

对于需要轮询的业务场景来说，采用 SSE 确实是一个更好的技术方案。接下来，我将 SSE 的概念、与 Websocket 对比、SSE 应用场景多个方面介绍 SSE 流式传输

### 什么是 SSE 流式传输

SSE 全称为  **Server-sent events** , 是一种基于 HTTP 协议的通信技术，允许服务器主动向客户端（通常是 Web 浏览器）发送更新。

它是 HTML5 标准的一部分，设计初衷是用来建立一个单向的服务器到客户端连接，使得服务器可以实时地向客户端发送数据。

**这种服务端实时向客户端发送数据的传输方式，其实就是流式传输。**

因为我经常使用字节跳动的 AI 应用“豆包”的原因，可以发现豆包的响应总是间断完成。细扒豆包的网络传输模式，可以发现，用的也是流式传输。

![](https://blog-1300014307.cos.ap-guangzhou.myqcloud.com/202501101018558.png)

### SSE 流式传输的好处

在  **SSE**  技术出现之前，我们习惯把需要等待服务端返回的过程称为长轮询。

长轮询的实现其实也是借助 http 请求来完成，一个完整的长轮询过程如下图所示：

![](https://blog-1300014307.cos.ap-guangzhou.myqcloud.com/202501101021822.png)

从图中可以发现，**长轮询最大的弊端是当服务端响应请求之前，客户端发送的所有请求都不会被受理。并且服务端发送响应的前提是客户端发起请求。**

前后端通信过程中，我们常采用 ajax 、axios 来异步获取结果，这个过程，其实也是长轮询的过程。

而同为采用 http 协议通信方式的 SSE 流式传输，相比于长轮询模式来说，优势在于可以在不需要客户端介入的情况下，多次向客户端发送响应，直至客户端关闭连接。

这对于需要服务端实时推送内容至客户端的场景可方便太多了！

### SSE 技术原理

###### 1\. 参数设置

前文说到，SSE 本质是一个基于 http 协议的通信技术。

因此想要使用  **SSE**  技术构建需要服务器实时推送信息到客户端的连接，只需要将传统的  **http 响应头的 contentType 设置为 text/event-stream** 。

并且为了保证客户端展示的是最新数据，需要将  **Cache-Control 设置为 no-cache** 。

在此基础上，**SSE**  本质是一个 TCP 连接，因此为了保证 SSE 的持续开启，需要将  **Connection 设置为 keep-alive** 。

```less
Content-Type: text/event-stream
Cache-Control: no-cache
Connection: keep-alive

```

完成了上述响应头的设置后，我们可以编写一个基于  **SSE**  流式传输的简单 Demo 。

###### 2\. SSE Demo

服务端代码：

```javascript
const express = require("express");
const app = express();
const PORT = 3000;

app.use(express.static("public"));

app.get("/events", function (req, res) {
  res.setHeader("Content-Type", "text/event-stream");
  res.setHeader("Cache-Control", "no-cache");
  res.setHeader("Connection", "keep-alive");

  let startTime = Date.now();

  const sendEvent = () => {
    // 检查是否已经发送了10秒
    if (Date.now() - startTime >= 10000) {
      res.write("event: close\ndata: {}\n\n"); // 发送一个特殊事件通知客户端关闭
      res.end(); // 关闭连接
      return;
    }

    const data = { message: "Hello World", timestamp: new Date() };
    res.write(`data: ${JSON.stringify(data)}\n\n`); // 每隔2秒发送一次消息

    setTimeout(sendEvent, 2000);
  };

  sendEvent();
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
```

客户端代码：

```xml
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>SSE Example</title>
</head>

<body>
    <h1>Server-Sent Events Example</h1>
    <div id="messages"></div>

    <script>
        const evtSource = new EventSource('/events');
        const messages = document.getElementById('messages');

        evtSource.onmessage = function(event) {
            const newElement = document.createElement("p");
            const eventObject = JSON.parse(event.data);
            newElement.textContent = "Message: " + eventObject.message + " at " + eventObject.timestamp;
            messages.appendChild(newElement);
        };
    </script>
</body>
</html>

```

当我们在浏览器中访问运行在 localhost: 3000 端口的客户端页面时，页面将会以  **流式模式**  逐步渲染服务端返回的结果

需要注意的是，为了保证使用  **SSE**  通信协议传输的数据能被客户端正确的接收，服务端和客户端在发送数据和接收数据应该遵循以下规范：

###### 服务端基本响应格式

**SSE**  响应主要由一系列以两个换行符分隔的事件组成。每个事件可以包含以下字段：

```kotlin
data：事件的数据。如果数据跨越多行，每行都应该以data:开始。
id：事件的唯一标识符。客户端可以使用这个ID来恢复事件流。
event：自定义事件类型。客户端可以根据不同的事件类型来执行不同的操作。
retry：建议的重新连接时间（毫秒）。如果连接中断，客户端将等待这段时间后尝试重新连接。

```

字段之间用单个换行符分隔，而事件之间用两个换行符分隔。

###### 客户端处理格式

客户端使用  **EventSource**  接口监听  **SSE**  消息：

```ini
const evtSource = new EventSource('path/to/sse');
evtSource.onmessage = function(event) {
    console.log(event.data); // 处理收到的数据
};

```

### SSE 应用场景

**SSE**  作为基于  **http**  协议由服务端向客户端单向推送消息的通信技术，对于需要服务端主动推送消息的场景来说，是非常适合的

1. AI 对话
2. 实时天气
3. 实时股票

### SSE 兼容性

![](https://blog-1300014307.cos.ap-guangzhou.myqcloud.com/202501101027256.png)

可以发现，目前市面上绝大多数浏览器都支持  **SSE**  通信。

### SSE 与 WebSocket 对比 h

看完 SSE 的使用方式后，细心的同学应该发现了：

**SSE**  的通信方式和  **WebSocket**  很像啊，而且 WebSocket 还支持双向通信，为什么不直接使用 WebSocket ？

对于这三者的详细区别，你可以参考下面我总结的表格：

以下是 WebSocket、轮询和 SSE 的对比表格：

| 特性           | WebSocket                                          | 轮询 Polling                                                                                                                                                                                                                                                                                                      | Server-Sent Events (SSE)                           |
| -------------- | -------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------- |
| **定义**       | 全双工通信协议，支持服务器和客户端之间的双向通信。 | 客户端定期向服务器发送请求以检查更新。                                                                                                                                                                                                                                                                            | 服务器向客户端推送数据的单向通信协议。             |
| **实时性**     | 高，服务器可以主动推送数据。                       | 低，依赖客户端定时请求。                                                                                                                                                                                                                                                                                          | 高，服务器可以主动推送数据。                       |
| **开销**       | 相对较高，需要建立和维护持久连接。                 | 较低，但频繁请求可能导致高网络和服务器开销。                                                                                                                                                                                                                                                                      | 相对较低，只需要一个 HTTP 连接，服务器推送数据。   |
| **浏览器支持** | 现代浏览器支持，需要额外的库来支持旧浏览器。       | 所有浏览器支持。                                                                                                                                                                                                                                                                                                  | 现代浏览器支持良好，旧浏览器可能需要 polyfill。    |
| **实现复杂性** | 高，需要处理连接的建立、维护和关闭。               | 低，只需定期发送请求。                                                                                                                                                                                                                                                                                            | 中等，只需要处理服务器推送的数据。                 |
| **数据格式**   | 支持二进制和文本数据。                             | 通常为 JSON 或 XML。                                                                                                                                                                                                                                                                                              | 仅支持文本数据，通常为 JSON。                      |
| **控制流**     | 客户端和服务器都可以控制消息发送。                 | 客户端控制请求发送频率。                                                                                                                                                                                                                                                                                          | 服务器完全控制数据推送。                           |
| **安全性**     | 需要 wss://（WebSocket Secure）来保证安全。        | 需要[https://来保证请求的安全。](https://link.juejin.cn?target=https%3A%2F%2F%25E6%259D%25A5%25E4%25BF%259D%25E8%25AF%2581%25E8%25AF%25B7%25E6%25B1%2582%25E7%259A%2584%25E5%25AE%2589%25E5%2585%25A8%25E3%2580%2582 "https://%E6%9D%A5%E4%BF%9D%E8%AF%81%E8%AF%B7%E6%B1%82%E7%9A%84%E5%AE%89%E5%85%A8%E3%80%82") | 需要 SSE 通过 HTTPS 提供，以保证数据传输的安全。   |
| **适用场景**   | 需要双向交互的应用，如聊天室、实时游戏。           | 适用于更新频率不高的场景，如轮询邮箱。                                                                                                                                                                                                                                                                            | 适用于服务器到客户端的单向数据流，如股票价格更新。 |
| **跨域限制**   | 默认不支持跨域，需要服务器配置 CORS。              | 默认不支持跨域，需要服务器配置 CORS。                                                                                                                                                                                                                                                                             | 默认不支持跨域，需要服务器配置 CORS。              |
| **重连机制**   | 客户端可以实现自动重连逻辑。                       | 需要客户端实现重连逻辑。                                                                                                                                                                                                                                                                                          | 客户端可以监听连接关闭并尝试重连。                 |
| **服务器资源** | 较高，因为需要维护持久连接。                       | 较低，但频繁的请求可能增加服务器负担。                                                                                                                                                                                                                                                                            | 较低，只需要维护一个 HTTP 连接。                   |

这个表格概括了 WebSocket、轮询和 SSE 在不同特性上的主要对比点。每种技术都有其适用的场景和限制，选择合适的技术需要根据具体的应用需求来决定。
可以发现，**SSE**  与  **WebSocket**  各有优缺点，对于需要客户端与服务端高频交互的场景，WebSocket 确实更适合；但对于只需要服务端单向数据传输的场景，**SSE 确实能耗更低，且不需要客户端感知**。
