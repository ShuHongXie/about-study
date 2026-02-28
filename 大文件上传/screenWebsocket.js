class ScreenWebSocket {
  /**
   * 初始化 WebSocket 连接
   * @param {string} url - WebSocket 服务端地址（如 ws://localhost:8080/ws）
   * @param {Object} options - 配置项
   * @param {number} options.heartbeatInterval - 心跳检测间隔（ms），默认5000
   * @param {number} options.reconnectInterval - 重连间隔（ms），默认3000
   * @param {number} options.throttleTime - 消息节流时间（ms），默认100
   * @param {Function} options.onMessage - 接收消息的回调
   * @param {Function} options.onStatusChange - 连接状态变化的回调
   */
  constructor(url, options = {}) {
    // 基础配置
    this.url = url;
    this.heartbeatInterval = options.heartbeatInterval || 5000; // 5秒一次心跳
    this.reconnectInterval = options.reconnectInterval || 3000; // 3秒重连一次
    this.throttleTime = options.throttleTime || 100; // 100ms内最多处理1条消息
    this.onMessage = options.onMessage || (() => {});
    this.onStatusChange = options.onStatusChange || (() => {});

    // 状态管理
    this.ws = null; // WebSocket 实例
    this.isConnected = false; // 是否已连接
    this.heartbeatTimer = null; // 心跳定时器
    this.reconnectTimer = null; // 重连定时器
    this.lastMessageTime = 0; // 最后一次接收消息的时间（节流用）

    // 初始化连接
    this.connect();
  }

  /**
   * 1. 建立 WebSocket 连接
   */
  connect() {
    // 清除旧的定时器
    this.clearTimers();

    try {
      // 创建 WebSocket 实例
      this.ws = new WebSocket(this.url);
      this.onStatusChange("connecting", "正在连接...");

      // 连接成功回调
      this.ws.onopen = () => {
        this.isConnected = true;
        this.onStatusChange("connected", "连接成功");
        // 启动心跳检测
        this.startHeartbeat();
      };

      // 接收消息回调（带节流）
      this.ws.onmessage = (event) => {
        const now = Date.now();
        // 节流：如果距离上次处理消息不足 throttleTime，直接忽略
        if (now - this.lastMessageTime < this.throttleTime) return;

        this.lastMessageTime = now;
        // 解析消息（大屏数据通常是JSON格式）
        let data = {};
        try {
          data = JSON.parse(event.data);
        } catch (e) {
          console.error("消息解析失败:", e);
          return;
        }
        // 触发外部回调，把数据传给大屏渲染逻辑
        this.onMessage(data);
      };

      // 连接关闭回调
      this.ws.onclose = (event) => {
        if (event.code === 1000) {
          // 1000是正常关闭，不重连
          this.onStatusChange("closed", "连接正常关闭");
        } else {
          // 异常关闭，触发重连
          this.isConnected = false;
          this.onStatusChange(
            "disconnected",
            `连接断开（${event.code}），准备重连...`,
          );
          this.startReconnect();
        }
      };

      // 连接错误回调
      this.ws.onerror = (error) => {
        console.error("WebSocket 错误:", error);
        this.isConnected = false;
        this.onStatusChange("error", "连接出错，准备重连...");
        this.startReconnect();
      };
    } catch (e) {
      console.error("创建连接失败:", e);
      this.onStatusChange("error", "创建连接失败");
      this.startReconnect();
    }
  }

  /**
   * 2. 启动心跳检测（保活+检测假连接）
   */
  startHeartbeat() {
    this.heartbeatTimer = setInterval(() => {
      if (!this.isConnected) return;

      try {
        // 发送心跳包（格式和服务端约定，通常是 {type: 'heartbeat'}）
        this.ws.send(
          JSON.stringify({ type: "heartbeat", timestamp: Date.now() }),
        );
      } catch (e) {
        // 发送心跳失败，说明连接已断
        console.error("心跳发送失败:", e);
        this.isConnected = false;
        this.onStatusChange("heartbeat_fail", "心跳检测失败，准备重连...");
        this.startReconnect();
      }
    }, this.heartbeatInterval);
  }

  /**
   * 3. 启动断线重连
   */
  startReconnect() {
    // 如果已经在重连，直接返回
    if (this.reconnectTimer) return;

    this.reconnectTimer = setInterval(() => {
      if (this.isConnected) {
        this.clearTimers();
        return;
      }
      // 尝试重新连接
      this.connect();
    }, this.reconnectInterval);
  }

  /**
   * 辅助：清除所有定时器
   */
  clearTimers() {
    if (this.heartbeatTimer) clearInterval(this.heartbeatTimer);
    if (this.reconnectTimer) clearInterval(this.reconnectTimer);
    this.heartbeatTimer = null;
    this.reconnectTimer = null;
  }

  /**
   * 发送消息到服务端（大屏主动发消息用，比如请求初始数据）
   * @param {Object} data - 要发送的数据
   */
  send(data) {
    if (!this.isConnected || !this.ws) {
      this.onStatusChange("send_fail", "连接未建立，发送失败");
      return false;
    }

    try {
      this.ws.send(JSON.stringify(data));
      return true;
    } catch (e) {
      console.error("发送消息失败:", e);
      this.onStatusChange("send_fail", "发送消息失败");
      return false;
    }
  }

  /**
   * 手动关闭连接（比如页面销毁时）
   */
  close() {
    this.clearTimers();
    if (this.ws) {
      this.ws.close(1000, "手动关闭"); // 1000表示正常关闭
    }
    this.isConnected = false;
    this.onStatusChange("closed", "已手动关闭连接");
  }
}
