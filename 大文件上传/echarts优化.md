```js
echarts.init(dom, null, {
  renderer: "canvas", // Canvas渲染比SVG更省内存
  useDirtyRect: true, // 脏矩形渲染：只重绘变化的区域
  animation: false, // 高频更新关闭动画，减少渲染开销
});
```

### 分片加载

```js
/**
 * 分片加载核心逻辑（核心：利用浏览器空闲时间分批次渲染，不阻塞主线程）
 * @param rawData 原始海量数据
 * @param batchSize 每批次加载数量（建议500-1000）
 * @param frameRate 目标帧率（默认60fps）
 * @param updateChart 图表更新回调
 */
const loadDataByChunk = (
  rawData: any[],
  batchSize: number = 500,
  frameRate: number = 60,
  updateChart: (renderedData: any[]) => void
) => {
  let renderedData: any[] = []; // 已渲染数据
  let animationFrameId: number | null = null; // 动画帧ID（控制帧率）

  // 核心：分批次加载函数
  const loadChunk = (startIndex: number) => {
    // 计算当前批次结束索引
    const endIndex = Math.min(startIndex + batchSize, rawData.length);
    // 截取当前批次数据
    const chunk = rawData.slice(startIndex, endIndex);
    // 合并已渲染数据
    renderedData = [...renderedData, ...chunk];

    // 更新图表（核心：将分片数据传给渲染逻辑）
    updateChart(renderedData);

    // 还有数据未加载，继续分片
    if (endIndex < rawData.length) {
      // 控制帧率：根据目标帧率计算渲染延迟（1000ms / 帧率 = 每帧间隔）
      const frameDelay = Math.floor(1000 / frameRate);

      // 用requestAnimationFrame保证帧率稳定
      animationFrameId = requestAnimationFrame(() => {
        // 用requestIdleCallback利用浏览器空闲时间加载，避免阻塞主线程
        requestIdleCallback(
          () => loadChunk(endIndex),
          { timeout: 100 } // 超时100ms强制执行，避免等待过久
        );
      });
    }
  };

  // 启动第一批次加载
  loadChunk(0);

  // 返回清理函数（防止内存泄漏）
  return () => {
    if (animationFrameId) cancelAnimationFrame(animationFrameId);
  };
};
```

### 帧率优化

```js
import * as echarts from 'echarts';

/**
 * 初始化带帧率优化的ECharts实例（核心配置）
 * @param domId 图表容器ID
 * @returns ECharts实例 + 销毁函数
 */
const initEchartsWithFpsOpt = (domId: string) => {
  const dom = document.getElementById(domId);
  if (!dom) throw new Error(`容器${domId}不存在`);

  // 核心：ECharts帧率优化配置（重中之重）
  const chartInstance = echarts.init(dom, null, {
    renderer: 'canvas', // 优先Canvas渲染（比SVG快5-10倍）
    useDirtyRect: true, // 脏矩形渲染：仅重绘变化区域（帧率提升30%+）
    devicePixelRatio: window.devicePixelRatio || 1, // 适配高清屏
    animation: false, // 禁用动画（高频更新必关，帧率提升最明显）
    animationThreshold: 2000, // 数据量超2000时强制禁用动画
  });

  // 图表基础配置（帧率优化相关）
  const baseOption = {
    xAxis: {
      type: 'category',
      axisLabel: { show: false }, // 隐藏标签减少渲染压力
      splitLine: { show: false },
    },
    yAxis: { type: 'value' },
    series: [
      {
        type: 'line',
        symbol: 'none', // 隐藏数据点（减少绘制指令）
        sampling: 'lttb', // 大数据采样：保留趋势，减少渲染点数
        large: true, // 开启大数据模式（ECharts内置优化）
        largeThreshold: 500, // 数据量超500启用大数据优化
        lineStyle: { width: 1 }, // 细线减少绘制开销
      },
    ],
  };

  chartInstance.setOption(baseOption);

  // 销毁函数（释放资源，保障长期运行）
  const destroy = () => {
    chartInstance.clear();
    chartInstance.dispose();
  };

  return { chartInstance, destroy };
};
```
