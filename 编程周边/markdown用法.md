# Markdown笔记
## 一、语法教程
  | 作用 | 用法 |
  |----|----|
  |标题| #（一级标题） |
  |段落|用空行表示|
  |斜体|\*斜体\*|
  |粗体|\*\*粗体\*\*|
  |粗斜体|\*\*\*粗斜体\*\*\*|
  |删除线|\~\~文本\~\~|
  |下划线|\<u>文本\</u>或者* - +3个以上|
  |无序列表|+第一项|
  |有序列表|1.第一项|
  |区块|>|
  |代码|'''python(指定语言)  '''|
  |链接|\[链接名称\](http://baodu.com,'百度')|
  |图片|\![alt 文本\](图片地址)|
  ---
  
  表格: \|表头\|表头|<hr>
        |----|----|<hr>
        |单元格|单元格|


## 二、用VSCode编写Markdown

## 三、在Markdown中用mermaid画图
----

1. 流程图
  ```
  graph [图布局方向]
    start[节点形状、文本] --> end
  ```
### 图形
  可能的方向是：TB BT RL LR TD
### 节点和形状
  常用的节点形状：
  |形状|用法|
  |----|----|
  |默认矩形|id[text]|
  |圆形|id(text)|
  |体育场形状|id([text])|
  |圆形式节点|id((text))|
  |菱形节点|id{text}}|
  
### 节点之间的链接
  |箭头|用法|
  |----|----|
  |箭头链接|A-->B|
  |开放链接|A---B|
  |链接上的文字|A --text---B|
  |链接上的文字|A ---\|text\|B|
  |带有箭头和文字的链接|A -->\|text\|B|
  |虚线链接|A-.->B|
  |带文字的虚线链接|A-.text.->B|
  |粗链接|A==>B|
  |带文字的粗链接|A==text==>B|

#### 子图
```
  subgraph title
    graph definition
  end
```
例子：
```
graph TB
    c1-->a2
    subgraph one
    a1-->a2
    end
    subgraph two
    b1-->b2
    end
    subgraph three
    c1-->c2
    end
```
效果：
``` mermaid
graph TB
    c1-->a2
    subgraph one
    a1-->a2
    end
    subgraph two
    b1-->b2
    end
    subgraph three
    c1-->c2
    end
```
----

2. 类图
>“在软件工程中，统一建模语言（UML）中的类图是一种静态结构图，它通过显示系统的类，其属性，操作（或方法）以及对象之间的关系来描述系统的结构。 。” 维基百科

3. 顺序图
4. 状态图
5.  甘特
6. 饼形图
7. Git

