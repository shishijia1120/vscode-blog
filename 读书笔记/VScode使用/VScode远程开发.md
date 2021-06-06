## VScode远程开发
VSCode文档：https://code.visualstudio.com/docs


VSCode提供了三种远程开发：SSH、Docker、WSL。


### SSH
> 引用：https://www.zhihu.com/search?type=content&q=vscode%20Remote%20Dev%E6%8F%90%E4%BE%9B%E4%BA%86%E4%B8%89%E7%A7%8D%E8%BF%9C%E7%A8%8B%E5%BC%80%E5%8F%91

#### 为什么使用远程开发
1. 开发环境与本地解耦，更换电脑不影响开发。
2. 服务器的网络速度和稳定性往往优于你的PC、npm install、git clone等命令会节省你非常多的时间。
3. 本地的计算压力小，内存压力小。
4. 保留了VSCode桌面端的完美体验的同时，还可以享受linux环境带来的便捷开发环境体验。
5. 保证开发环境和部署环境相同，开发和部署无缝衔接。
6. 方便协作，一个团队可以共享一个服务器，共同对一个服务器进行开发、测试。
7. 对外服务的应用可以直接通过公网访问，方便分享和协作。


#### 具体流程
1. 配置云服务器
2. 配置VSCode
    **安装插件**
    remote development:包含Remote-WSL、Remote-SSH、Remote-Container，这里使用的其实是Remote-SSH插件。
    **安装SSH Client**
    先在本地安装SSH Client，只需在本地打开powershell(管理员身份运行)，输入命令：
    ```# Get-WindowsCapability -Online | ? Name -like 'OpenSSH'```
    返回结果：
    ```
    Name  : OpenSSH.Client~~~~0.0.1.0
    State : NotPresent
    Name  : OpenSSH.Server~~~~0.0.1.0
    State : NotPresent
    ```
    正式安装：
    ```# Add-WindowsCapability -Online -Name OpenSSH.Client~~~~0.0.1.0```
    返回结果：
    ```
    Path          :
    Online        : True
    RestartNeeded : False
    ```

    **配置SSH key**
    打开command prompt，输入命令 cd %USERPROFILE%/.ssh

    查看文件夹：

    配置:ssh-keygen -t rsa -b 4096



3. 开始远程开发
   打开VSCode，按ctrl+shift+p，弹出命令搜索框，搜索remote:
   选择该命令，和我们的远程服务器建立连接：
   在弹出的搜索框里输入我们的用户名@主机ip，然后就会发现VSCode打开；了一个新窗口，提示你输入密码：
   只需输入刚才配置ssh key的时候输入的密码即可。
   点击open folder，就会看到我们服务器的文件，