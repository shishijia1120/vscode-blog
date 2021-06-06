1. xshell突然连接不上虚拟机
原因：防火墙没有关闭
systemctl stop iptables.service
chkconfig iptables off

2. centos7安装redis并设置desktopManager远程连接
https://www.cnblogs.com/zkj1204/p/12108653.html

- 配置远程访问
  1. 修改配置文件
   vim /etc/redis.conf
    
    a.bind:192.168.221.129
    b.protected-mode no关闭保护模式
    c.可以设置一个密码 requirepass:123456
  2. 关闭并重启redis，然后重启redis，
   systemctl dtop redis
   systemctl start redis
   ss -tunlp | grep redis
  3. 如果还是只能本地访问，有2点原因：1.端口问题，直接关闭防火墙；2.配置文件的问题

3. elasticsearch连接报错curl: (7) Failed connect to localhost:9200; 拒绝连接
   原以为是端口或是防火墙问题，后来发现是未开启elasticsearch服务
   如何设置elasticsearch服务开机自启动：https://www.cnblogs.com/Rawls/p/10937280.html