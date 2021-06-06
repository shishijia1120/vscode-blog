## 4 操作Docker容器

容器是镜像的一个运行实例，不同的是，镜像是静态的只读文件，而容器带有运行时需要的可写文件层。

虚拟机是模拟运行的一整套操作系统(包括内核、应用运行态环境和其他系统环境)和跑在上面的应用。
Docker容器就是独立运行的一个(或一组)应用，以及它们所需要的运行环境。


### 4.1 创建容器
1. 创建新容器
    可以使用docker create命令新建一个容器：
    ```$ docker create -it ubuntu:latest```
    ```$ docker ps -a```
    使用docker create命令新建的容器处于停止状态，可以使用docker start命令来启动它。

2. 启动容器

    使用docker start命令来启动一个已经创建的容器，例如启动刚创建的ubuntu容器：
    ```$ docker start af```
    查看运行的容器：
    ```$ docker ps```

3. 新建并启动容器
    docker run命令等价于先执行docker crete命令，再执行docker start命令。

    例如：
    ```$ docker run ubuntu /bin/echo 'Hello world' ```

    启动一个bash终端，允许用户进行交互：
    ```$ docker run -it ubuntu:14.04 /bin/bash```

    其中，-t选项让Docker分配一个伪终端并绑定到容器的标准输入上，-i则让容器的标准输入保持打开。

    用户可以按Ctrl+d或输入exit命令来退出容器:

    未完。。。

### 4.2 终止容器

**命令格式**
```docker stop[-t|--time[=10]][CONTAINER...]```

```$ docker stop ce5```

### 4.3 进入容器
在使用-d参数时，容器启动后会进入后台，用户无法看到容器中的信息，也无法进行操作。
这个时候如果需要进入容器进行操作，有多种方法，包括使用官方的attach或exec命令，以及第三方的nsenter工具等。
1. attach命令
   attach是Docker自带的命令，命令格式为：
   ```docker attach [--detach-keys[=[]]] [--no-stdin] [--sig-proxy[=true]] CONTAINER```
   支持三个主要选项：
   --detach-keys[=[]]:
    ```$ docker run -itd ubuntu```
    ```$ docker ps```
    ```$ docker attach nostalgic_hypatia```


2. exec命令
3. nsenter工具







### 4.4 删除容器
可以使用docker rm命令来删除处于终止或退出状态的容器，命令格式为docker rm[-f|--force][-l|--link][-v|--volumes]CONTAINER[CONTAINER...]
主要支持的选项包括：
- \-f：--force=false:是否强行终止并删除一个运行中的容器；
- \-l:--link=false:删除容器的连接，但保留容器；
- \-v:--volumes=false：删除容器挂载的数据卷；

例如，查看处于终止状态的容器，并删除：
```$ docker ps -a```
默认情况下，docker rm命令只能删除处于终止状态或退出状态的容器，并不能删除还处于运行状态的容器。

如果要删除一个运行中的容器，可以添加-f参数。Docker会先发送SIGKILL信号给容器，终止其中的应用，之后强行删除，如下所示：
```$ docker run -d ubuntu:14.04 /bin/sh -c "while true;do echo hello world; sleep 1; done" ```

### 4.5 导入和导出容器
某些时候，需要将容器从一个系统迁移到另一个系统，此时可以使用Docker的导入和导出功能。这也是Docker自身提供的一个重要特性。
1. 导出容器
   导出容器是指导出一个已经创建的容器到一个文件，不管此时这个容器是否处于运行状态，可以使用docker export命令，该命令的格式为docker export[-o|--putput[=""]]CONTAINER。其中，可以通过-o选项来指定导出的tar文件名，也可以直接通过重定向实现。

   首先查看所有的容器:
   ```$ docker ps -a```
   分别导出ce55426777容器和e812617b41f6容器到文件test_for_run.tar文件和test_for_stop.tar文件：
   ```$ docker export -o test_for_run.tar ce5 ```
   ```$ ls```
   ```$ docker export e81 >test_for_stop.tar```
   ```$ ls```
   之后，可将导出的tar文件传输到其他机器上，然后再通过导入命令导入到系统中，从而实现容器的迁移。
2. 导入容器
   导出的文件又可以使用docker import命令导入变成镜像，该命令格式为：
   ```docker import [-c|--change[=[]]] [-m|--message[=MESSAGE]] file|URL|-[REPOSITORY[:TAG]]```

   将导出的test_for_run.tar文件导入到系统中：
   ```$ docker import test_for_run.tar - test/ubuntu:v1.0```
   ```$ docker images```

### 4.6 本章小结
