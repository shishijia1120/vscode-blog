
## 1. MySQL容器
> https://hub.docker.com/_/mysql


创建MySQL配置文件，指定字符集为UTF-8：
```
[root@CentOS www]# mkdir -p $PWD/docker/mysql/conf.d
[root@CentOS www]# vim $PWD/docker/mysql/conf.d/custom.cnf
内容如下：

[mysqld]
character-set-server = utf8
collation-server = utf8_general_ci
skip-character-set-client-handshake
```

> 注意: utf8_general_ci 数据表中的字段值不区分大小写（ci, case insensitive），比如 Madman 和 madman 被认为是一样的。如果你想区分大小写，则要设置为 utf8_bin（不能设置为 utf8_general_cs，容器会无法启动）

然后将宿主机上的 配置文件 和 数据目录 链接到 MySQL 容器，这样就算后续不小心删除了此容器，数据库中的数据文件还存在于本地，下次再重新启一个 MySQL 容器即可：

```
[root@CentOS www]# docker run -d \
  --name mysql \
  -e MYSQL_ROOT_PASSWORD=123456 \
  -e MYSQL_DATABASE=madblog \
  -e MYSQL_USER=testuser \
  -e MYSQL_PASSWORD=password \
  -p 3306:3306 \
  --rm \
  -v $PWD/docker/mysql/conf.d:/etc/mysql/conf.d \
  -v $PWD/docker/mysql/data:/var/lib/mysql \
  mysql:5.6
```

测试一下连接，再启动一个 MySQL 容器，需要先 链接 上面的 MySQL Server 容器，并设置主机名为 mysql-server，这样 -hmysql-server 才能解析到 MySQL Server 容器所绑定的 IP 地址：

```
[root@CentOS www]# docker run -it --link mysql:mysql-server --rm mysql:5.6 mysql -hmysql-server -utestuser -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 2
Server version: 5.7.25 MySQL Community Server (GPL)

Copyright (c) 2000, 2019, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| madblog            |
+--------------------+
2 rows in set (0.00 sec)

mysql> quit
Bye
```

## 2. Redis容器
> https://hub.docker.com/_/redis

```
[root@CentOS www]# docker run -d \
  --name redis \
  -p 6379:6379 \
  --rm \
  -v $PWD/docker/redis/data:/data \
  redis redis-server --appendonly yes
```

启动此容器时要运行 redis-server --appendonly yes 命令，表示启用了 Redis 数据持久性，所以指定了映射宿主机上的 $PWD/docker/redis/data 目录到容器的 /data 目录

测试连接：
```
[root@CentOS www]# docker run -it --link redis:redis-server --rm redis redis-cli -h redis-server
redis-server:6379> keys *
(empty list or set)
redis-server:6379> quit
```

## 3. Elasticsearch容器
