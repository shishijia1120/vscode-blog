# Python小结之自定义序列

----

## 自定义序列类型Vector


实现如此自然的行为，考的不是继承，而是鸭子类型：我们只需按照预定行为实现对象所需的方法即可。
在Python中创建功能完善的序列类型无需使用继承，只需实现符合序列协议的方法。
在面向对象编程中，协议是非正式的接口，只在文档中定义，在代码中不定义。例如，Python的序列协议只需要__len__和__getitem__两个方法。任何类，只要使用标准的签名和语义实现了这两个方法，就能用在任何期待序列的地方，不管它是否是谁的子类。我们说它是序列，因为它的行为像序列，这才是重点。



我们希望自定义序列实现的效果：

9 符合Python风格的对象：

10 序列的修改、散列和切片：切片、散列、修改、格式化

13 重载运算符：一元运算符、中缀运算符(如+ 和* 、比较运算符、增量赋值运算符）


----
### 9 符合Python风格的对象
**实现功能：**
- 所有用于获取字符串和字节序列表示形式的方法:\__repr__、\__str__、\__format__和__bytes__。
- 把对象转换成数字的几个方法：\__abs__、\__bool__和__hash__。
- 用于测试字节序列转换和支持散列(连同__hash__方法)的__eq__运算符。


----


#### 9.1 对象表现形式
每门面向对象的语言至少都有一种获取对象的字符串表现形式的标准方式，Python提供了两种方式。
- repr():以便于开发者理解的方式返回对象的字符串表示形式。
- str():以便于用户理解的方式返回对象的字符串表示形式。

为了给对象提供其他的表示形式，还会用到另外两个特殊方法：\__bytes__和__format__。bytes()函数调用它获取对象的字节序列表示形式。而__format__方法会被内置的formt()函数和str.format()方法调用，使用特殊的格式代码显示对象的字符串表示形式。




#### 9.2 再谈向量类

为了说明用于生成对象表现形式的众多方法。我们将使用一个Vector2d类，接下来我们将会不断实现这个类。

我们期望Vector2d实例具有的基本行为如下所示：
1. Vector2d实例的分量可以直接通过属性访问(无需调用读值方法)。
```
>>> v1=Vector2d(3,4)
>>> print(v1.x,v1.y)
 3.0 4.0
```

2. Vector2d实例可以拆包成变量元组。

3. repr函数Vector2d实例，得到的结果类似于构建实例的源码。

```
>>> v1
Vector2d(3.0,4.0)
```
4. 这里使用eval函数，表明repr函数调用Vector2d实例得到的是对构造方法的准确表述。

5. Vector2d实例支持使用==比较，这样便于测试。
```
>>> v1_clone=eval(repr(v1))
>>> v1=v1_clone
True
```

6. print函数会调用str函数，对Vector2d来说，输出的是一个有序对。
```
>>> print(v1)
(3.0,4.0)
```

7. bytes函数会调用__bytes__方法，生成实例的二进制表示形式。
```
>>> octets=bytes(v1)
>>> octets
b'd\\x00\\x00\\x00\\x00\\xoo...'

```

8.  abs函数会调用__abs__方法，返回Vector2d实例的模。
```
>>> abs(v1)
5.0
```

9. bool函数会调用__bool__方法，如果Vector2d实例的模为零，返回False，否则返回True。
```
>>> bool(v1), bool(Vector2d(0,0))
(True,False)
```

----

**如何实现上述行为：**

from array import array
import math

class Vector2d:
    typecode='d'

(1). typecode是类属性。在Vector2d实例和字节序列之间转换时使用。

    def __init__(self,x,y):
        self.x=float(x)
        self.y=float(y)

(2). 在__init__方法中把x和y转换成浮点数，今早捕获错误，以防调用Vector2d函数时传入不当参数。

    def __iter__(self):
        return (i for i in (self.x,self.y))

(3). 定义__iter__方法，把Vector2d实例变成可迭代对象。这样才能拆包。这个方法的实现方式很简单。直接调用生成器表达式一个接一个产出分量。

    def __repr__(self):
        class_name=type(self).__name__
        return '{}({!r},{!r})'.format(class_name,*self)

(4). __repr__方法使用{!r}获取各个分量的表示形式，然后插值，构成一个字符串；因为Vector2d实例是可迭代对象，所有*self会把x和y分量提供给format函数。

    def __str__(self):
        return str(tuple(self))
(5). 从可迭代的Vector2d实例中可以轻松地得到一个元组，显示为一个有序对/

    def __bytes__(self):
        return (bytes([ord(self.typecode)]) + 
                bytes(array(self.typecode,self)))
(6). 为了生成字节序列，我们把typecode转换成字节序列，然后迭代Vector2d实例，得到一个数组，再把数组转换成字节序列。


    def __eq__(self,other):
        return tuple(self) == tuple(other)

(8). 为了快速比较所有分量，在操作数中构建元组。对Vector2d实例来说，可以这样做，不过仍有问题。如Vector(3,4) == [3,4].


    def __abs__(self):
        return math.hypot(self.x,self.y)

(9). 模是x和y分量构成的直角三角形的斜边长


    def __bool__(self):
        return bool(abs(self))

(10). __bool__方法使用abs(self)计算模，然后把结果转换成布尔值。因此，0.0是False，非零值是True。


----

#### 9.3 备选构造方法
我们可以把Vector2d实例转换成字节序列；同理，也应该能把从字节序列转换成Vector2d实例。在此使用array.array有个类方法.frombytes。
```
@classmethod
(1) 类方法使用classmethod装饰器修饰。

def frombytes(cls,octets):
    (2) 不用传入self参数；相反，要通过cls传入类本身。

    typecode=chr(octets[0])
    (3) 从第一个字节中读取typecode

    menv=memoryview(octets[1:]).cast(typecode)
    (4) 使用传入的octets字节序列创建一个memoryview，然后使用typecode转换。
    
    return cls(*menv)
    (5) 拆包转换后的memoryview，得到构造方法所需的一对参数。


```
----

#### 9.4 classmethod与staticmethod

classmethod：定义操作类，而不是操作实例的方法。
classmethod最常见的用途是定义备选构造方法，按照约定，类方法的第一个参数名为cls。

staticmethod装饰器也会改变方法的调用方式，但是第一个参数不是特殊的值。其实静态方法就是普通的函数，只是碰巧在类的定义体中，而不是在模块层定义。

**比较classmethod和staticmethod的行为：**
```
class Demo:
    @classmethod
    def klasssmeth(*args):
        return args
    
    @staticmethod
    def staticmeth(*args):
        return args

>>> Demo.klassmeth()
(<class '__main__.Demo'>,)

>>>Demo.klassmeth('spam')
(<class '__main__.Demo'>,'spam')

不管怎样调用 Demo.klassmeth，它的第一个参数始终是Demo类。

>>> Demo.statmeth()
()

>>>  Demo.statmeth('spam')
('spam')

Demo.statmeth的行为与普通的函数相似。
```

classmethod装饰器非常有用，但是却几乎没有不得不与staticmethod的情况。


----
#### 9.5 格式化显示

。。。。。。


----

#### 9.6 可散列的Vector2d
要想创建可散列的类型，不一定要实现特性，也不一定要保护实例属性。只要正确地实现__hash__和__eq__方法即可。但是，实例的散列值绝不应该变化，因此我们借机提到了只读特性。




为了把Vector2d实例变成可散列的，必须使用__hash__方法(还需要__eq__方法，前面已经实现了)。此外，还要让向量不可变。

1. 为此，我们要把x和y分量设为只读特性：
```
class Vector2d:
    typecode='d'

    def __init__(self,x,y):
            self.__x=float(x)
            self.__y=float(y)

(1) 使用两个前导下划线(尾部没有下划线，或者有一个下划线)，把属性标记为私有的。
    
    @property
    def x(self):
        return self.__x

(2) @property装饰器把读值方法标记为特性
(3) 读值方法与公开属性同名，都是x。
(4) 直接返回self.__x。

    @property
    def y(self):
        return self.__y

    def __iter__(self):
        return (i for i in (self.x,self.y))
(6) 需要读取x和y分量的方法可以保持不变通过self.x和self.y读取公开特性，而不必读取私有属性，因此上述代码清单省略了这个类的其他代码。

```







2. 实现__hash__方法


```
def __hash__(self):
    return hash(self.x) ^ hash(self.y)
```




----
#### 9.7 Python的私有属性和"受保护的"属性

#### 9.8 使用__slots__类属性节省空间


#### 9.9 覆盖类属性






----

### 10 序列的修改、散列和切片
**实现功能：**

- 基本的序列协议——\__len__和__getitem__
- 正确表述拥有很多元素的实例
- 适当的切片支持，用于生成Vector实例
- 综合各个元素的值计算散列值
- 自定义的格式语言扩展

此外，还将通过__getattr__方法实现属性的动态存取，以次取代Vector2d使用的只读特性。


----

#### 10.4 Vector类第2版：可切片的序列


```
class Vector：

    ...

    def __len__(self):
        return len(self._components)

    def __getitem__(self,index):
        return self._components[index]
```

添加了这两个方法，就能执行下述操作了：
```
>>> v1=Vector([3,4,5])
>>> len(v1)
3
>>> v1[0],v1[-1]
(3.0,5.0)
>>> v7=Vector(range(7))
>>> v7[1:4]
array('d',[1.0,2.0,3.0])

```


可以看到，现在连切片都支持了。不过尚不完美。如果Vector实例的切片也是Vector实例，而不是数组，那就更好了。对Vector来说，如果切片生成普通的数组，将会缺失大量功能。

为了把Vector实例的切片也变成Vector实例，我们不能简单地委托给数组切片。我们要分析传给__getitem__方法的参数，做适当的处理。

##### 10.4.1 切片原理
。。。。。。
##### 10.4.2 能处理切片的__getitem__方法
为了让Vector表现为序列所需的两个方法:__len__和__getitem__(后者现在能正确地处理切片了)。
```
def __len__(self):
    return len(self._components)

def __getitem__(elf,index):
    cls=type(self)

(1) 获取实例所属的类(级Vector)

    if isinstance(index,slice):
        return cls(self._components[index])
(2) 如果index参数的值是slice对象，调用类的构造方法，使用_components数组的切片构建一个新Vector实例。

    elif isinstance(index,numbers.Integral):
        return self._components[index]
(3) 如果index是int或其他整数类型，那就返回_components中相应的元素。

    else:
        msg='{cls.__name__} indices must be integers'
        raise TypeError(msg.format(cls=cls))
(4) 否则，抛出异常。
```




----

#### 10.5 Vector类第3版：动态存取属性


。。。。。。
1. 添加__getattr__方法


**添加__getattr__方法：**
```
shortcut_names = 'xyzt'
def __getattr__(self,name):
    cls=typr(self)
    (1) 获取Vector，后面待用

    if len(name) ==1:
    (2) 如果属性名只有一个字谜，可能是shortcut_names中的一个

        pos cls.shortcut_names.find(name)
        (3) 查找那个字母的位置：str.find还会定位'yz'，但是我们不需要，因此在前一行做了测试。

        if 0<= pos <len(self._components):
        (4) 如果位置都在范围内，返回数组中对应的元素。

            return self._components[pos]
    
    msg='{.__name__!r} object has no attributes {!r}'
    (5) 如果测试都失败了，抛出AttributeError，并指明标准的消息文本。

    raise AttributeError(msg.format(cls,name))
```




2. 改写Vector类中设置属性的逻辑，实现__setattr__方法

**实现__setattr__方法：**
```
def __setattr__(self,name,value):
    cls=type(self)
    。。。。。。


```


----
#### 10.6 Vector类第4版：散列和快速等值测试
我们要再次实现__hash__方法，加上现有的__eq__方法，这会把Vector实例变成可散列的对象。

1. 实现__hash__方法：

。。。。。。


```
from array import array
import reprlib
import math
import functools
import operator

class Vector:
    typecode = 'd'

    def __eq__(self,other):
        return tuple(self) = tuple(other)

    def __hash__(self):
        hashes=(hash(x) for x in self._components)
        (1) 创建一个生成器表达式，惰性计算各个分量的散列值。

        return fuctools.reduce(operator.xor, hashes,0)
        (2) 把hashes提供给reduce函数，使用xor函数计算聚合的散列值；第三个参数，0是初始值。

```

2. 修改__eq__方法：

对Vector2d(只有两个分量)来说，这是个捷径，但是对维数很多的向量来说情况就不同了。

```
def __eq__(self,other):
    if len(self) != len(other)；
        return False
    for a,b in zip(self,other):
        if a!=b:
            return False
    return True
```
zip函数生成一个由元组构成的生成器，元组中的元素来自参数传入的各个可迭代对象。

**出色的zip函数：**

。。。。。。


还可以使用all函数替换for循环：

**使用zip和all函数实现__eq__方法：**
```
def __eq__(self,other):
    return len(self) == len(other) and all(a ==b for a,b in zip(self,other))
```

----
#### 10.7 Vector类第5版：格式化





----

### 13 正确重载运算符

运算符重载的作用是让用户定义的对象使用中缀运算符(如+和|)或一元运算符(如 - 和~)。说的宽泛一些，函数调用(())、属性访问(.)和元素访问切片([])也是运算符.

#### 13.1 运算符重载基础


- 不能重载内置类型的运算符
- 不能新建运算符，只能重载现有的
- 某些运算符不能重载——is、and、or和not
#### 13.2 一元运算符
下面是这三个运算符和对应的特殊方法：


-  -(__neg__):取负算术运算符。如果x是-2，那么-x==2.
    ```
    def __neg__(self):
        return Vector(-x for x in self)

    ```
-  +(__pos__):取正算术运算符。通常，x == +x，但也有一些例外。
    ```
    def __pos__(self):
        return Vector(self)
    ```

-  ~(__invert__):对整数按位取反。定义为-x == -(x+1)。如果x是2，那么-x == -3。


支持一元运算符很简单，只需实现相应的特殊方法。这些特殊方法只有一个参数，self。然后，使用符合所在类的逻辑实现。不过，要遵守运算符的一个基本规则，始终返回一个新对象。

----

#### 13.3 重载向量加法运算符 +

**中缀运算符特殊方法的分派机制**
对表达式a+b，解释器会执行以下几步操作：
1. 如果a有__add__方法，而且返回值不是NotImplemented，调用a.\__add\__(b)，然后返回结果。
2. 如果a没有__add__方法，或者调用__add__方法返回NotImplemented，检查b有没有__radd__方法，如果有，而且返回值不是NotImplemented，调用b.\__radd\__(a)，然后返回结果。
3. 如果b没有__radd__方法，或者调用__radd__方法返回NotImplemented，抛出TypeError，并在错误消息中指明操作数类型不支持。

如果中缀运算符方法抛出异常，就终止了运算符分派机制。对TypeError来说，通常最好将其捕获，然后返回NotImplemented。这样，解释器会尝试调用反向运算符方法。如果操作数是不同的类型，对调之后，反向运算符方法可能会在正确计算。




**Vector中加法运算符需实现的功能**：
- 两个长度相同的Vector实例相加。
- 如果尝试把两个长度不同的Vector实例加在一起，最好使用零填充较短的那个向量。
- 可以处理Vector对象或任何具有数值元素的可迭代对象。例如整数元组或浮点数数组。




**Vector + 运算符方法**：
```
def __add__(self,other):
 try:
    pairs=itertools.zip_longest(self,other,fillvalue=0.0)
    return Vector(a+b for a,b in pairs)
  except TypeErrpr:
    return NotImplemented

def __radd__(self,other):
    return self + other
```

pairs是个生成器，它会生成(a,b)形式的元组，其中a来自self，b来自other。如果self和other的长度不同，使用生成器表达式计算pairs中各个元素的和。

构建一个新Vector实例，使用生成器表达式计算pairs中各个元素的和。

----

#### 13.4 重载向量乘法运算符 *
V * x ，如果x是数字，就是计算标量积，各个分量都会乘以x——这也叫元素级乘法。如果x是向量，叫两个向量的点积。目前，不重载这种意义的*，只用*计算标量积。


**Vector中乘法运算符需实现的功能**：
- 操作数为数字时，向量可以乘数字
- 操作数不能为复数，但可以是int、bool(int的子类)，甚至fractions.Fraction实例等标量。

我们可以像上节中，采用鸭子类型技术，在__mul__方法中捕获TypeError。但是，这个问题有个更容易理解的方式，而且也更合理：白鹅类型。我们将使用isinstance()检查scalar类型，但是不硬编码具体的类型，而是检查numbers.Real抽象基类。这个抽象基类涵盖了我们所需的全部类型，而且还支持以后声明为numbers.Real抽象基类的真实子类或虚拟子类的数值类型。


**vector:增加*运算符方法**：
```
from array import array
import numbers


class Vector:
    typecode = 'd'

    def __init__(self,components):
        self._components=array(self.typecode,components)

    ...


    def __mul__(self,scalar):
        if isinstance(scalar,numbers.Real):
            return Vector(n * scalar for n in self)
        else:
            return NotImplemented

    def __rmul__(self,scalar):
        return self * scalar

```

(1) 为了检查类型，导入numbers模块。
(2) 如果scalar是number.Real某个子类的实例，用分量的乘积创建一个新Vector实例。
(3) 否则，返回NotImplemented，让Python尝试在scalar操作数上调用__rmul__方法。
(4) 这里，__rmul__方法只需执行self*scalar，委托给__mul__方法。



----


#### 13.5 众多比较运算符
Python解释器对众多比较运算符(==、!=、>、<、>=、<=)的处理与前文类似，不过在两个方面有重大区别。
- 正向和反向调用使用的是同一系列方法。例如，对==来说，正向和反向调用都是__eq__方法，只是把参数对调了；而正向的__gt__方法调用的是反向的__lt__方法，并把参数对调。
- 对==和!=来说，如果反向调用失败，Python会比较对象的ID，而不抛出TypeError。


```
def __eq__(self,other):
    if isinstance(other,Vector):
        return (len(self) == len(other) and
            all(a == b for a,b in zip(self,other)))
    else:
        return NotImplemented
```


**测试**：
```
>>> va=Vector([1.0,2.0,3.0])
>>> t3=(1,2,3)
>>> va == t3
False

```

(1) 为了计算va == t3，Python调用Vector.\__eq\__(va,t3)
(2) 经Vector.\__eq\__(va,t3)确认，t3不是Vector实例，因此返回NotImplemented。
(3) Python得到NotImplemented结果，尝试调用tuple.\__eq\__(t3,va)。
(4) tuple.\__eq\__(t3,va)不知道Vector是什么，因此返回NotImplemented.
(5) 对==来说，如果反向调用返回NotImplemented，Python会比较对象的ID，作最后一搏。


----

#### 13.6 增量赋值运算符


如果一个类没有实现就地运算符，增量赋值运算符只是语法糖：a+=b的作用与a=a+b完全一样，对不可变类型来说，这是预期的行为。而且，如果定义了__add__方法的话，不用编写额外的代码，+=就能使用。

然而，如果实现了就地运算符，例如_iadd__，计算a+=b的结果时会调用就地运算符方法。这种运算符的名称表明，它们会就地修改左操作数，而不会创建新对象作为结果。
不可变类型，如Vector类，一定不能实现就地特殊方法，这是明显事实。




```


class AddableBingoCage()

。。。。。。

 

```


