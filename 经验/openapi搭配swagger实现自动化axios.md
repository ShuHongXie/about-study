### 前言

自从 vue3 版本推出之后，typescript 就进入了众多 vue 选手的视野，但是使用 axios 来请求时，往往会出现返回的结构体需要专门定义，且旧的 axios 还需要根据新项目来花大量时间来定义和改造 typescript 返回结构体，这让我们团队的同事头疼不已，我做为团队组长，有必要解决这个问题。

### 解决问题的方案：Hey API

Hey API 是 OpenAPI 到 TypeScript 的 codegen，我们团队使用的 swagger 文档遵循的就是 openapi 规范，Hey API 和 swagger 文档相结合可以使用 axios 配置和返回结构体的自动生成，下面我使用公司的后台管理系统来演示下改造方案

### 依赖安装

```js
pnpm add @hey-api/client-axios && pnpm add @hey-api/openapi-ts -D
```

### 策略 1：axios 实例配置自动生成

```js
// 1.项目根目录增加配置文件
import { defineConfig } from "@hey-api/openapi-ts";

export default defineConfig({
  client: "@hey-api/client-axios", // 所使用类型包
  input: "http://127.0.0.1:3000/api-json", // swagger文档地址
  output: {
    format: "prettier", // 格式化策略
    lint: "eslint",
    path: "./src/client", // 输出地址
  },
  types: {
    dates: "types+transform",
    enums: "javascript",
  },
});

// 2.package.json配置
"scripts": {
    "openapi-ts": "openapi-ts"
}


// 3.命令执行
pnpm run openapi-ts
```

### 文件生成

执行步骤 3 后会生成 client 文件夹

![](https://blog-1300014307.cos.ap-guangzhou.myqcloud.com/20250110113100.png)

service.gen.ts 里面包含了所有生成的接口文档方法, 下面是里面自动生成的范例

```js
/**
 * 获取所有员工
 */
export function findAllEmployee<ThrowOnError extends boolean = false>(options?: Options<unknown, ThrowOnError>) {
  return (options?.client ?? client).get<
    FindAllEmployeeResponse,
    FindAllEmployeeError,
    ThrowOnError
  >({
    ...options,
    url: '/findAllEmployee',
  })
}
```

### 增加 axios 拦截器

创建 config.ts，引入配置文件，初始化拦截器

![](https://blog-1300014307.cos.ap-guangzhou.myqcloud.com/20250110113101.png)

### axios 拦截器方法调用生效

![](https://blog-1300014307.cos.ap-guangzhou.myqcloud.com/20250110113411.png)

**这些步骤下来，通过自动生成的结构体和 axios 方法，此后将不再需要自己写 axios 的配置方法和返回的结构体，大大提高团队开发小绿绿**

参考链接：[Hey API](https://heyapi.dev):
