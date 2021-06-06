## 虚拟机安装ubuntu
教程：https://www.cnblogs.com/liuxiaowei/p/8297301.html
ubuntu镜像网址：http://releases.ubuntu.com/14.04/

ubuntu14.04下命令行安装vmware tools:
1. sudo apt-get upgrade
2. sudo apt-get install open-vm-tools-desktop -y
3. sudo reboot


## CentOS 7教程（一)-初步入门及安装
教程：https://zhuanlan.zhihu.com/p/79047510

系统教程：https://how2j.cn/k/vmware/vmware-vmware/1997.html

- 下载centos
   https://www.centos.org，
   一般来说，从官网下载是比较慢，我们可以从国内的镜像网站下载
   点击下面黄色的椭圆形、写着“DVD ISO”的按纽。点击Mirror List
   可以看到国内经官方认证的镜像列表，从这些镜像列表下载就安心了。
   iso:https://mirrors.tuna.tsinghua.edu.cn/centos/7.8.2003/isos/x86_64/

- 在虚拟机中安装
    1. 创建新的虚拟机
    2. 安装Linux，设置安装选项
        需手动设置安装位置，对分区进行手动配置
        软件选择，选择带GUI的服务器安装
        最后点击开始安装
    3. 安装过程中可以设置ROOT管理员密码
    4. 安装完成后，进入到初始设置界面，接受许可证
    5. 重启后，进入欢迎界面。设置语言等
    
**关键：**
- 虚拟机安装Linux自动启动
- 虚拟机安装Linux防火墙
- 虚拟机安装Linux固定ip地址
- 


## 虚拟机配置
虚拟机——网络适配器——网络设置

为虚拟机设计固定静态ip地址(不靠DHCP)：su root

dhclient

ifconfig

配到网卡：vi /etc/sysconfig/network-scripts/ifcfg-en33
```
DHCP改成static
onboot=yes
IPADDR=获得ip地址
NETMASK=255.255.255.0
GATEWAY=
DNS1=

```

## Linux关闭防火墙命令
CentOS7如何开发其它的端口？
centos7默认使用的是firewall作为防火墙，这里改为iptables防火墙
1. 关闭firewall
```
systemctl stop firewalld.service

systemctl disble firewalld.service

systemctl mask firewalld.service
```
2. 安装iptables防火墙
```
yum install iptables-services -y
```
3. 启动设置防火墙
```
systemctl enable iptables

systemctl start iptables
```
4. 查看防火墙状态
```
systemctl status iptables
```
5. 编辑防火墙，增加端口
vi /etc/sysconfig/iptables
```
-A INPUT -m state --state NEW -m tcp -p tcp --dport 22 -j ACCEPT

-A INPUT -m state --state NEW -m tcp -p tcp --dport 80 -j ACCEPT

-A INPUT -m state --state NEW -m tcp -p tcp --dport 3306 -j ACCEPT

-A INPUT -m state --state NEW -m tcp -p tcp --dport 8000 -j ACCEPT
```

6. 重启配置，重启系统
```
systemctl restart iptables.service #重启防火墙使配置生效

systemctl enable iptables.service #设置防火墙开机启动
```




目前ubuntu14.04用户名:shishijia 密码:shishijia
cent0s7 用户名：root 密码:admin