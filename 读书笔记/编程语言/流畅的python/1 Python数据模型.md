### 1. Python数据模型
#### 1.1 一摞Python风格的纸牌
一个非常简单的例子来展示如何实现__getitme__和__len__这两个特殊方法，通过这个例子我们也能见识到特殊方法的强大。

示例1-1 一摞有序的纸牌
```python
class FrenchDeck:
    ranks=[str(n) for n in range(2,11)]+list('JQKA')
    suits='spades diamonds clubs hearts'.split()

    def __init__(self):
        self.__cards=[Card(rank,suit) for suit in self.suits
                                      for rank in self.ranks]
    
    def __len__(self):
        return len(self._cards)
    
    def __getitem__(self,position):
        return self.__cards[position]
```

可以体会到通过实现特殊方法来利用Python数据模型的两个好处：
- 作为你的类的用户，不必去记住标准操作的各式名称
- 可以更加方便地利用Python的标准库。
  
#### 1.2 如何使用特殊方法
首先明确一点，特殊方法的存在是为了被解释器调用的，你自己并不需要调用它们。也就是说没有my_object.__len__()这种写法，而应该使用len(my_object)。在执行len(my_object)的时候，如果my_object是一个自定义类的对象，那么Python会自己去调用其中由你实现的__len__方法。

然而如果是Python的内置的类型，比如列表(list)、字符串(str)、字节序列(bytearray)等，那么CPython会抄个近路，__len__实际上会直接返回PyVarObject里的ob_size属性。PyVarObject是表示内存中长度可变的内置对象的C语言结构体。直接读取这个值比调用一个方法要快很多。

很多时候，特殊方法的调用是隐式的，比如for i in x:这个语句，背后其实使用的是iter(x),而这个函数的背后则是x.__iter__()方法。当然前提是这个方法在x中被实现了。

通过内置的函数(例如len、iter、str，等等)来使用特殊方法是最好的选择。这些内置函数不仅会调用特殊方法，通常还提供额外的好处，而且对于内置的类来说，它们的速度更快。14.12节中有详细的例子。

##### 1.2.1 模拟数值类型
利用特殊方法，可以让自定义对象通过+进行运算。

abs是一个内置函数，如果输入的是整数或者浮点数，它返回的是输入值的绝对值；如果输入是复数，那么返回这个复数的模。为了保持一致性，我们的API在碰到abs函数的时候，也应该返回该向量的模：

示例1-2：一个简单的二维向量类
```python
from math import hypot

class Vector:
    def __init__(self,x=0,y=0):
        self.x=x
        self.y=y
    
    def __repr__(self):
        return 'Vector(%r,%r)' % (self.x,self.y)

    def __abs__(self):
        return hypot(self.x,self.y)
    
    def __bool__(self):
        return bool(abs(self))
    
    def __add__(self,other):
        x=self.x+other.x
        y=self.y+other.y
        return Vector(x,y)

    def __mul__(self,scalar):
        return Vector(self.x * scalar,self.y * scalar)
```

虽然代码里有6个特殊方法，但这些方法(除了__init__)并不会在这个类自身的代码中使用。一般只有Python的解释器会频繁地直接调用这些方法。

##### 1.2.2 字符串表示形式
Python有一个内置的函数叫repr，它能把一个对象用字符串的形式表达出来以便辨认，这就是“字符串表示形式”。repr就是通过__repr__这个特殊方法来得到一个对象的字符串表示形式的。如果没有实现__repr__，当我们在控制台里打印一个向量的实例时，得到的字符串可能会是<Vector at 0x24ad9eac128>

##### 1.2.3 算术运算符
通过__add__和__mul__，示例1-2为向量类带来了+和*这两个算术运算符。值得注意的是，这两个方法返回值都是新创建的向量对象，被操作的两个向量(self或other)还是原封不动，代码里只是读取了它们的值而已。

##### 1.2.4 自定义的布尔值

#### 1.3 特殊方法一览

...
#### 1.4 为什么len不是普通方法
如果x 是一个内置类型的实例，那么len(x)的速度会非常快。背后的原因是CPython会直接从一个C结构体里读取对象的长度，完全不会调用任何方法。

换句话说，len之所以不是一个普通方法，是为了让Python自带的数据结构可以走后门，abs也是同理。但是多亏了它是特殊方法，我们也可以把len用于自定义数据类型。

#### 1.5 本章小结
通过实现特殊方法，自定义数据类型可以表现得跟内置类型一样，从而让我们写出更具表达力的代码——或者说，更具Python风格的代码。

Python对象的一个基本要求就是它得有合理的字符串表示形式，我们可以通过__repr__和__str__来满足这个要求。前者方便我们调试和记录日志，后者则是给终端用户看的。这就是数据模型中存在特殊方法__repr__和__str__的原因。
...
