# VSCode Python使用
**关键词：**虚拟环境、调试、数据科学、测试、Flask、容器中的Python

## 虚拟环境
步骤：创建虚拟环境、选择虚拟环境、激活虚拟环境

**为Flask创建虚拟环境**

创建虚拟环境：Windows：python -m venv env (创建一个env基于当前解释器命名的虚拟环境)
如果不在VS Code的终端下创建虚拟环境，那么在VS code打开该文件夹时需要选择虚拟环境。命令面板中，选择Python:Select Interpreter命令
从命令面板创建新的集成终端(Ctrl+Shift+`)，该命令将创建终端并通过运行其激活脚本自动激活虚拟环境。如果打开单独的命令提示符或终端，Windows下通过命令env\scripts\activate激活环境。

**创建一般虚拟环境**
创建虚拟环境：python -m venv .venv 或 py -3 -m venv .venv
激活虚拟环境：.venv\scripts\activate

**conda环境**
创建conda虚拟环境：conda create -n your_env_name python=X.X
同时安装必要的包：conda create -n env_name numpy matplotlib python=2.7
激活conda虚拟环境：Windows:activate your_env_name
移除conda虚拟环境：conda remove -n your_env_name(虚拟环境名称) --all， 即可删除。


## 调试

## 测试

## 数据科学