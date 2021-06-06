## Remote
**关键词**：SSH密钥、使用SSH远程开发、

----
### 1 SSH密钥

**快速入门：使用SSH密钥**
首先我们将创建一个人密钥对，然后将公共密钥复制到主机。

1. 创建本地SSH密钥对
检查本地计算机是否已经有SSH密钥，在Windows下的位置是C:\Users\your-user\\.ssh\id_rsa.pub
如果没有密钥，在本地终端或PowerShell中运行以下命令以生成SSH密钥对:```ssh-keygen -t rsa -b 4096```
\
2. 授权你的Windows计算机连接
连接到macOS或Linux SSH主机：
```
$USER_AT_HOST="your-user-name-on-host@hostname"
$PUBKEYPATH="$HOME\.ssh\id_rsa.pub"
$pubKey=(Get-Content "$PUBKEYPATH" | Out-String); ssh "$USER_AT_HOST" "mkdir -p ~/.ssh && chmod 700 ~/.ssh && echo '${pubKey}' >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys"
```

----

**使用专有钥匙提高安全性**

1. 在其它文件中生成单独的SSH密钥

    Windows:在本地PowerShell中运行以下命令：
    ```ssh-keygen -t rsa -b 4096 -f "$HOME\.ssh\id_rsa-remote-ssh"```
2. 授权你的Windows计算机连接
```  
$USER_AT_HOST="root@47.97.204.176"
$PUBKEYPATH="$HOME\.ssh\id_rsa-remote-ssh.pub"
$pubKey=(Get-Content "$PUBKEYPATH" | Out-String); ssh "$USER_AT_HOST" "mkdir -p ~/.ssh && chmod 700 ~/.ssh && echo '${pubKey}' >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys"
```
3. 修改配置文件

```
Host name-of-ssh-host-here
    User your-user-name-on-host
    HostName host-fqdn-or-ip-goes-here
    IdentityFile ~/.ssh/id_rsa-remote-ssh
```

----
### 2 使用SSH进行远程开发
1. 在终端或PowerShell窗口中运行以下命令(user@hostname指用户名@服务器公网ip)来验证可以连接到SSH主机
2. 从命令面板(F1)中选择Remote-SSH:Connect to Host，输入user@hostname
3. 可能会要求您手动选择类型
选择平台后，它将存储在该属性下的VS Code设置中(/docs/getstarted/settings)，remote.SSH.remotePlatform因此您可以随时对其进行更改。
4. vv
5. 连接后，可以参考状态栏来查看连接到的主机
   连接状态下，单击状态栏项目将提供远程命令列表。


----
#### 2.1 记住主机和高级设置

#### 2.2 管理扩展
VS Code在以下两个位置之一运行扩展：在客户端本地，或在SSH主机远程。

#### 2.3 转发端口/创建SSH隧道
