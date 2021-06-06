## 6. Linux文件与目录管理
### 6.2 文件与目录管理
#### 6.2.1 文件与目录的检视：ls
将家目录下的所有文件列出来（含属性与隐藏文件）
ls -al ~
#### 6.2.2 复制、删除与移动:cp,rm,mv
- 复制(cp)这个指令是非常重要的，不同身份者执行这个指令会有不同的结果产生。
```
# cp [-adfilprsu] 来源文件(source) 目标文件(destination)
# cp [options] source1 source2 source3 ... directory
常用选项与参数：
-a ：
-i:若目标文件已经存在时，在覆盖时会先询问动作的进行
-r：递归持续复制

```

示例
```
1. 用root身份，将家目录下的.bashrc复制到/tmp下，并更名为bashrc
# cp ~/.bashrc /tmp/bashrc
# cp -i ~/.bashrc /tmp/bashrc
# 重复作两次动作，由于.tmp底下已经有bshrc了，加上-i选项后，则在覆盖前会询问使用者是否确定
```

- rm(移除文件或目录)
```
rm [-fir]文件或目录
选项与参数：
-f:force
-i:互动模式
-r:递归删除！非常危险  
```
示例
```
1. 将/tmp/etc/这个目录删除掉！
# rm -r /tmp/etc
```

- mv(移动文件与目录，或更名)
```
# mv [-fiu] source destination
# mv [options] source1 source2 source3 .... directory
选型与参数：
-f:force
-i:
-u:
```
示例
```
1. 复制一文件，建立一目录，将文件移动到目录中
# mv bashrc mvtest

2. 将刚刚的目录名称更名为mvtest2
# mv mvtest mvtest2

3. 移动多个文件
# mv bashrc1 bashrc2 mvtest2
```
#### 6.2.3 取得路径的文件名与目录名称
```
# basename /etc/sysconfig/network
network
# dirname /etc/sysconfig/network
/etc/sysconfig
```
### 6.3 文件内容查阅
#### 6.3.1 直接检视文件内容
- cat
  由第一行到最后一行连续显示在屏幕上
```
# cat [-AbEnTv]
-A：相当于-vET的整合选项
-b：列出行号，空白行不标行号
-n:打印出行号，连同空白行
-E：将结尾的断行字符$显示出来
-T：将[tab]按键以^I显示出来
-v:列出一些看不出来的特殊字符
```

示例
```
1. 检阅 /etc/issue这个文件的内容
# cat /etc/issue

# cat -n /etc/issue


```

- tac
  由最后一行到第一行反向在屏幕上显示出来
- nl(添加行号打印)
```
# nl [-bnw] 文件
选项与参数：

```

#### 6.3.2 可翻页检视
- more(一页一页翻动)
    - 空格键(space):代表向下翻一页
    - Enter:代表向下翻一行
    - /字符串:代表在这个显示的内容当中，向下搜寻字符串这个关键词
    - :f：立刻显示出文件名以及目前显示的行数

#### 17.2.1 透过systemctl 管理单一服务(service unit)的启动/开机启动与观察状态
```
# systemctl [command] [unit]
```