## 3 使用Docker镜像
Docker运行容器前需要本地存在对应的镜像，如果镜像没保存在本地，Docker会尝试先从默认镜像仓库下载(默认使用Docker Hub公共注册服务器中的仓库)，用户也可以通过配置，使用自定义的镜像仓库。


### 3.1 获取镜像
镜像是运行容器的前提，官方的Docker Hub网站已经提供了数十万个镜像供大家开放下载。
可以使用docker pull命令直接从Docker Hub镜像源来下载镜像。
**命令格式**
```docker pull NAME[:TAG]```

例如，获取一个Ubuntu14.04系统的基础镜像可以使用如下的命令：
```$ docker pull ubuntu:14.04```

例如，获取一个最新Ubuntu系统的基础镜像可以使用如下的命令：
```$ docker pull ubuntu```

严格地来讲，镜像的仓库名称中还应该添加仓库地址(即registry，注册服务器)作为前缀，只是我们默认使用的是Docker Hub服务，该前缀可以忽略。

例如,docker pull ubuntu:14.04命令相当于docker pull registry.hub.docker.com/ubuntu:14.04命令。
如果从非官方的仓库下载，则需要在仓库名称前指定完整的仓库地址。例如从网易蜂巢的镜像源来下载ubuntu:14.04镜像，可以使用如下命令：
```$ docker pull hub.c.163.com/public/ubuntu:14.04```

### 3.2 查看镜像信息
1. 使用images命令列出镜像
    使用docker iamges命令可以列出本地主机上已有镜像的基本信息。
    ```$ docker images```

    **选项**：
    - a：
    - digests:
    - f:
    - format:
    - no-trunc:
    - q:
2. 使用tag命令添加镜像标签
   为了方便在后续工作中使用特定镜像，还可以使用docker tag命令来为本地镜像任意添加新的标签。
   例如添加一个新的myubuntu:latest镜像标签：
   ```$ docker tag ubuntu:latest myubuntu:latest```
    再次使用docker images列出本地主机上镜像信息，可以看到多了一个拥有myubuntu:latest标签的镜像：

3. 使用inspect命令查看详细信息
   使用docker inspect命令可以获取该镜像的详细信息，包括制作者、适应架构、各层的数字摘要等：
   ```$ docker inspect ubuntu:14.04```

4. 使用history命令查看镜像历史
不懂

### 3.3 搜寻镜像
使用docker search命令可以搜索远端仓库中共享的镜像，默认搜索官方仓库中的镜像。
**命令格式**
```docker search TERM```

**选项**
- \-\-automated:
- \-s:
- \-\-no-trunc


例如，搜索所有自动创建的评价为1+的带nginx关键字的镜像：
```$ docker search --automated -s 3 nginx```


### 3.4 删除镜像
1. 使用标签删除镜像
    使用docker rmi命令可以删除镜像。
    **命令格式**
    ```docker rmi IMAGE[IMAGE...] IMAGE可以为标签或ID```

    例如，删除myubuntu:latest镜像：
    ```$ docker rmi myubuntu:latest```
    **注意：**该命令只是删除该镜像多个标签中的指定标签而已，并不影响镜像文件。只是删除了镜像的一个标签而已。如果镜像只剩下一个标签的时候就要小心了，此时再使用docker rmi命令会彻底删除镜像。


2. 使用镜像ID删除镜像
    当使用docker rmi命令，并且后面跟上镜像的ID(也可以是能进行区分的部分ID串前缀)时，会先尝试删除所有指向该镜像的标签，然后删除该镜像文件本身。
    **注意：**当有该镜像创建的容器存在时，镜像文件默认是无法被删除的，例如，先利用ubuntu:14.04镜像创建一个简单的容器来输出一段话：
    ```$ docker run ubuntu:14.04 echo 'hello! I am here!' ```
    使用docker ps-a命令可以看到本机上存在的所有容器：
    
    试图删除该镜像，Docker会提示有容器正在运行，无法删除：
    ```$ docker rmi ubuntu:14.04```
    
    如果想强行删除镜像，可以使用-f参数:
    ```$ docker rmi -f ubuntu:14.04```
    
    **注意：**通常不建议使用-f参数来强制删除一个存在容器依赖的镜像。正确的做法是，先删除依赖该镜像的所有容器，再来删除镜像。如首先删除容器a21c0840213e:
    ```$ docker rm a21c0840213e```
    再使用ID来删除镜像，此时会正常打印出删除的各层信息:
    

### 3.5 创建镜像
创建镜像的方法主要有三种:基于已有镜像的容器创建、基于本地模板导入、基于Dockerfile创建。

1. 基于已有镜像的容器创建
    **命令格式**
    ```docker commit [option] CONTAINER [REPOSITORY :TAG]```
    **选项**
    - \-a:
    - \-c:
    - \-m:
    - \-p:

    如何创建一个新镜像：
    (1) 首先，启动一个镜像：
    ```$ docker run -it ubuntu:14.04 /bin/bash```
    记住容器的ID设为a925cb40b3f0。

    (2) 此时该容器跟原ubuntu:14.04镜像相比，已经发生了改变，可以使用docker commit命令来提交一个新的镜像。提交时可以使用ID或名称来指定容器：
    ```$ docker commit -m "Added a new file" -a "Docker Newbee" a925cb40b3f0 test:0.1```

    (3) 查看本地镜像列表，会发现新创建的镜像已经存在了:
    ```$ docker iamges```
    
2. 基于本地模板导入
   用户也可以直接从一个操作系统模板文件导入一个镜像，主要使用docker import命令。
   **命令格式**
    ```docker import [option] file |URL|-[REPOSITORY[:TAG]]```


    例如，下载了ubuntu-14.04的模板压缩包，之后使用以下命令导入：
    ```$ cat ubuntu-14.04-x86_64-minimal.tar.gz | docker import - ubuntu:14.04```
    然后查看新导入的镜像，会发现它已经在本地存在了：
    ```$ docker images```


### 3.6 存出和载入镜像
用户可以使用docker save和docker load命令来存出和载入镜像。

1. 存出镜像
   例如，导出本地的ubuntu:14.04镜像为文件ubuntu_14.04.tar：
    ```$ docker images```
    ```$ docker save -o ubuntu_14.04.tar ubuntu:14.04```
    之后，用户就可以通过复制ubuntu_14.04.tar文件将该镜像分享给他人。

2. 载入镜像
    可以使用docker load将导出的tar文件再导入到本地镜像库，例如从文件ubuntu_14.04.tar导入镜像到本地镜像列表：
    ```$ docker load --input ubuntu_14.04.tar```
    ```$ docker load < ubuntu_14.04.tar```

### 3.7 上传镜像
可以使用docker push命令上传镜像到仓库，默认上传到Docker Hub官方仓库(需要登录)。
**命令格式**
```docker push NAME[:TAG] | [REGISTRY_HOST[:REGISTRY_PORT]/]NAME[:TAG]```

用户在Docker Hub网站注册后可以上传自制的镜像。例如用户user上传本地的test:latest镜像，可以先添加新的标签user/test:latest，然后用docker push命令上传镜像:
```$ docker tag test:latest user/test:latest```
```$ docker push user/test:latest```
第一次上传时，会提示输入登录信息或进行注册。

### 3.8 本章小结
镜像是平时使用Docker的前提，也是最基本的资源。所以，在平时的Docker使用中，要注意积累自己定制的镜像文件，并将自己创建的高质量镜像分享到社区中。