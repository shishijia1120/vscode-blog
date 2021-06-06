## 1
**借鉴：https://zhuanlan.zhihu.com/p/47077536**

**虚拟机：**模拟整台机器包括硬件，每台虚拟机都需要有自己的操作系统，虚拟机一旦被开启，预分配给它的资源将全部被占用。
**容器：**和宿主机共享硬件资源及操作系统，可以实现资源的动态分配。容器包含应用和其所有的依赖包，但是与其他容器共享内核。容器在宿主机操作系统中，在用户空间以分离的进程运行。

容器技术是实现操作系统虚拟化的一种途径，可以让你在资源受到隔离的进程中运行应用程序及其依赖关系。通过使用容器，可以轻松打包应用程序的代码、配置和依赖关系，将其变成容易使用的构建块，从而实现环境一致性。

Docker将应用程序与该程序的依赖，打包在一个文件里面。运行这个文件，就会生成一个虚拟容器。程序在这个虚拟容器里运行，就好像真实的物理机运行一样。

### Docker三个基本概念
- Image
- Container
- Repository

## Docker的安装和使用

Docker CE的安装请参考官方文档：
- Windows:

**环境准备**

Docker 软件包已经包括在默认的 CentOS-Extras 软件源里。因此想要安装 docker，只需要运行下面的 yum 命令
```$ sudo yum install docker ```

当然在测试或开发环境中 Docker 官方为了简化安装流程，提供了一套便捷的安装脚本，CentOS 系统上可以使用这套脚本安装：
```curl -fsSL get.docker.com -o get-docker.sh```
```sh get-docker.sh```

安装完成后，运行下面的命令，验证是否安装成功：
```docker version```

启动Docker-CE
```$ sudo systemctl enable docker```
```$ sudo systemctl start docker```


## 2
**参考：https://zhuanlan.zhihu.com/p/44866322**
Docker 是一个开源的应用容器引擎，基于 Go 语言 并遵从 Apache2.0 协议开源。Docker 可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中，然后发布到任何流行的 Linux 机器上。

虚拟机最大的瓶颈在于其需要特殊硬件虚拟化技术支持，并且携带完整的操作系统；而 Docker 没有硬件虚拟化，可以运行在物理机、虚拟机, 甚至嵌套运行在 Docker 容器内，并且其不携带操作系统的，会轻巧很多。在调用宿主机的内存、CPU、磁盘等等资源时，虚拟机是利用 Hypervisor 去虚拟化内存，整个调用过程是虚拟内存->虚拟物理内存->真正物理内存，但是 Docker 是利用 Docker Engine 去调用宿主的的资源，这时候过程是虚拟内存->真正物理内存。



## CScript
Docker是开发人员或系统管理员使用"容器"开发、部署和运行应用程序的平台(Build、Share、Run)。


**使用docker创建一个简单的Web应用(Flask框架)**
1. 下载安装docker，修改docker镜源为国内的镜像(提高下载速度)
2. docker run hello-world
3. 创建目录，新建Dockerfile、app.py、requirements.txt
4. 使用Dockerfile进行自定义镜像的制作：可以在配置文件里获取需要依赖的上层镜像(父级镜像)，也可以把本地目录拷贝到镜像内部的指定目录(目录映射)。
5. 运行创建命令:docker image build就可以创建自定义镜像
6. 实现自动更新

**docker compose**