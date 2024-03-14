## 前言

前段时间自己用 Next.js 的项目部署上线了，记录下 Next.js 的部署方式

## Next.js 项目模块建议使用自带的 dynamic 动态导入模块

## 开始部署

1. 删除 node_modules 文件夹(文件过大，等在服务器重新下载比较合适)
2. Linux 下使用 scp 命令传输到服务器/window 下使用 xftp 工具直接拖
   > scp -r 本地文件夹地址 服务器用户名@服务器 ip:远程目录地址
3. 远程目录下 npm install 安装依赖 修改 package.json 的 npm start 命令为 > NODE_ENV=production node server.js
4. npm run build
5. pm2 启动
   > pm2 start npm --name \"your_server_name\" -- run start
