# Flask Web开发实战

## 第一部分 基础篇
### 1. 初识Flask
Flask是使用Python编写的Web微框架。Flask有两个主要依赖，一个是WSGI工具集——Werkzeug，另一个是Jinja2模板引擎。
#### 1.1 搭建开发环境
##### 1.1.1 Pipenv工作流
1. 安装pip和Pipenv
   使用pip安装Pipenv:
   pip install pipenv
2. 创建虚拟环境
   在Python中，虚拟环境就是隔离的Python解释器环境。这样做的好处是可以为每个项目创建独立的Python解释器环境，因为不同的项目常常会依赖不同版本的库或Python版本。使用虚拟环境可以保持全局Python解释器环境的干净，避免包和版本的混乱，避免包和版本的混乱，并且可以方便区分和记录每个项目的依赖，以便在新环境下复现依赖环境。

   虚拟环境通常使用Virtualenv来创建，但是为了更方便地管理虚拟环境和依赖包，我们将会使用集成了Virtualenv的Pipenv。首先确保我们当前工作目录在示例程序项目的根目录。
   使用pipenv install命令为当前的项目创建虚拟环境：
   pipenv install
   >这会为当前项目创建一个文件夹，其中包含隔离的Python解释器环境，并且安装pip、wheel、setuptools等基本的包。
   **附注**
   >默认情况下，Pipenv会统一管理所有虚拟环境。在windows系统中，虚拟环境文件夹会在C:\users\Administrator\.virtualenvs\目录下创建。如果你想在项目根目录内创建虚拟环境文件夹，可以设置环境变量PIPENV_VENV_IN_PROJECT，这时名为.env的虚拟环境文件夹将在项目根目录被创建。

   使用pipenv shell命令显示激活虚拟环境：
   pipenv shell
   >当执行pipenv shell或pipenv run命令时，Pipenv会自动会从项目目录下的.env文件中加载环境变量

3. 管理依赖
 在以前我们通常使用pip搭配一个requirements.txt文件来记录依赖。但requirements.txt需要手动维护，在使用上不够灵活。Pipfile的出现就是为了替代难于管理的requirements.txt。

 在创建虚拟环境时，如果项目根目录下没有Pipfile文件，pipenv install命令还会在项目文件夹根目录下创建Pipfile和Pipfile.lock文件，前者用来记录项目依赖包列表，而后者记录了固定版本的详细依赖包列表。当我们使用Pipenv安装/删除/更新依赖包时，Pipfile以及Pipfile.lock会自动更新。

**附注**
 >当需要在一个新环境运行程序时，只需要执行pipenv install 命令。Pipenv就会创建一个新的虚拟环境，然后自动从Pipfile中读取依赖并安装到新创建的虚拟环境中。

##### 1.1.2 安装Flask
pipenv install flask
> Pipenv 会自动帮我们管理虚拟环境，所以在执行pipenv install安装Python包时，无论是否激活虚拟环境，包都会安装到虚拟环境中。相当于在激活虚拟环境的情况下使用pip安装包。只有需要需要在全局环境下安装/更新/删除包，我们才会使用pip。

##### 1.1.3 集成开发环境
 pycharm

#### 1.3 启动开发服务器
flask run
**附注**
>确保执行命令前激活了虚拟环境，复杂需要使用pipenv run flask run命令启动开发服务器。
1. 自动发现程序实例
   一般来说，在执行flask run命令运行程序前，我们需要提供程序实例所在模块的位置。可以直接运行程序，是因为Flask会自动探测程序实例，自动探测存在下面这些规则：
   - 从当前目录寻找app.py和wsgi.py模块，并从中寻找名为app或application的程序实例
   - 从环境变量FLASK_APP对应的值寻找名为app或application的程序实例。
  如果你的程序主模块是其它名称，比如hello.py，那么需要设置环境变量FLASK_APP。
  windows系统中使用set命令：set FLASK_APP=hello
2. 管理环境变量
   Flask的自动发现程序实例机制还要第三条规则：如果安装了python-dotenv，那么在使用flask run或其他命令时会自动使用它自动从.flaskenv文件和.env文件中加载环境变量
   **附注**
  > 当安装了python-dotenv时，Flask在加载环境变量的优先级是：手动设置的环境变量>.env中设置的环境变量>.flaskenv设置的环境变量。
  >环境变量在新创建命令行窗口或重启电脑后就清除了，每次都要重设变量有些麻烦。而且如果你同时开发多个Flask程序，我们可以使用python-dotenv管理项目的环境变量，首先使用Pipenv将它安装到虚拟环境：pipenv install python-dotenv

我们在项目根目录下公开创建两个文件：.env和.flaskenv。.flaskenv用来存储和Flask相关的公开环境变量，比如FLASK_APP；而.env用来存储包含敏感信息的环境变量，比如Email服务器的账户名和密码。在.flaskenv或.env文件中，环境变量使用键值对的形式定义，每行一个，以#开头的为注释，如下所示：
SOME_VAR=1
FOO="BAR"
**注意**
>.env包含敏感信息，除非是私有项目，否则绝对不能提交到Git仓库中。当你开发一个新项目时，记得把它的名称添加到.gitignore文件中，这会告诉Git忽略这个文件。gitignore文件是一个名为.gitignore的文本文件，它存储了项目中Git提交时的忽略文件规则清单。

##### 1.3.2 更多的启动选项
1. 使服务器外部可见
   在run命令后添加--host选项将主机地址设为0.0.0.0使其对外可见：
   $ flask run --host=0.0.0.0
   这会让服务器监听所有外部请求。个人计算机一般没有公网IP(公有地址)，所以你的程序只能被局域网内的其他用户通过你的个人计算机内网IP访问。
   >把程序安装在拥有公网IP的服务器上，让互联网上的所有人都可以访问。如果你迫切想要把你的程序分享给朋友们，可以考虑使用ngrok、Localtunnel等内网穿透/端口转发工具。
2. 改变默认端口
   Flask提供的Web服务器默认监听端口5000端口，你可以在启动时传入参数来改变它：
   $ flask run --port=8000
   **附注**
   >执行flask run 命令时的host和port选项也可以通过环境变量FLASK_RUN_HOST和FLASK_RUN_PORT设置。事实上，Flask内置的命令都可以使用这种模式定义默认选项值，即FLASK_\<COMMAND>_\<OPTION>

##### 1.3.3 设置运行环境
   开发环境和生产环境。为了区分程序运行环境，FLASK提供了一个FLASK_ENV环境变量用来设置环境，默认为production(生产)。在开发时，我们可以将其设为development(开发)，这会开启所有支持开发的特性。为了方便管理，我们将把环境变量FLASK_ENV的值写入.flaskenv文件中：
   FLASK_ENV=development

   **注意**
   >在生产环境中部署程序时，绝不能开启调试模式。

#### 1.4 Pyton Shell
在开发Flask程序时，我们并不会直接使用python命令启动Python shell，而是使用flask shell命令：
**注意**
>和其他flask命令相同，执行这个命令前我们要确保程序实例可以被正常找到。

使用flask shell命令打开的Python shell自动包含程序上下文，并且已经导入app实例：
```
>>> app
<Flask 'app'>
>>> app.name
'app'
```
上下文可以理解为环境。为了正常运行程序，一些相关的状态和数据需要被临时保存下来，这些状态和数据被统称为上下文。在Flask中，上下文有两种，分别为程序上下文和请求上下文。

#### 1.6 项目配置
在很多情况下，你需要设置程序的某些行为，这时你需要使用配置变量。
在一个项目中，你会用到许多配置：Flask提供的配置，扩展提供的配置，还要程序特定的配置。这些配置变量都通过Flask对象的app.config属性作为统一的接口来设置和获取，它指向的Config类实际上是字典的子类。

#### 1.8 Flask命令
自定义flask命令，通过创建任意一个函数，并为其添加app.cli.command()装饰器，就可以注册一个flask命令。

### 2. Flask和HTTP
HTTP定义了服务器和客户端之间信息交流的格式和传递方式。

#### 2.1 请求响应循环
#### 2.2 HTTP请求
URL组成部分，如http://helloflask.com/hello?name=Grey：
|信息|说明|
|----|----|
|信息|说明|
|http://|协议字符串，指定要使用的协议|
|helloflask.com|服务器的地址(域名)|
|/hello?name=Grey|要获取的资源路径(path)，类似UNIX的文件目录结构|

##### 2.2.1 请求报文
当我们在浏览器中访问这个URL时，随之产生的是一个发向所在服务器
的请求。请求的实质是发送到服务器上的一些数据，这种浏览器与服务器之间交互的数据被称为报文(message)，请求时浏览器发送的数据被称为请求报文(request message)，而服务器返回的数据被称为响应报文(request message)。




### 5. 数据库






## 第二部分 实战篇
### 7. 留言板
#### 7.1 使用包组织代码
在Python中，每一个有效的Python文件(.py)都是模块。每一个包含__init__.py文件的文件夹都被视作包，包让你可以使用文件夹来组织模块。__init__.py文件通常被称作构造文件，文件可以为空，也可以用来放置包的初始化代码。当包或包内的模块被导入时，构造文件将自动执行。

##### 7.1.1 配置文件
在Flask中，配置不仅可以通过config对象直接写入，还可以从文件中读取，常被命名为config.py。当在单独的文件中定义配置时，不再使用config对象添加配置，而是直接以键值对的方式写出，和保存环境变量的.flaskenv文件非常相似。

##### 7.1.2 创建程序实例
使用包组织程序代码后，创建程序实例、初始化扩展等操作可以在程序包的构造文件(__inti__.py)中实现。




## 第三部分 进阶篇
### 12. 自动化测试




### 13. 性能优化


### 14. 部署上线
部署指的是把程序托管到拥有公网IP的远程服务器（计算机）上，这样程序才可以被互联网上所有人通过IP或映射的域名访问到。
#### 14.1 传统部署VS云部署
- 传统部署
  自己购买/租用远程服务器，然后把程序安装到服务器上的过程。传统部署比较灵活，一切都由你自己来掌控，不过同时也需要耗费较多的精力去进行环境搭设和维护。
- 云部署
  云部署即PaaS。云部署服务提供了一个完善的平台，提供了所有底层继承设施，我们只需要推送程序代码即可。使用云部署可以省去配置服务器、设置数据库、配置网络服务器以及设置防火墙等步骤。使用简单的方式即可集成第三方工具、添加数据库、设置邮件服务等，使用方式非常灵活。当然，云部署的价格一般要比传统部署要高。
  比较流行的又有PaaS有Heroku、PythonAnywhere

#### 14.2 基本部署流程
无论是使用传统部署还是云部署，我们都要考虑如何将程序代码推送到服务器中，并考虑如何推送更新。部署时所使用的工具和开发时会有所不同。

部署方式：
- (1)Flask官方推荐将程序像Python包那样添加一个setup.py文件，然后通过打包构建生成分发包，将分发包上传到服务器并安装到虚拟环境中。
实际上，这种方式引入了不必要的复杂度。对于程序来说，通过Git来推送代码的方式更加简单。

- (2)如果你将程序代码托管在在线代码托管平台（比如Gthub、Gitlab等），那么使用Git部署程序的过程非常简单，和你在自己的电脑运行代码的过程基本相同，流程大致如下：
  - 1. 在本地执行测试
  - 2. 将文件添加到Git仓库并提交
  - 3. 在本地将代码推送到代码托管平台
  - 4. 在远程主机上从代码托管平台复制程序仓库
  - 5. 创建虚拟环境并安装依赖
  - 6. 创建实例文件夹，添加部署特定的配置文件或是创建.env文件存储环境并导入
  - 7. 初始化程序和数据库，创建迁移环境
  - 8. 使用Web服务器运行程序

- (3)除了使用Python包和Git进行部署，另外一种逐渐流行的方式是使用容器技术部署程序。简单地说，借助容器管理系统，比如Docker(https://www.docker.com/)，我们可以在本地开发时就把程序以及各种操作系统在内的所有依赖封装成镜像，这样可以直接运行在各种服务器环境中，省去了重复的调试和部署操作。

#### 14.3 部署前的准备
##### 14.3.1 更新程序配置
生产环境下需要不同的配置，我们在开发时已经通过使用Python类对生产配置进行了分离，并且对某些包含敏感信息的配置变量优先从环境变量读取，比如数据库URL、Email服务器配置信息等，在部署到远程主机上后，我们仍然通过将环境变量写到.env文件来设置关键配置，现在，我们的任务是将这些信息提前写到本地.env文件。

首先，我们需要为保存程序密钥的SECRET_KEY配置变量生成一个随机字符，更换开发时填入的占位字符，比如：
```
SECRET_KEY=\X8DYai\x06r....
```

随机密钥的生成方式有很多，比如，os模块的urandom()方法可以用来生成随机密码，它接受字节长度作为参数：
```python
>>> import os
>>> os.urandom(12)
'\xf0....'
```
复制返回的字符串作为密钥使用就可以了。

如果你使用Python3.6版本，那么可以使用secrets模块提供的token_bytes()、toekn_hex()、token_urlsafe()方法，这些方法接受字节长度作为参数，比如：
```python
>>> import secrets
>>> token_urlsafe(16)
'....'
```
另外，我们也可以使用uuid模块来生成随机字符：
```python
>>> import uuid
>>> uuid.uuid4().hex
'....'
```

在生产环境下我们仍需要执行某些flask命令，而执行flask命令需要正确设置FLASK_APP环境变量。这个变量在我们项目根目录下的.flaskenv文件中已经定义，并且这个文件被提交到Git仓库中，所以不需要重复写入.env文件中。

**注意**
在生产环境下，我们需要将FLASK_CONFIG变量设置为production，这可以确保在。。。


.env文件包含敏感信息，不能提交进Git仓库。你可以考虑在远程主机上重新创建这个文件，将本地内容复制过去。

##### 14.3.2 创建生产环境专用的程序实例
生产环境下的程序自然要加载生成配置，我们需要在项目的根目录下创建一个wsgi.py脚本（这里的命名只是约定，你可以使用其他名称），在这个模块中使用工厂函数create_app()创建一个程序实例，传入生产环境配置名为production。
```python
from ... import create_app
app=create_app('production')
```

这个程序实例专用于部署时运行。在生产环境下，我们需要使用生产服务器运行实例，这时就可以从这个文件中导入这个程序实例：
```python
from foo_server import serve
from wsgi import app

serve(app,'0.0.0.0:80')
```

##### 14.3.3 设置迁移工具
```
pipenv install flask-migrate
```
在extensions.py脚本中实例Migrate类，在工厂函数中对该实例调用init_app()方法，传入app和db对象，
```python
$ flask db init
$ flask db migrate -m "Initial migration"
```
> 对于要部署到Heroku的程序来说，生成迁移文件夹和创建迁移脚本的操作必须在本地进行。

##### 14.3.4 程序日志
在生产环境下，当程序出现错误时，用户会看到一个错误页面，但我们开发人员却什么也不知道。这时把错误信息记录下来会有助于调试和修复。在开发时，我们可以通过Werkzeug内置的调试器来查看错误堆栈，或在命令行输出中查看日志。但是在生产环境中，我们没法使用上面的方式获取日志，这时就需要记录日志。


##### 14.3.5 手动导入环境变量
在开发时，因为安装了python-dotenv，使用flask run 命令启动开发服务器时Flask会自动导入存储在.flaskenv或.env文件中的环境变量。在生产环境下，我们需要使用性能更高的生产服务器，所以不能再使用这个命令启动该程序，这时我们需要手动导入环境变量。

我们应该尽可能
。。。。

##### 14.3.6 HTTPS转发
。。。
#### 14.4 部署到Linux服务器(基于Ubuntu)
传统部署就意味着我们要自己搭建一个服务器环境。在此之前，你需要做下面这些服务：
1. 租用一个远程主机。租用成功后你会获得主机IP和root密码
   选择要安装的服务器操作系统时，建议选择Linux Ubuntu16.04.4LTS
2. (可选)购买一个域名
3. (可选)域名解析
  
##### 14.4.1 使用OpenSSH登录远程主机
当你获取了远程主机的IP和root密码，就可以使用OpenSSH来连接服务器：
```
$ ssh root@your_server_ip
```
**附注**
> SSH是一种用于远程连接Linux主机的加密协议。这里的OpenSSH是基于SSH协议实现的开源程序，Ubuntu内置了这个软件。

如果你使用Windows系统，那么可以使用PuTTY替代，或是使用Git Bash内置的OpenSSH。

##### 14.4.2 安装基本库和工具
连接到远程主机后，首先更新系统可安装的包列表，并对可升级的包进行升级：
```
$ apt update
$ apt upgrade
```
使用Root用户部署代码或运行Web服务器容易带来安全风险，我们可以创建一个新用户，并赋予其root权限（超级用户）:
```
$ adduser greyli
$ usermod -aG sudo greyli
```
现在切换到新创建的用户：
```
$ su greyli
```
接着需要安装必备的包和开发工具，在命令前添加sudo以执行管理员操作。如果你使用Python3，则使用下面的命令：
```
$ sudo apt install python3-dev python3-pip
```
上面命令中的python(3)-dev包含Python2/3和一些基础的包，python(3)-pip用来安装pip。安装过程中会请求输入y来进行确认，你也可以在apt install命令后添加-y选项来省略这个确认。

下面使用pip3(如果你使用python2，这里则使用pip)安装Pipenv
```
$ sudo -H pip3 install pipenv
```

**附注**
>如果你不想全局安装，可以添加--user选项执行用户安装(即pip install --user pipenv)

##### 14.4.3 安全防护措施
我们要对服务器进行一些安全设置，让我们从最基本的方面入手——使用SSH密钥(SSH key)来代替密码作为认证方式。

1. 使用SSH密钥登录
  通过输入密码来登录远程主机比较麻烦，而且不安全，更安全和方便的做法是通过SSH密钥进行认证，为此你需要在你自己的电脑上先生成一个SSH密钥对。你可以新创建一个命令行会话，通过OpenSSH内置的ssh-keygen来生成SSH密钥对：
```
$ ssh-keygen
```
如果你使用Windows系统，可以使用Git Bash来执行上面的操作。生成完成后，你会得到两个保存密钥的文件：
.id_ras.pub:保存你的公钥(public key)，可以用来提供给第三方作为你的认证凭据
.id_ras:保存你的私钥(private key)，用来在认证时进行配对，不要公开这个文件。
**提示**
>密钥默认保存到home目录(~)下的.ssh文件夹中，即~/.ssh。在Linux或macOS中类似home/greyli/.ssh，在Windows中类似C/Users/Administrator/..sh

现在你需要把公钥保存到远程主机上，具体来说，就是将公钥(id_rsa.pub)的内容添加到远程主机的~/.ssh/authorized_keys文件中。最简单的方式是通过ssh-copy-id程序，输入你的远程主机地址作为参数：
```
$ ssh-copy-id greyli@123.45.67.89
...
```
输入密码后，就会看到添加成功的提示。然后在远程主机使用下面的命令给相应目录设置合适的权限：
```
$ chmod go-w ~/
$ chmod 700 ~/.ssh
$ chmod 600 ~/.ssh/authorized_keys
```
2. 关闭密码登录
   既然我们可以不用输入密码就能登录远程主机，那么有必要关闭密码登录功能，这样就可以大幅度提高安全系数。
3. 设置防火墙
   Ubuntu默认安装了ufw，即Uncomplicated Firewall，我们需要使用它来设置开放的端口：
   ```
   $ sudo ufw allow 22
   $ sudo ufw allow 80
   $ sudo ufw allow 443
   ```

##### 14.4.4 推送代码并初始化程序环境
下一步是把我们的程序上传到服务器，这可以有很多种方式实现。
因为我们将实例程序代码托管在Github上，所以最简单的方式还是直接从Github的Git服务器复制仓库到远程主机：
```
$ cd ~
$ git clone https://github.com/greyli/bluelog.git
```
切换进仓库目录，使用Pipenv创建虚拟环境并安装依赖，最后激活虚拟环境：
```
$ cd bluelog
$ pipenv install
$ pipenv shell
```
在程序的配置文件中，包含敏感信息的配置都从环境变量中读取。在开发时，我们将这些环境变量定义在.env文件夹中。在部署时，为了让程序正常运行，我们需要在远程主机的项目目录中也创建一个.env文件，并将本地的.env文件内容复制到这个文件中：
```
$ nano .env
```
为了确保执行命令时配置和环境正确设置，我们还需要在.env文件中为FLASK_ENV变量和自定义的FLASK_CONFIG变量设置正确的值：
```
FLASK_ENV=production
FLASK_CONFIG=production
```
最后我们需要执行程序的初始化操作，如果你使用Flask-Migrate扩展来设置迁移环境，那么使用下面的命令还可以更新数据库：
```
$ flask db upgrade
```
如果没有使用Flask-Migrate，那么就使用下面的命令创建数据库表：
```
$ flask initdb
```
初始化程序
```
$ flask init
```
##### 14.4.5 使用Gunicorn运行程序
在开发时，我们使用flask run命令启动的开发服务器是由Werkzeug提供的。细分的话，Werkzeug提供的这个开发服务器应该被称为WSGI服务器，而不是单纯意义上的Web服务器。在生产环境中，我们需要一个更强健、性能更高的WSGI服务器。这里使用Gunicorn，先在远程主机中使用Pipenv安装它：
```
$ pipenv install gunicorn
```
为了方便进行测试，我们可以临时设置


部署连接：
1. https://www.oldlee.cn/forum.php?mod=viewthread&tid=230
2. https://www.cnblogs.com/Ray-liang/p/4173923.html
3. https://www.cnblogs.com/amberhome-wei/p/12701448.html（搭建Drupal网站）
4. https://www.javazhiyin.com/41606.html
  (比较好)
5. https://blog.csdn.net/weixin_39212776/article/details/81318553
6. https://www.cnblogs.com/cerofang/p/11122286.html
