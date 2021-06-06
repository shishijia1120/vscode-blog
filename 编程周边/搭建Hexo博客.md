# 搭建Hexo博客 的填坑之路······
>Hexo 是一个快速、简洁且高效的博客框架。Hexo 使用 Markdown（或其他渲染引擎）解析文章，在几秒内，即可利用靓丽的主题生成静态网页。

参考
- hexo官方文档：https://hexo.io/zh-cn/docs/index.html
- 超详细Hexo+Github博客搭建小白教程 https://zhuanlan.zhihu.com/p/35668237
## 1. 安装
### 安装前提
- Node.js（Node.js版本需不低于8.10,建议使用Node.js 10.0及以上版本）
- Git
  
### 安装Hexo
   安装前确保已经安装好node.js和Git环境。
```
$ npm install -g hexo-cli
```
#### 问题
- 使用```$ npm install -g hexo-cli```安装太慢
- 改用```$ cnpm install -g hexo-cli```安装过程中，由于我的node版本是v6.11.3，一直会提醒我node>=8，安装完毕后，输入```$ hexo -v```，报错：
```
C:\Users\Administrator>hexo -v
G:\environment\node\node_global\node_modules\hexo-cli\node_modules\_chokidar@3.3.1@chokidar\index.js:151
  async remove(item) {
        ^^^^^^

SyntaxError: Unexpected identifier
    at createScript (vm.js:56:10)
    at Object.runInThisContext (vm.js:97:10)
    at Module._compile (module.js:542:28)
    at Object.Module._extensions..js (module.js:579:10)
    at Module.load (module.js:487:32)
    at tryModuleLoad (module.js:446:12)
    at Function.Module._load (module.js:438:3)
    at Module.require (module.js:497:17)
    at require (internal/module.js:20:19)
    at Object.<anonymous> (G:\environment\node\node_global\node_modules\hexo-cli\node_modules\_hexo-fs@2.0.0@hexo-fs\lib\fs.js:6:18)
    at Module._compile (module.js:570:32)
    at Object.Module._extensions..js (module.js:579:10)
    at Module.load (module.js:487:32)
    at tryModuleLoad (module.js:446:12)
    at Function.Module._load (module.js:438:3)
    at Module.require (module.js:497:17)
```  
百度检查hexo版本报错后，没有得到什么答案，又百度node.js版本过低影响安装hexo吗？
一直没有搜索到相关的答案，决定尝试更新node.js版本！！！
### 升级（重新安装）Node.js
百度说，在windows下是没有n模块，不支持通过n模块来更新node.js。只能重新安装node.js
1. 在命令行窗口输入where node，查看现在Node版本安装的路径
2. 在node官网下载与你电脑系统对应的最新的版本，安装地址一定要覆盖原版本的地址
3. 在命令行输入node -v，查看版本是否更新成功
### 再次安装hexo
```
$ npm install -g hexo-cli
```
```
$ hexo -v
```   
成功！！！
   
### 进阶安装和使用
对于熟悉npm的进阶用户，可以仅局部安装hexo包
```
$ npm install hexo
```
安装以后，可以使用以下两种方式执行Hexo:
1. ```npx hexo <command>```
2. 将Hexo所在的目录下的node_modules添加到环境变量之中即可直接使用```hexo <command>```
```
echo 'PATH="$PATH:./node_modules/.bin"' >> ~/.profile
```   
## 2. 本地搭建hexo博客 
安装Hexo完成后，新建文件夹。在该文件夹右键 git bash here
```
$ hexo init 
```
完成之后输入：
```
$ npm install 
$ hexo g //生成静态网页 
```
```
$ hexo server //打开本地服务器
```
之后，浏览器访问http://localhost:4000，即可看到hexo博客页面。

但我又失败了，访问http://localhost，显示无法访问网站。这个问题又搜索不到原因？？？？

最后再看hexo官方文档，在基本操作/服务器中，发现文档中写：
>Hexo 3.0 把服务器独立成了个别模块，您必须先安装 hexo-server 才能使用。
```
$ npm install hexo-server --save
```
再次打开服务器：
```
$ hexo server //打开本地服务器
```
终于成功！！!

新建完成后，指定文件夹的目录如下：
```
.
├── _config.yml
├── package.json
├── scaffolds
├── source
|   ├── _drafts
|   └── _posts
└── themes
```
## 3.将博客托管到Github上
打开博客根目录下的_config.yml文件，这是博客的配置文件，可以修改与博客相关的各种信息。
修改配置：
```
deploy:
  type: git
  repository: https://github.com/username/username.github.io
  branch: master
```
reository修改为你自己的github地址
### 写文章、发布文章
在博客根目录下右键git bash，安装一个扩展```npm i hexo-deployer-git```
输入```hexo new post <title>```，新建一篇文章。
再打开博客目录，可以发现多了一个文件夹和一个.md文件，用来存放图片，和编写markdown文件。
编写完markdown文件后，根目录输入hexo g 生成静态网页，然后输入hexo s可以本地预览效果，最后输入hexo d上传到github上。这是打开你的github.io主页就能看到发布的文章了。

### 绑定域名
现在默认域名是xxx.github.io，如果像弄一个专属域名。购买完域名后，打开github博客项目，点击settings，拉到下面Custom domain处。填上自己的域名这时候你的项目根目录应该会出现一个名为CNAME的文件了。如果没有的话，打开你本地博客/source目录，我的是D:\study\program\blog\source，新建CNAME文件，注意没有后缀。然后在里面写上你的域名，保存。最后运行hexo g、hexo d上传到github。
