
在Python语言内部，迭代器用于支持：
- for循环
- 构建和扩展集合类型
- 列表推导、字典推导和集合推导
    ```Python
    s3 = Sentence('Pig and Pepper')
    list(iter(s3)) || list(s)
    ['Pig','and','Pepper']
    ```
- 元组拆包
- 调用函数时，使用*拆包实参

## 第1版：单词序列
```Python
class Sentence:
    
    def __int__(self,text):
        self.text = text
        self.words = RE_WORD.findall(text)

    def __getitem__(self,index):
        return self.words[index]

    def __len__(self):
        return len(self.words)
    
    def __repr__(self):
        return 'Sentence(%s)' % reprlib.repr(self.text)
```


```Python
s = Sentence('the time has come')
for word in s:
    print(word)
...
...
...
...
list(s)
['the','time','has','come']
```


### 序列可以迭代的原因：iter函数
解释器需要迭代对象x时，会自动调用iter(x)。
内置的iter函数有以下作用：
- 检查对象是否实现了\_\_iter__方法，如果实现了就调用它，获取一个迭代器。
- 如果没有实现\_\_iter\_\_方法，但是实现了\_\_getitem\_\_方法，Python会创建一个迭代器，尝试按顺序(从索引0开始)获取元素。
- 如果尝试失败，Python抛出TypeError异常。

任何Python序列都可迭代的原因是，它们都实现了\_\_getitem\_\_方法。其实，标准的序列也都实现了\_\_iter\_\_方法.



**可迭代的对象**
- 使用iter内置函数可以获取迭代器的对象。如果对象实现了能返回迭代器的\_\_iter\_\_方法，那么对象就是可迭代的。序列都可以迭代，实现了\_\_getitem\_\_方法，这种对象也可以迭代。
- Python从可迭代的对象中获取迭代器。

```Python
s = 'ABC'
for char in s:
    print(char)
```
若不使用for语句，不得不使用while循环模拟：
```Python
s = 'ABC'
it = iter(s)
while True:
    try:
        print(next(it))
    except StopIteration:
        del it
        break
```

**标准的迭代器接口有两个方法**：
- \_\_next\_\_
  返回下一个可用的元素。如果没有元素了，抛出StopIteration异常。
- \_\_iter\_\_
  返回self，以便在应该使用可迭代对象的地方使用迭代器，例如在for循环中。

**迭代器：**
    实现了无参数的\_\_next\_\_方法，返回序列中的下一个元素；如果没有元素了，那么抛出StopIteration异常。Python中的迭代器还实现了\_\_iter\_\_方法，因此迭代器也可以迭代。




## 第2版：典型的迭代器
```Python
class Sentence:
    
    def __int__(self,text):
        self.text = text
        self.words = RE_WORD.findall(text)
  
    def __repr__(self):
        return 'Sentence(%s)' % reprlib.repr(self.text)

    def __iter__(self):
        return SentenceIterator(self.words)
    
    class SentenceIterator:
        def __init__(self,words):
            self.words = words
            self.index = 0
        
        def __next__(self):
            try:
                word = self.words[self.index]
            except IndexError:
                raise StopIteration()
            self.index += 1
            return word
        
        def __iter__(self):
            return self
```


## 第3版：生成器函数
```Python
class Sentence:
    
    def __init__(self,text):
        self.text = text
        self.words = RE_WORD.findall(text)
    
    def __repr__(self):
        return 'Sentence(%s)' % reprlib.repr(self.text)
    
    def __iter__(self):
        for word in self.words:
            yield word
```

## 第4版：


## 第5版：生成器表达式

```Python
def gen_AB():
    print('start')
    yield 'A'
    print('continue')
    yield 'B'
    print('end.')
```

```Python
res1 = [x*3 for x in gen_AB()]
start
continue
end.
```

```Python 
res2 = (x*3 for x in gen_AB())
>>>print(res2)
<generator object <genexpr> at 0X10063C240>
for i in res2:
    print('--->',i)
...
...
start
--->AAA
continue
--->BBB
end.
```
res2是一个生成器对象，只有for循环迭代res2时，gen_AB函数的定义体才会真正执行。for循环每次迭代时会隐式调用next(res2)，前进到gen_AB函数中的下一个yield语句。注意，gen_AB函数的输出与for循环中print函数的输出夹杂在一起。

```Python
class Sentence:

    def __init__(self,text):
        self.text = text
    
    def __repr__(self):
      return 'Sentence(%s)' % reprlib.repr(self.text)
    
    def __iter__(self):
        return (match.group() for match i RE_WORD.finditer(self.text))
```
**生成器表达式是语法糖:完全可以替换成生成器函数，不过有时使用生成器表达式更便利。**

## 何时使用生成器表达式
- 生成器表达式是创建生成器的简洁句法，这样无需先定义函数再调用。
- 生成器函数灵活得多，可以使用多个语句实现复杂的逻辑，也可以作为协程使用。
- 如果生成器表达式要分成多行写，建议使用生成器函数，以便提高可读性。


## 标准库中的生成器函数

**用于映射的生成器函数**
- enumerate(iterable,start=0)
    ```Python
    a = list(enumerate('albatroz',1))
    print(a)

    def test(iterable1):
        # length = len(iterable1)
        i = 1 
        for item in iterable1:
            yield i,item
            i+=1

    b = list(test('albatroz'))
    print(b)
    ```