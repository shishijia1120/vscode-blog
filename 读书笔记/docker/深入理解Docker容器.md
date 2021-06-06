

## 1. 安装Docker社区版
```
1. 添加 aliyun-centos7 源 (国内访问速度快)、epel 源
[root@CentOS ~]# cd /etc/yum.repos.d
[root@CentOS ~]# rm -rf ./*
[root@CentOS ~]# wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo
[root@CentOS ~]# wget -O /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-7.repo

2. 增加docker-ce源
[root@CentOS ~]# yum-config-manager --add-repo http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo

3. 安装必要的一些系统工具
[root@CentOS ~]# yum makecache fast
[root@CentOS ~]# yum install -y yum-utils device-mapper-persistent-data lvm2

4. 安装 Docker-CE
[root@CentOS ~]# yum install -y docker-ce
[root@CentOS ~]# systemctl start docker
[root@CentOS ~]# systemctl enable docker

5. 验证
[root@CentOS ~]# docker version
[root@CentOS ~]# docker info
```

注意： Docker 默认使用的 docker0 网段是 172.17.0.0/16
```
[root@CentOS ~]# ip addr
...
3: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN 
    link/ether 02:42:97:6e:da:33 brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
```
如果你的局域网内部已经有该网段了，请先修改 docker0 之后再启动 Docker 服务，否则 SSH 会被断开
```
[root@CentOS ~]# vim /etc/docker/daemon.json
内容如下:

{
  "bip": "172.31.0.1/16"
}
```

国内 Docker 镜像加速：
```
[root@CentOS ~]# vim /etc/docker/daemon.json
内容如下：

{
  "bip": "172.31.0.1/16",
  "registry-mirrors": [
    "https://registry.docker-cn.com"
  ]
}
```

然后，重启 Docker 服务进程即可！

## 2. Docker基础概念

## 3. 镜像管理

```
[root@CentOS ~]# docker image --help

Usage:  docker image COMMAND

Manage images

Commands:
  build       Build an image from a Dockerfile
  history     Show the history of an image
  import      Import the contents from a tarball to create a filesystem image
  inspect     Display detailed information on one or more images
  load        Load an image from a tar archive or STDIN
  ls          List images
  prune       Remove unused images
  pull        Pull an image or a repository from a registry
  push        Push an image or a repository to a registry
  rm          Remove one or more images
  save        Save one or more images to a tar archive (streamed to STDOUT by default)
  tag         Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE

Run 'docker image COMMAND --help' for more information on a command.
```

### 3.1 镜像列表
```
[root@CentOS ~]# docker image ls
或者：
[root@CentOS ~]# docker images  # 只列出顶层镜像
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
   0.0.1               caddd4eb3c24        About an hour ago   89.7MB
...

或者：
[root@CentOS ~]# docker images -a  # 列出镜像的所有文件系统层
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
   0.0.1               caddd4eb3c24        About an hour ago   89.7MB
<none>              <none>              8894a4ef4d93        About an hour ago   89.7MB
<none>              <none>              13a10f373fa4        About an hour ago   89.7MB
<none>              <none>              7c7ea499a390        About an hour ago   89.7MB
<none>              <none>              83828598cf8c        About an hour ago   79.1MB
<none>              <none>              512c36f28841        About an hour ago   79.1MB
...
```
### 3.2 搜索镜像
### 3.3 拉取镜像
### 3.4 删除镜像
### 3.5 构建镜像
### 3.6 归档镜像
### 3.7 导入镜像
### 3.8 镜像历史

## 4. 容器管理