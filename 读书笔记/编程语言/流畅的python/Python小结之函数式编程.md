# Python小结之函数式编程


**装饰器和高阶函数**
装饰器是可调用的对象，其参数是另一个函数(被装饰的函数)。装饰器可能会处理被装饰的函数，然后把它返回，或者将其替换成另一个函数或可调用对象。

其实装饰器就是高阶函数(我理解)，不过函数装饰器在导入模块时立即执行，而高阶函数不存在导入和运行的区别。

如果不使用@句法，想像常规函数那样使用，同样也不存在导入和运行的区别。


**闭包和自由变量**
只有涉及嵌套函数时才有闭包问题，其实闭包指延伸了作用域的函数，其中包含函数定义体引用，但是不在定义体中定义的非全局变量。关键是它能访问定义体之外定义的非全局变量。具体实例可见7.5节。


**对象编程和函数式编程**




----
**常见的装饰器类型：**


**1. 装饰器返回的函数与通过参数传入的相同，即装饰器内没有定义函数**

```
def decorate(func):
    print('装饰函数func')
    return func

```

应用：
```
@decorate
def f():
    print('我是f函数')

def main():
    print('main函数')
    f()

if __name__=='__main__':
    main()

```
运行结果：
```
装饰函数func
main函数
我是f函数
```

可以发现，在运行f()函数之前就已经输出装饰器的输出语句。这里的重点是**导入时和运行时之间的区别**。函数装饰器在导入模块时立即执行，而被装饰的函数只在明确调用时运行。



**2.装饰器内部定义函数**
 
大多数装饰器会在内部定义一个函数，然后将其返回。
即装饰器就是一个高阶函数decorate，decorate的参数是被装饰的函数，函数decorate内嵌套一个函数B，decorate的返回值的函数B。

装饰器的定义：
```
def decorate(func):
    def B(*args):
        ...
        return reslut
    return B
```

应用：
```
@decorate
def f(* args):
    ...
```
其实等价于：
```

f=decorate(f)

f其实是函数B的引用
所以f(*args)就是B(*args) (我的理解)

```

**3. 参数化装饰器**



**4. 叠放装饰器**


----

## 5 一等函数
在Python中，函数是一等对象。一等对象定义为满足下述条件的程序实体：
- 在运行是创建
- 能赋值给变量或数据结构中的元素
- 能作为参数传给函数
- 能作为函数的返回结果

在Python中，整数、字符串和字典都是一等对象。模块也是一等对象。

### 5.1 把函数视作对象
Python函数是对象，函数本身是function类的实例。

```
def factorial(n):
    '''return n!'''
    return 1 if n < 2 else n * factorial(n-1)

>>> factorial(42)
1405006117989854314260624451169936384000000000

>>>factorial.__doc__
'return n!'
(2) __doc__是函数对象众多属性中的一个

>>> type(factorial)
<class 'function'>

(3) factorial是function类的实例

>>> fact = factorial
>>> fact
<function factorial at 0x...>
(4) 可以把factorial函数赋值给变量fact，然后通过变量名调用

>>> fact(5)
120
>>> map(factorial,range(11))
<map object at 0x...>
(5) 可以把函数作为参数传递给map函数
```

----

### 5.2 高阶函数
接收函数为参数，或者把函数作为结果返回的函数是高阶函数。
map函数就是一例，内置函数sorted也是：可选的key参数用于提供一个函数，它会应用到各个元素上进行排序。

```
>>> fruits = ['stawberry','fig','apple','cherry','banana']
>>> sorted(fruits,key=len)
['fig','apple','cherry','banana','strawberry']

```

----

### 5.3 匿名函数

lambda关键字在Python表达式内创建匿名函数。

然而，Python简单的句法限制了lambda函数的定义体只能使用纯表达式。即lambda函数的定义体中不能赋值，也不能使用while和try等Python语句。


lambda句法只是语法糖，与def语句一样，lambda表达式会创建函数对象。这是Python中几种可调用对象的一种。

在参数列表中最适合使用匿名函数。
```
>>> fruits = ['stawberry','fig','apple','cherry','banana']
>>> sorted(fruits,key=lambda word : fruits[::-1])
```

----

### 5.4 可调用对象

除了用户定义的函数，调用运算符(即( ))还可以应用到其他对象上。如果想判断对象能否调用。可以使用内置的callable()函数。

Python数据模型文档列出来7种可调用对象：
- 用户定义的函数：使用def语句或lambda表达式创建。
- 内置函数：使用C语言(CPython)实现的函数，如len或time.strftime。
- 内置方法：使用C语言实现的方法。如dict.get。
- 方法：在类的定义体中定义的函数。
- 类：调用类时会运行类的__new__方法创建一个实例，然后运行__init__方法，初始化实例，最后把实例返回给调用方。因为Python没有new运算符，所以调用类相当于调用函数。(通常，调用类会创建那个类的实例，不过覆盖__new__方法的话，也可能出现其他行为。)

- 类的实例：如果类定义了__call__方法。那么它的实例可以作为函数调用。
- 生成器函数：使用yield关键字的函数或方法。调用生成器函数返回的是生成器对象。


Python中有各种各样可调用的类型，因此判断对象能否调用，最安全的方法是使用内置的callable()函数:
```
>>> abs,str,13
(<built.in function abs>, <class 'str'> ,13)

>>> [callable(obj) for obj in (abs,str,13)]
[True,True,False]
```

接下来说明如何把类的实例变成可调用的对象。

----

### 5.5 用户定义的可调用类型

不仅Python函数是真正的对象，任何Python对象都可以表现得像函数。为此，只需实现实例方法__call__。

```
import random

class BingoCage:
    
    def __init__(self,items):
        self._items = list(items)
        (1) __init__接受任何可迭代对象：在本地构建一个副本，防止列表参数的意外副作用。

        random.shuffle(self._items)
        (2) shuffle定能完成工作，因为self._items是列表。


    def pick(self):
        try:
            return self._items.pop()
        except IndexError:
            raise LookupError('pick from empty BingoCage')
        (3) 起主要作用的方法，如果self._items为空，抛出异常，并设定错误信息。

    def __call__(self):
        return self.pick()
        (4) bingo.pick()的快捷方式是bingo() 

```

实现__call__方法的类是创建函数类对象的简捷方式，此时必须在内部维护一个状态，让它在调用之间可用。例如BingoCage中的剩余元素。装饰器就是这样，装饰器必须是函数，而且有时要在多次调用之间"记住"某些事[例如备忘录，即缓存消耗大的计算结果，供后面使用]。


创建保有内部状态的函数，还有一种截然不同的方式——使用闭包。



下面讨论把函数视作对象处理的另一方面：运行时内省。

----

### 5.6 函数内省
除了__doc__，函数对象还有很多属性。的使用dir函数可以探知factorial具有下述属性：
```
>>> dir(factorial)
['__annotations__', '__call__','__closure__','__code__',
'__defaults__'  ,..., '__dict__', '__dir__', '__doc__', '__eq__',
'__format__','__ge__','__getattribute__','__globals__','__hash__',
'__init__','__name__','__ne__','__new__','__repr__','__setattr__','__str__',

]

```

其中大多数属性是Python对象共有的。本节讨论与把函数视作对象相关的几个属性。


**列出常规对象没有而函数有的属性**
```
>>> class C:pass 
>>> obj =C()
>>> def func():pass
>>> sorted(set(dir(func)) -set(dir(obj)))

['__annotations__','__call__','__closure__','__code__',
'__defaults__','__get__','__globals__','__kwdefaults__',
'__name__','__qualname__']
>>>
```

**函数特有属性：**

|名称|类型|说明|
|----|----|---|
| \__annotations__|dict|参数和返回值的注解|
|\__call__|method-wrapper|实现()运算符：即可调用对象协议|
|\__closure__|tuple|函数闭包，即自由变量的绑定(通常是None)|
|\__code__|code|编译成字节码的函数元数据和函数定义体|
|\__defaults__|tuple|形式函数的默认值|
|\__get__|method=wrapper|实现只读描述协议(参加第20章)|
|\__globals__|dict|函数所在模块中的全局变量|
|\__kwdefaults__|dict|仅限关键字形式参数的默认值|
|\__name__|str|函数名称|
|\__qualname__|str|函数的限定名称，如Random.chioce|

后面几节会讨论__defaults__、_-code__和__annotations__属性，IDE和框架使用它们提取关于函数签名的信息。。

----

### 5.7 从定位参数到仅限关键字参数
Python最好的特性之一是提供了极为灵活的参数处理机制，而且Python3进一步提供了仅限关键字参数。与之密切相关的是，调用函数时使用*和**展开可迭代对象，映射到单个参数。




注意，仅限关键字参数不一定要有默认值。

----

### 5.8 获取关于参数的信息



----

### 5.9 函数注解
Python3提供了一种句法，用于为函数声明中的参数和返回值附加元数据。

```
def clip(text:str, max_len:'int > 0'=80) ->str:
    """ 在max_len前面或后面的的第一个空格处截断文本
    """

    end = None
    if len(text) > max_len:
        space_before = text.rfind('',0,max_len)
        if space_before >= 0:
            end =space_before
        else:
            space_after = text.rfind('',max_len)
            if space_after >= 0:
            end =space_after
    if end is None:
        end = len(text)
    return text[:end].rstrip()
```
函数声明中的各个参数可以在 : 之后增加注解表达式。如果参数有默认值，注解放在参数名和=号之间。如果想注解返回值 ，在）和函数声明末尾的：之间添加 ->和一个表达式。那个表达式可以是任何类型。注解中最常用的类型是类(如str或int)和字符串(如'int > 0')。

注解不会做任何处理，只是存储在函数__annotations__属性(一个字典)中：

```
>>> from clip_annot import clip
>>> clip.__annotations__
{'text':<class 'str'>, 'max_len': 'int > 0' ,'return':<class 'str'>} 
```
'return'键保存的是返回值注解。

Python对注解所作的唯一事情是，把它们存储在函数的__annotations__属性里。仅此而已，Python不做检查、不做强制、不做验证、什么操作都不做。换句话说，注解对Python解释器没有任何意义。注解只是元数据，可以供IDE、框架和装饰器等工具使用。也可以使用inspect.signature()函数知道怎么提取注解。


```
>>> from clip_annot import clip
>>> from inspect import signature
>>> sig=signature(clip)
>>> sig.return_annotation
<class 'str'>

>>> for param in sig.parameters.values():
...     note=repr(param.annotation).ljust(13)
...     print(note,':',param.name,'=',param.default)
<class 'str'>:text = <class 'inspect._empty'>
'int > 0' : max_len = 80

```

signature函数返回一个Signature对象，它有一个return_annotation属性和一个parameters属性，后者是一个字典，把参数名映射到Parameter对象上。每个Parameter对象自己也有annotation属性。


----

### 5.10 支持函数式编程的包



#### 5.10.1 operator模块

#### 5.10.2 使用functools.partial冻结参数



----

## 6 使用一等函数实现设计模式

Norvis建议在有一等函数的语言中重新审视"策略" "命令" "模板方法"和"访问者"模式。通常，我们可以把这些模式中涉及的某些类的实例替换成简单的函数，从而减少样板代码。


### 6.1 案例分析：重构"策略"模式
如果合理利用作为一等对象的函数，某些设计模式可以简化，"策略"模式就是其中一个很好的例子。

#### 6.1.1 经典的"策略"模式


《设计模式：可复用面向对象软件的基础》一书中是这样概述"策略"模式的：
>定义一系列算法，把它们一一封装起来，并且使它们可以相互替换。本模式使得算法可以独立于使用它的客户而变化。



"策略"模式的UML类图，其中涉及以下内容：

。。。。。。






- 上下文：把一些计算委托给实现不同算法的可互换组件，它提供服务。在这个电商示例中，上下文是order，它会根据不同的算法计算促销折扣。
- 策略：实现不同算法的组件共同的接口。在这个示例中，名为Promotion的抽象类扮演这个角色。
- 具体策略："策略"的具体子类。

具体策略由上下文类的客户选择。在这个示例中，实例化订单之前，系统会以某种方式选择一种促销折扣策略，然后把它传给Order构造方法。具体怎么选择策略，不在这个模式的职责范围内。


#### 6.1.2 使用函数实现"策略"模式
在上例中，每个具体策略都是一个类，而且都只定义了一个方法，即discount。此外策略实例没有状态(没有实例属性)。

此例中，把具体策略换成了简单的函数，而且去掉了Promo抽象类。






"策略对象通常是很好的享元"。"享元是可共享的对象，可以同时在多个上下文中使用"。共享是推荐的做法，这样不必在每个新的上下文(这里是order实例)中使用相同的策略时不断新建具体策略对象，从而减少消耗。因此，为了避免"策略"模式的一个缺点(运行时消耗)，《设计模式》作者建议再使用另一个模式。但此时，代码行数和维护成本会不断攀升。



在复杂的情况下，需要具体策略维护内部状态时，可能需要把"策略"和"享元"模式结合起来。但是，具体策略一般没有内部状态，只是处理上下文中的数据。此时，一定要使用普通的函数，别去编写一个只有方法的类，再去实现另一个类声明的单函数接口。函数比用户定义的类的实例轻量，而且无需使用"享元"模式，因为各个策略函数在Python编译模块时只会创建一次。普通的函数也是"可共享的对象，可以同时在多个上下文中使用。


至此，我们使用函数实现了"策略模式"，由此也出现了其他可能性。假设我们想创建一个"元策略"，让它为指定的订单选择最佳折扣。

#### 6.1.3 选择最佳策略：简单的方式

```
promos = [fidelity_promo,bulk_item_promo,large_order_promo]
(1) promos列出以函数实现的各个策略

def  best_promo(order):
    """ 选择可用的最佳折扣
    """
    return max(promo(order) for promo in promos)
```

上例可用，而且易于阅读，但是有些重复可能会导致不易察觉的缺陷：若想添加新的促销策略，要定义相应的函数，还要记得把它添加到promos列表中；否则，当新促销函数显示地作为参数传给Order时，它是可用的，但是best_promo不会考虑它。


#### 6.1.4 找出模块中的全部策略

在Python中，模块也是一等对象。而且标准库提供了几个处理模块的函数。Python文档是这样说明内置函数globals的。

globals():返回一个字典，表示当前的全局符号表。这个符号表始终针对当前模块(对函数或方法来说，是指定义它们的模块，而不是调用它们的模块)。



**内省模块的全局命名空间，构建promos列表：**
```
promos=[globals()[name] for name in globals()
            (1) 迭代globals()返回字典中的各个name

            if name.endswith('_promo')
            (2) 只选择以_promo结尾的名称。

            and name != 'best_promo'
            (3) 过滤掉best_promo自身，防止无限递归。
        ]

def  best_promo(order):
    """ 选择可用的最佳折扣
    """
    return max(promo(order) for promo in promos)

```

收集所有可以促销的另一种方法是，在一个单独的模块中保存所有策略函数，把best_promo排除在外。



**内省单独的promotions模块，构建promos列表：**
```
promos=[func for name, func in
            inspect.getmembers(promotions,inspect.isfunction)]

def  best_promo(order):
    """ 选择可用的最佳折扣
    """
    return max(promo(order) for promo in promos)
```

inspect.getmembers函数用于获取对象(这里是promotions模块)的属性，第二个参数是可选的判断条件(一个布尔值函数)。我们使用的是inspect.isfunction，只获取模块中的函数。


不管怎么样命名策略函数，上例都可用。唯一重要的是，promotions模块只能包含计算订单折扣的函数。


动态收集促销折扣函数更为显示的一种方案是使用简单的装饰器。

----

### 6.2 "命令"模式




## 7 函数装饰器和闭包
函数装饰器用于在源码中"标记"函数，以某种方式增强函数的行为。这是一项强大的功能，但是若想掌握，必须理解闭包。

nonlocal是新近出现的保留关键字，在Python3.0中引入。如果你严格遵守基于类的面向对象编程方式，即便不知道这个关键字也不会受到影响。然而，如果你想自己实现函数装饰器，那就必须了解闭包的方方面面，因此也就需要知道nonlocal。


- Python如何计算装饰器句法
- Python如何判断变量是不是局部的
- 闭包存在的原因和工作原理
- nonlocal能解决什么问题

掌握了基础后，可以进一步探索装饰器：
- 实现行为良好的装饰器
- 标准库中有用的装饰器
- 实现一个参数化装饰器


----
### 7.1 装饰器基础知识
装饰器是可调用的对象，其参数是另一个函数(被装饰的函数)。装饰器可能会处理被装饰的函数，然后把它返回，或者将其替换成另一个函数或可调用对象。


**示例7-1 装饰器通常会把函数替换成另一个函数**
```
>>> def deco(func):
...     def inner():
...            print('running inner()')
...        return inner
    (1) deco返回inner函数对象

>>> @deco
... def target():
        print('running target()')


>>> target()
running inner()
(2) 调用被装饰的target其实会运行inner。

>>> target
<function deco.<local>.inner at 0X1003b598>
(3) 审查对象，发现target现在是inner的引用。

```
严格来说，装饰器只是语法糖。如前所示，装饰器可以像常规的可调用对象那样调用，其参数是另一个函数。有时，这样做更方便。尤其是做元编程(在运行时改变程序的行为)时。

综上，装饰器的一大特性是，能把被装饰的函数替换成其他函数。第二个特性是，装饰器在加载模块时立即执行。下一节会说明。

----
### 7.2 Python何时执行装饰器
装饰器的一个关键特性是，它们在被装饰的函数定义之后立即运行。这通常是在导入时(即Python加载模块时)，如下所示：

**示例7-2 registration.py模块：**
```
registry = []

def register(func):
    print('running register(%s)' % func)
    registry.append(func)
    return func

@register
def f1()；
    print('running f1()')


@register
def f2()；
    print('running f2()')

def f3()；
    print('running f3()')

def main():
    print('running main()')
    print('registry -> ',registry)
    f1()
    f2()
    f3()

if __name__='__main__':
    main()
```
把register.py当作脚本运行得到的输出如下：
```
runing register(<function f1 at 0x100...>)
runing register(<function f2 at 0x100...>)
runing main()
register ->[<function f1 at 0x...>,<fuction f2 at 0x...>]
running f1()
running f2()
running f3()

```
注意，register在模块中其他函数之前运行(两次)。调用register时，传给它的参数是被装饰的函数。例如<function f1 at 0x100...>。

加载模块后，registry中有两个被装饰函数的引用：f1和f2。这两个函数，以及f3，只在main明确调用它们时才执行。

示例7-2主要想强调，**函数装饰器在导入模块时立即执行。而被装饰的函数只在明确调用时运行。** 这突出了Python程序员所说的**导入时和运行时之间的区别**。

考虑到装饰器在真实代码中的常用方式，示例7-2有两个不寻常的地方：
- 装饰器函数与被装饰的函数在同一个模块中定义。实际情况是，装饰器通常在一个模块中定义，然后应用到其他模块中的函数上。
- register装饰器返回的函数与通过参数传入的相同。实际上，大多数装饰器会在内部定义一个函数，然后将其返回。

。。。。。。

----

### 7.3 使用装饰器改进"策略"模式



**示例7-3 promos列表中的值使用promotion装饰器填充：**
```
promos = []
(1) promos列表起初是空的。

def promotion(promo_func):
    promos.append(promo_func)
    return promo_func
(2) promotion把promo_func添加到promos列表中，然后原封不动地将其返回。

。。。。。。


```

不过，多数装饰器会修改被装饰的函数。通常，它们会定义一个内部函数，然后将其返回，替换被装饰的函数。使用内部函数的代码几乎都要靠闭包才能正确运作。为了理解闭包，我们要退后一步，先了解Python中的变量作用域。

----
### 7.4 变量作用域规则


**示例7-4 一个函数，读取一个局部变量和一个全局变量**
```
>>> def f1(a):
        print(a)
        print(b)

>>> f1(3)
3
Traceback (...)
    ...
    ...
NameError:global name 'b' is not defined

```
出现错误很正常，如果先给全局变量b赋值，然后再调用f，那就不会出错：
```
>>> b=6
>>> f1(3)
3
6
```


**示例7-5 b是局部变量，因为在函数的定义体中给他赋值了：**
```
>>> b=6
>>> def f2(a):
        print(a)
        print(b)
        b=9

>>> f2(3)
3
Traceback (...)
    ...
    ...
UnboundLocalError:local variable 'b' referenced before assignment


```

Python编译函数的定义体时，它判断b是局部变量。因为在函数中给它赋值了。生成的字节码证实了这种判断。Python会尝试从本地环境获取b。后面调用f2(3)时，f2的定义体会获取并打印局部变量a的值，但是尝试获取局部变量b的值时，发现b没有绑定值。

这不是缺陷，而是设计选择：Python不要求声明变量，但是**假定在函数定义体中赋值的变量是局部变量**。这比JavaScript的行为好多了，JavaScript也不要求声明变量，但是如果忘记把变量声明为局部变量(使用var)，可能会在不知情的情况下获取全局变量。


如果在函数中赋值时想让解释器把b当成全局变量，要使用global声明：
```
>>> b=6
>>> def f3(a):
        global b
        print(a)
        print(b)
        b=9

>>> f3(3)
3
6
>>> b
9

>>> f3(3)
3
9

>>> b=30
>>> b
30
>>>
```

**比较字节码**
。。。。。。

----
### 7.5 闭包
其实，闭包指延申了作用的函数，其中包含函数定义体中引用，但是不在定义体中定义的非全局变量。函数是不是匿名的没有关系，关键是它能访问定义体之外定义的非全局变量。

我的理解：如函数1内包含了函数2，变量a是函数1中的变量，a不是在函数2定义体中的局部变量，也不是全局变量，此时当函数2想使用函数2外中函数1的变量a，就是闭包。我们称a是闭包中的自由变量。

但是如果在函数2中的语句操作使变量a重新绑定意外成为函数2中的局部变量(如赋值语句，隐式创建局部变量a)，那么a就不是自由变量了。要想解决这个问题，可以使用nonlocal声明，它的作用是把变量标记为自由标量。



**示例7-8 计算移动平均值的类：**
```
class Averager():

    def __init__(self):
        delf.series = []

    def __call__(self,new_value):
        self.series.append(new_value)
        total=sum(self.series)
        return total /len(self.series)
```




**示例7-9 计算移动平均值的高阶函数：**
```
def make_averager():
    series=[]

    def averager(new_value):
        series.append(new_value)
        total=sum(new_value)
        return total/len(series)
    return  averager
```
调用make_averager时，返回一个averager函数对象。每次调用averager时，它会把参数添加到系列值中，然后计算当前平均值。

示例7-8中avg是Averager的实例，在示例7-9中是内部函数averager。


注意，series是make_averager函数的局部变量，因为那个函数的定义体中初始化了series：series=[]。可是，调用avg(10)时，make_averager函数已经返回了，而它的本地作用域也一去不复返了。

在averager函数中，series是自由变量。指未在本地作用域中绑定的变量。




图
综上，闭包是一种函数，它会保留定义函数时存在的自由变量的绑定，这样调用函数时，虽然定义作用域不可用了，但是仍能使用那些绑定。

注意，只有嵌套在其他函数中的函数才可能需要处理不在全局作用域中的外部变量。

----
### 7.6 nonlocal声明


```
def make_averager():
    count=0
    total=0

    def averager(new_value):
        count+=1
        total+=new_value
        return total / count

    return averager

```

```
>>> avg=make_averager()
>>> avg(10)
Traceback(...)
    ...
UnboundLocalError:local variable 'count' referenced before assignment    
```
问题是，当count是数字或任何不可变类型时，count+=1语句的作用其实与count = count+1一样。因此，我们在averager的定义体中为count赋值了，这会把count变成局部变量。total变量也受这个问题影响。

示例7-9没遇到这个问题，因为我们没有给series赋值，我们只是调用series.append，并把它传给sum和len。也就是说，我们利用了列表是可变的对象这一事实。

但是对数字、字符串、元组等不可变类型来说，只能读取，不能更新。如果尝试重新绑定，例如count=count+1，其实会隐式创建局部变量count。这样，count就不是自由变量了，因此不会保存在闭包中。

为了解决这个问题，Python3中引入了nonlocal声明，它的作用是把变量标记为自由变量，即使在函数中为变量赋予新值了，也会变成自由变量。如果为nonlocal声明的变量赋予新值，闭包中保存的绑定会更新。

**示例7-14 计算移动平均值，不保存所有历史**
```
def make_averager():
    count=0
    total=0

    def averager(new_value):
        nonlocal count,total
        count+=1
        total+=new_value
        return total / count

    return averager
```

----

### 7.7 实现一个简单的装饰器

示例7-15定义了一个装饰器，它会在每次调用被装饰的函数时计时，然后把经过的时间、传入的参数和调用的结果打印出来。

**示例7-15 一个简单的装饰器，输出函数的运行时间：**
```
import time

def clock(func):
    def clocked(* args):
    (1) 定义内部函数clocked，它接受任意个定位参数。

        t0=time.pref_counter()
        result=func(*args)
        (2) 这行代码可用，是因为clocked的闭包中包含自由变量func。

        elapsed=time.perf_counter()-t0
        name=func.__name__
        arg_str=','.join(repr(arg) for arg in args)
        print('[%0.8fs] %s(%s) -> %r' % (elapsed,name,arg_str,result))
        return reslut
    return clocked
    (3) 返回内部函数clocked，取代被装饰的函数。
```

**示例7-16 使用clock装饰器：**
```
# clockdeco_demo.py

impport time
from clockdeco import clock

@clock
def snooze(seconds):
    time.sleep(seconds)

@clock
def factorial(n):
    return 1 if n <2 else n*factorial(n-1)

if __name__=='__main__':
    print('*'*40, 'Calling snooze(.123')
    snooze(.123)

    print('*'*40,'Calling factorial(6)')
    print('6!=',factorial(6))
    
```


----

### 7.8 标准库中的装饰器



----
### 7.9 叠放装饰器

```
@d1
@d2
def f():
    print('f')
```
等同于：
```
def f():
    print('f')

f=d1(d2(f))
```


----

### 7.10 参数化装饰器
解析源码中的装饰器时，Python把被装饰的函数作为第一个参数传给装饰器函数。那怎么让装饰器接受其他参数呢？答案是创建一个装饰器工厂函数，把参数传给它，返回一个装饰器，然后再把它应用到装饰的函数上。


#### 7.10.1 一个参数化的注册装饰器


**示例7-23 为了接受参数，新的register装饰器必须作为函数调用：**
```

registry=set()
(1) registry现在是一个set对象，这样添加和删除函数的速度更快。

def register(active=True):
(2) register接受一个可选的关键字参数。

    def decorate(func):
    (3) decorate这个内部函数是真正的装饰器：注意它的参数是一个函数。
        print('running register(active=%s) ->decorate(%s)' %(active,func))
        if active:
        (4) 只有active参数的值(从闭包中获取)是True时才注册func。
            registry.add(func)
        else:
            registry.discard(func)
        (5) 如果active不为真，而且func在registry中，那么把它删除。
        return func
        (6) decorate是装饰器，必须返回一个函数。
    return decorate
    (7) register是装饰器工厂函数，因此返回decorate。


@register(active=False)
(8) register是工厂函数必须作为函数调用，并且传入所需的参数。
def f1():
    print('running f1()')

@register()
(9) 即使不传入参数，register也必须作为函数调用(@register())，即要返回真正的装饰器decorate。

def f2():
    print('running f2()')

def f3():
    print('running f3()')

```
这里的关键是，register()要返回decorate，然后把它应用到被装饰的函数上。

**示例7-23 中的代码在registration_param.py模块中。如果导入，得到的结果如下：**
```
>>> import registration_param
running register(active=False) ->decorate(<function f1 at 0x10063c1e0>)
running register(active=True) ->decorate(<function f2 at 0x10063c268>)

>>> registration_PARAM>REGISTRY
{<function f2 at 0x10063c268>}
```
注意，只有f2函数在registry中：f1不在其中，因为传给register装饰器工厂函数的参数是active=False，所以应用到f1上的decorate没有把它添加到registry中。

如果不使用@句法，那就要像常规函数那样使用register，若想把f添加到registry中，则装饰f函数的句法是register()(f):不想添加(或把它删除)的话，句法是register(active=False)(f)。


**示例7-24**

```
>>> from registration_param import *
running register(active=False) ->decorate(<function f1 at 0x10063c1e0>)
running register(active=True) ->decorate(<function f2 at 0x10063c268>)
>>> registry 
{<function f2 at 0x10063c268>}

>>> registry()(f3)
running register(active=True) ->decorate(<function f3 at 0x10063c158>)
<function f3 at 0x10063c158>

>>> registry
{<function f3 at 0x10063c158>,<function f2 at 0x10063c268>}

>>> registry(active=False)(f2)
running register(active=False) ->decorate(<function f2 at 0x10063c268>)
>>> registry
{<function f3 at 0x10063c158>}

```


#### 7.10.2 参数化clock装饰器



