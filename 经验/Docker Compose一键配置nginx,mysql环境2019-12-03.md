## 前言

之前一直觉得把 mysql 和 nginx 环境分别分开部署很不好，一旦服务器宕机，又得找到对应的目录开启对应的指令，后面发现了 docker 可以用来一次性部署环境，但是也有缺点，服务器宕机的情况下 Mysql 容器里面的数据就会丢失，正好 docker-compose 可以解决这个问题，在这里记录下自己的部署过程。

### 前期准备

docker 环境安装(这部分自行百度)安装完毕就直接拉取镜像

> docker pull mysql:5.6
> docker pull nginx:latest

## 开始正式配置

docker-compose.yml 在自己配置好的 docker 文件夹下(推荐)，创建 docker-compose.yml

> touch docker-compose.yml 编辑 docker-compose.yml
> vim docker-compose.yml 粘贴配置文件

```yml
nginx:
  image: nginx:latest
  ports:
    - \"80:80\"
  volumes:
    - ./nginx/conf/nginx.conf:/etc/nginx/nginx.conf:ro
  mysql:
  restart: always
  image: mysql:5.6
  volumes:
    - ./mysql:/var/lib/mysql
  ports:
    - 3306:3306
  environment:
   MYSQL_ROOT_PASSWORD: \"your_mysql_password\"
```

说明: _ image 代表所要启动的镜像名称_ ports 为当前镜像所启动的映射端口* volumes 下方配置 分号左边为本地的路径，分号右边为原始配置路径，即使用当前路径替换原始配置路径达到自定义的效果* MYSQL_ROOT_PASSWORD 为初始化的 mysql 密码之前后就可以在当前目录下创建 mysql 文件夹和 nginx 文件夹，nginx 文件夹下创建 conf 文件夹并在 conf 下创建 nginx.conf 配置文件

### 开始配置

nginx.conf 文件这里需要注意 upstream 里面的域名不能直接使用 localhost/127.0.0.1 因为 docker 下是无法访问外部宿主机 需要使用指令桥接替换本地 ip 指向，输入以下指令就可以直接使用 192.168.0.1 来指代本地 ip

> docker network create -d bridge --subnet 192.168.0.0/24 --gateway 192.168.0.1 localNet

### 开始构建 docker 容器在 docker 文件夹下输入构建指令

> docker-compose up -d

如果提示如下，那么就成功构建 `  docker_mysql_1 is up-to-date  docker_nginx_1 is up-to-date`构建完直接开启服务

> docker-compose start // 开启服务
