# Git
## 1.Git简介
----
### 1.1基本概念

### 2.1创建版本库
```
$ mkdir learngit
$ git init            //变成git可管理的仓库
可创建一个readme.txt
$ git add readme.txt  //把文件添加到仓库
$ git commit -m "write a readme file第一次提交" //提交到本地仓库，-m表示对提交的注释
```
提交后，再改动readme.txt
想要查看readme.txt做了什么修改
```
$ git diff readme.txt
```
修改后，想要重新提交：
```
$ git add readme.txt
$ git commit -m "第二次提交"

也可以直接：
$ git commit -am "第二次提交"
```
### 1.2 版本回退
```
$ git log  //显示从最近到最远的提交日志，HEAD表示当前版本，HEAD^表示上一个版本
$ git reset --hard HEAD^
$ git log  //最初的版本已经看不到
```
如果进行了版本回退后，又想回到之前的版本：
1.如果命令行窗口没有关掉
```
$ git reset --hard <commit id>
```
2.如果窗口关了
```
$ git reflog //找到commit id
$ git reset --hard <commit id>
```
小结：
```
$ git reset --hard <commit id>  //在版本的历史之间穿梭
$ git log    //查看提交历史
$ git relog   //查看命令历史，已确定要回到哪个版本
```
### 1.3管理修改
### 1.4解决冲突
## 2.分支操作
----
### 2.1特性分支 
*特性分支*:集中实现单一特性，除此之外不进行任何作业的分支

### 2.2创建分支
假设开始只有master分支
```
$ git branch     //显示分支一览表
 * master 

$ git checkout -b '分支名'   //创建且切换到新分支
```
创建分支也可以：

```
$ git branch '分支名'   //创建分支

$ git checkout '分支'   //切换分支

$ git checkout -   //切换到上一个分支
```

### 2.3合并分支
假设分支feature-A已经实现完毕，想合并到主干分支master中

```
$ git checkout master   //切换到master分支

$ git merge --no-ff newbranch   //合并分支

$ git log --graph   //以图表形式查看分支
``` 
### 2.4更改提交的操作
### 2.5将本地仓库推送至远程仓库
#### 在github上新建仓库
在github新建一个仓库，仓库名与本地仓库保持一致，注意创建时请**不要**勾选Initialize this respository with a README.md。
先有本地仓库，再关联同名的远程仓库
```

$ git remote add origin git@github.com:username.git //执行后Git将远程仓库的名称设置为origin
```
#### 推送至master分支(在本地master分支下进行操作)：
```
$ git push -u origin master
```
-u:在推送的同时，将origin仓库的master分支设置为本地仓库当前分支的upstream(上游)。将来运行git pull命令从远程仓库获取内容省去了另外添加参数的麻烦。
#### 推送至master以外的分支
```
$ git checkout -b feature-D //在本地仓库创建并切换到分支feature-D
$ git push -u origin feature-D //（当前本地分支为feature-D）推送至远程分支feature-D
```
### 2.6从远程仓库克隆
先有远程仓库，再克隆一个本地仓库
```
$ git clone git@github.com:username.git //获取远程仓库,默认只有master分支
$ git branch -a //-a:同时显示本地仓库和远程仓库的分支信息
    *master
    remotes/origin/HEAD -> origin/master
    remotes/origin/feature-D
    remotes/origin/master 
$ git checkout -b feature-D origin/feature-D //获取远程的feature-D分支
```
向本地的feature-D分支提交更改：
```
$ git diff
$ git commit -am "Add feature-D"
```
推送至远程feature-D分支：
```
$ git push //当前分支为feature-D,由于之前已设置对于的上游远程分支，不需要再写其他参数
```
获取最新的远程仓库分支：
```
$ git  pull //当前分支为feature-D分支，将本地的feature-D分支更新到最新状态
```