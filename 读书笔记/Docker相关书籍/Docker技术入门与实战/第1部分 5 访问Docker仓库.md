## 5 访问Docker仓库
仓库是集中存放镜像的地方，分公共仓库和私有仓库。

### 5.1 Docker Hub公共镜像市场

Docker官方维护了一个公共镜像仓库https://hub.docker.com。大部分镜像需求，都可以通过在Docker Hub中直接下载镜像来实现。
1. 登录
    可以通过命令执行dicker login命令来输入用户名、密码和邮箱完成注册和登录。注册成功后，本地用户目录的.dockercfg中将保存用户的认证信息。
    登录成功的用户可以上传个人创造的镜像。

2. 基本操作
    用户无需登录即可通过docker search命令来查找官方仓库中的镜像，并利用docker pull命令来将它下载到本地。
3. 自动创建
    不懂

### 5.2 时速云镜像市场

国内不少云服务器都提供了Docker镜像市场，下面以时速云为例。

1. 查看镜像
2. 下载镜像
    **命令格式**
    ```index.tenxcloud.com/<namespace>/<repository>:<tag>```

    例如，要下载Docker官方仓库中的node:latest镜像，可以使用如下命令:
    ```$ docker pull index.tenxcloud.com/docker_library/node:latest```
    正常情况下，镜像下载会比直接从DockerHub下载快得多。

    下载后，可以更新镜像的标签，与官方标签保持一致，方便使用：
    ```$ docker tag index.tenxcloud.com/docker_library/node:latest node:latest```

    另外，阿里云等服务商也已提供了Docker镜像的下载服务，用户可以根据服务质量自行选择。


### 5.3 搭建本地私有仓库
1. 使用registry镜像创建私有仓库
   安装Docker后，可以通过官方提供的registry镜像来简单搭建一套本地私有仓库环境：
   ```$ docker run -d -p 5000:5000 registry```
    这将自动创建下载并启动一个registry容器，创建本地的私有仓库服务。
    默认情况下，会将仓库创建在容器的/tmp/registry目录下。可以通过-v参数来将镜像文件存放在本地的指定路径。

    例如下面的例子将上传的镜像放到/opt/data/registry目录:
    ```$ docker run -d -p 5000:5000 -v /opt/data/registry:/tmp/registry registry```
    此时，在本地将启动一个私有仓库服务，监听端口为5000。


2. 管理私有仓库
    首先假设本书环境的笔记本上(Linux Mint)搭建私有仓库，查看其地址为10.0.2.2：5000.然后在虚拟机系统(Ubuntu 14.04)里测试上传和下载镜像。

    在Ubuntu 14.04系统查看已有的镜像：
    ```$ docker images```
    使用docker tag命令将这个镜像标记为10.0.2.2:5000/test
    ```$ docker tag ubuntu:14.04 10.0.2.2:5000/test```
    ```$ docker images```

    使用docker push上传标记的镜像：
    ```$ docker push 10.0.2.2:5000/test```
    用curl查看仓库10.0.2.2：5000中的镜像：
    ```$ curl http://10.0.2.2:5000/v1/search```
    上传成功后，可以到任意一台能访问到10.0.2.2地址的机器上下载这个镜像了。



### 5.4 本章小结
在企业的生产环境中，则往往需要使用私有仓库来维护内部镜像。