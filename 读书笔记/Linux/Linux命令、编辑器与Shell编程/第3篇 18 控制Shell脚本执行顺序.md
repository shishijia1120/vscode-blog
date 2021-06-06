## 18 控制Shell脚本执行顺序


### 18.1 条件测试和捕获信号

#### 18.1.1 退出状态
在Linux系统中，无论是命令、脚本还是程序，执行完成退出后都存在退出状态，退出状态通常保存在预定义$?中。大多数情况下，预定义变量都只会使用两个数字表示命令、脚本和程序的退出状态。
- 数字0表示命令、脚本或程序成功执行，没有发生错误。
- 数字1表示在执行过程中发生了错误，没有成功执行。


**设置退出状态命令**

- exit 0:表示返回脚本执行成功，无错误返回。有时也称为返回为真。  
- exit 1:表示返回脚本执行失败，无错误返回。有时也称为返回为假。

除了以上的0和1外，还可以使用其他的一些数字，但只要返回的状态非0，系统就认为脚本执行失败。

使用exit命令设置退出状态时需要注意，无论脚本执行到何处，只要遇到exit命令，脚本会立即设置退出状态并退出脚本。

```
# cat example18.1.sh
...

function usage()
{
    ...
    return 1

}

if [ $# = 0 ]
    then
        usage
        exit 1
fi

echo $1
exit 0

```

执行脚本：
```
# ./example18.1.sh
Error:...
# echo命令显示脚本的退出状态为有错误退出
# echo $?
1

# ./example18.1.sh abc
abc
# echo 命令显示脚本无错误退出
# echo $?
0

```


**函数返回状态命令return与退出状态命令exit的区别**
```
# cat example18.1.1.sh
...

function usage()
{

    echo "Error..."
    exit 1

}

if [ $# = 0 ]
    then
        usage
fi

echo $1
# 正常退出状态设置为2
exit 2


```

执行脚本：
```
# ./example18.1.1.sh

Error:...

# 查看脚本的退出状态
# echo $?

1

# 执行脚本时传递参数abc
# ./example18.1.1.sh abc
Abc

# 查看脚本的退出状态
# echo $?
2

```

在脚本的任何位置使用exit命令设置退出状态，脚本执行都会中断。



#### 18.1.2 文件测试

对文件的测试包括两个方面：第1个方面是文件基本测试，包括文件、目录是否存在、文件类型、文件长度等；第2个方面是文件权限测试，包括文件是否可读取、写入、执行等。

1. 文件基本测试
文件基本测试大多用在创建文件、目录之前，这样做的目的是让脚本拥有更好的容错性。

**文件测试命令**
- d:测试目标是否存在，并且是一个目录。
- f:测试目标文件是否存在，并且是一个普通文件。
- L:测试目标是否存在，并且是一个链接文件。
- b:测试文件是否存在，并且是一个块设备文件。
- c:测试目标文件是否存在，并且是一个块设备文件。
- e:测试指定文件或目录是否存在。

**文件测试命令的格式**
```[ -command parameter]```

(1) 测试文件/etc/rc.local是否为一个目录：
```
# [ -d /etc/rc.local ]

# echo $?
1
```

从命令的退出状态可以看出测试为假。表示/etc/rc.local并不是一个目录。


(2) 测试文件的示例脚本：
。。。。。。

2. 文件权限测试

**文件权限测试命令**
- w:判断指定的文件是否存在，并且拥有可写入权限。判断指定的文件是否存在，并且具备可读取权限。
- r:判断指定的文件是否存在，并且具备可读取权限。
- x:判断目标文件是否存在，并且具备可执行权限。
- u:判断目标文件是否具有SUID权限。

对文件权限进行测试时，需要注意的是这些测试都是针对脚本的执行用户，并非测试的是文件属主的权限。

**用法示例**

(1) 
```
# cat example18.3.sh
...

# 定义用于返回错误信息的函数usage
function usage()
{
    echo "Error:..."
    echo "Usage:"$0" filename"
    exit 1
}

# 定义用于生成文件权限字符串的函数permission
function permission()
{
    # 判断传递过来的参数是否是一个文件，如果不是则返回提示
    if [ ! -e $1 ]
        then
            echo "Error:$1 file not find."
            return 1
    fi



    # 判断参数1所指向的文件是否具有读的权限
    # 并将生成的权限字符串保存在变量PERMI中

    if [ -r $1 ]
        then
            PERMI ="r" 
    else
            PERMI = "-"
    fi

    # 判断参数1所指向的文件是否具有写的权限
    # 并将权限标记保存在变量PERMI中

    if [ -w $1 ]
        then
            PERMI =$PERMI "w" 
    else
            PERMI = $PERMI"-"
    fi

    # 判断参数1所指向的文件是否具有执行的权限
    # 并将权限标记保存在变量PERMI中

    if [ -x $1 ]
        then
            PERMI =$PERMI "x" 
    else
            PERMI = $PERMI"-"
    fi

    # 函数处理完成后返回生成的权限字符串
    echo $PERMI
    return 0
}

# 脚本主体部分

if [ $# = 0]
    then
        usage
        exit 1
fi

# 调用函数permission并判断是否成功执行
if MESSAGE='permission $1'
    then
        echo $1 ":"$MESSAGE
        exit 0
else
    echo $MESSAGE
    exit 1
fi


```


执行脚本：
```
# ./example18.3.sh /etc/passwd /etc/passwd:rw-

```


#### 18.1.3 变量测试
对变量的测试内容是测试变量是否已经被定义(被定义的标准是变量已经赋值)。
测试变量是否被定义需要使用命令z，对于没有被定义的变量，将会返回数字0，已经定义的函数将会返回数字1.

```
# [-z $NAME]

# echo $?
0

# NAME=Jhon
# [-z $NAME]
# echo $?
1

```



#### 18.1.4 字符串和数值测试

1. 字符串测试
- =：判断两个字符串是否相等，如果相等，则返回为真(即数字0)。
- !=：判断两个字符串是否不相等，如果不相等，则返回为真。
- n:测试字符串是否为非空。

**用法示例**
(1) 测试字符串是否相等：

```
# ["abc" = "ABC"]

# echo $?
1
```

(2) 许多时候都希望能够判断某个变量是否为空：

```
# ["$NAME" = ""]
# echo $?
1
```

(3) 测试某个变量是否等于一个字符串:
```
# ["$NAME" = "Jhon" ]
# echo $?
0

```

(4) 使用命令n测试字符串是否为空:
```
# [-n "$NAME"]
# echo $?
1
# NAME="Jhon"
# echo $?
0
```

2. 数值测试
- eq:
- ne:
- lt:
- le:
- gt:
- ge:

**用法示例**
(1) 测试数字300是否小于200：
```
# [ 300 -lt 200]
# echo $?
1

```

(2) 进行数值测试时，也可以将两个数放入引号内：
```
# [ "300" -lt "500" ] 
# echo $?
0
```
无论使用哪种形式进行测试，命令都会先将两边的字符转换为数值之后，再进行数值测试。

(3) 对两个变量进行测试：
```
# A=14
# B=53
# [ $A -gt $B]
# echo $?
1
```

(4) 测试某个变量是否大于等于某个数字：
```
# FLAG=134

# [$FLAG -ge "133" ]
# echo $?
0
```




#### 18.1.5 逻辑操作符

**常用的逻辑操作符**
- a:逻辑与，操作符两边都为真时，结果为真，否则为假。
- o:逻辑或，操作符两边至少有一边为真时，结果为真，否则为假。
- !:逻辑非，条件为真时，结果为假，条件为假时，结果为真。


**用法示例**
(1) 测试文件/etc/passwd是否可读、写：
```
# [ -r /etc/passwd -a -w /etc/passwd ]
# echo $?
0
```

(2) 测试文件可读或可执行：
```
# [-r /etc/passwd -o -x /etc/passwd ]
# echo $?
0
```



#### 18.1.6 捕获系统信号
在编写脚本时，可能会担心由于脚本的使用者发出了一个终止脚本运行的信号，Shell脚本就终止运行，从而无法完成正在处理的工作。
因此在重要的脚本中，应该捕获系统发出的终止信号并做出相应的动作，以免脚本终止带来不必要的损失。

**可以捕获的信号**

- 1 (SIGHUP):来自控制终端的挂起或来自控制进程的死亡信号。
- 2 (SIGINT):来自键盘的中断信号。
- 3 (SIGQUIT):来自键盘的退出信号。
- 4 (SIGTERM):终止信号。


**捕获信号后的措施**

- 不采取任何措施，由系统处理这些信号。这会导致脚本结束执行、暂停等后果，这个办法通常用于不重要的脚本中。
- 捕获并忽略信号，即捕获到信号后不采取任何操作。
- 捕获信号并采取操作，这通常用于比较重要的脚本中。通常操作是提示用户是否需要中断脚本的执行，也可以向用户发出脚本正在执行不能退出的消息等。

**捕获信号的格式**
``` trap "command" signals ```

command表示捕获到信号之后需要执行的命令或函数，如果为空(使用""表示)则表示忽略信号，否则表示执行信号。
signals表示要捕获的信号列表，可以使用数字表示，也可以使用信号名称表示。如果要捕获多个信号，则使用空格作为信号间的分隔符。



**用法示例**
在脚本ex_trap.sh中，捕获的是用户从键盘上发送的结束信号(Ctrl+C，对应的信号为2)，捕获到信号后脚本将调用函数trap，输出提示信息并退出。


```
# cat ex_trap.sh
...

# 如果捕获到信号2，则执行函数trap
trap "trap" 2

# 定义捕获到信号后的处理函数trap
function trap()
{
    echo "You press the Ctrl+C."
    echo "Exiting, please wait ..."
    exit 1
}

sleep 60

```
这是一个用于捕获Ctrl+C退出快键的脚本，运行结果如下：
```
# ./ex_trap.sh
# 此时按下Ctrl+C
You press the Ctrl+C.
Exiting, please wait ...
```


### 18.2 条件判断语句if
#### 18.2.1 简单if语句的使用

**简单if语句的格式**
```
if 条件表达式
    then
        语句1
        语句2

        ...
fi

```


#### 18.2.2 if else 语句的使用
**if else语句的格式**
```
if 条件测试
    then
        语句块1
else
    语句块2
fi

```


#### 18.2.3 if elif语句的使用
**if elif 语句的基本格式**

```
if 条件测试1
    then
        语句块1
elif 条件测试2
    then
        语句块2
elif 条件测试3
    then
        语句块3
elif 条件测试4
        语句块4
...

else
    语句块5
fi
```



### 18.3 多条件判断语句case

#### 18.3.1 多条件判断语句case的基本格式
**case语句的基本格式**
```
case 变量 in
    模式1)
        语句块1
        ;;
    模式2)
        语句块2
        ;;
    ...

        ;;
esac

```

#### 18.3.2 利用case语句处理选项参数



#### 18.3.3 利用case语句处理用户输入
```
...

while true
    do
        echo -n "Please enter yes or no ?[yes|no]"
        read ANS
        case "$ANS" in 
        # 如果用户输入的是y、Y、yes或Yes
        y|Y|yes|Yes)
        
        echo "You enter yes"
        ...
        break
        ;;
        # 如果用户输入的是n、N、no或No
        n|N|no|No)
            echo "You enter no"
            ...
            break
            ;;

        *)
            echo "Please enter yes or no."

            continue
            ;;
    esac
done
```

### 18.4 步进循环语句for

#### 18.4.1 for语句的基本格式
```
for 变量 in 列表
do 
    语句块
done
```

#### 18.4.2 利用for语句处理数组


```
# cat exampl18.11.sh

...

I=1
for LOOP in 1 2 3 4 5 6
    do
        # 显示当前是第几次执行循环
        echo "loop:" $I
        # 显示当前循环中变量LOOP的值
        echo "LOOP="$LOOP
        # 将变量I的值加1
        I='expr $I +1'
done
exit 0

```

执行脚本：
```
# ./example18.11.sh

loop:1
LOOP=1
loop:2
LOOP=2
loop:3
LOOP=3
...
loop:6
LOOP=6
```

也可改写成数组表示值列表的方式：
```
# cat exampl18.11.1.sh

...

I=1
J="1 2 3 4 5 6"
for LOOP in $J
    do
        # 显示当前是第几次执行循环
        echo "loop:" $I
        # 显示当前循环中变量LOOP的值
        echo "LOOP="$LOOP
        # 将变量I的值加1
        I='expr $I +1'
done
exit 0
```

#### 18.4.3 一个设置防火墙的例子
先从用户输入中接收防火墙端口号列表，然后使用for语句引用这些端口并使用命令添加规则，最后保存防火墙规则。

```
# cat example18.12.sh

echo -n "Please enter the port number allowed:"
read PORT_LIST

# 利用for语句处理变量PORT_LIST中的端口列表
for PORT in $PORT_LIST
    do
        # 为防火墙添加规则
        iptables -t filter -A OUTPUT -p tcp --dport $PORT -j ACCEPT
        iptables -t filter -A OUTPUT -p udp --dport $PORT -j ACCEPT
        # 显示已经添加规则的端口号
        echo "Allowed port:" $PORT 
done

#保存防火墙规则
/etc/init.d/iptables save 
exit 0
```

执行脚本：
```
# ./example18.12.sh
Please enter thr port number
allowed:80 53 110 21
Allowed port:80
Allowed port:53
Allowed port:110
Allowed port:25
Allowed port:21
Saving firewall rules to 
/etc/sysconfig/iptables:
[OK]
```
脚本成功执行，并添加用户输入的端口号至防火墙规则。


### 18.5 循环语句until

#### 18.5.1 until语句的基本格式
**until语句的基本格式**
```
until 条件测试
    do
        语句块
done
```

```
# cat example18.13.sh
...

I=0
until [$I -gt 5 ]
    do
        I='expr $I + 1'
        echo "I="$I
done

```
运行脚本：
```
# ./example18.13.sh
I=1
I=2
...
I=6 
```


#### 18.5.2 利用until语句监控文件系统状态
。。。。。。

### 18.6 while循环语句

#### 18.6.1 while语句的基本格式
```
while 条件测试
    do
        语句块
done
```

#### 18.6.2 while语句与until语句的区别
```
# cat example18.15.sh
...

I=1
while [$I -lt 6 ]
    do
        echo "loop:"$I
        echo "I="$I
        I='expr $I + 1'
done

```

运行脚本：
```
# ./example18.15.sh
loop:1
I=1
loop:2
I=2
...
loop:5
I=5
```
**while 与until区别**：
- while语句先判断条件测试是否为真，如果为真，再执行循环结构中的语句；until语句则先执行一次循环结构，再判断条件测试是否为真。
- 在while语句中，如果条件测试为假，系统就会跳出while语句；在until语句中，只有条件测试为真时才跳出循环。

#### 18.6.3 利用while语句监控系统网络状态
。。。。。。

### 18.7 利用break和continue控制循环

#### 18.7.1 使用break语句控制循环
(1)
```
# cat example18.17.sh
...

I=1

while true
    do
        if [ $I -gt 6 ]
            then
                break
        fi

        echo "I="$I
        I='expr $I + 1 '
done
```
运行脚本：
```
# ./example18.17.sh

I=1
...
I=6

```
(2)
```
# cat example18.17.1.sh


I=1
J=1
# 定义两个无限循环
while true
    do
    while true
        do
            if [ $J -gt 3 ]
                then
                    # 使用break语句跳出两个无限循环
                    break 2
            fi

            echo "I="$I
            echo "J="$J
            J='expr $J + 1'

    done
    I='expr $I + 1'
done

```
运行脚本：
```
# ./example18.17.1.sh
I=1
J=1
...
I=1
J=3

```

#### 18.7.2 使用continue语句控制循环
continue语句并不会退出循环，而是跳过当前循环，开始下一次循环过程。

```
# cat example18.18.sh
...

I=1
J=1

while true
    do
        while true
            do
                if [ $J = 3 ]
                    then
                        echo "use continue"
                        J='expr $J + 1'
                        continue
                fi

                if [ $J -gt 4 ]
                    then

                        break 2
                fi

                echo "I="$I
                echo "J="$J
                J='expr $J + 1 '
        done

        I='expr $I + 1'
done

```

运行脚本：
```
# ./example18.16.18.sh
I=1
...
J=2
use continue
I=1
J=4

```