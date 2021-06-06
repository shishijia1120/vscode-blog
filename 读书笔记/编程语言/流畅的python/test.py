# import time

# def clock(func):
#     def clocked(* args):
#         t0=time.perf_counter()
#         result=func(*args)
#         elapsed=time.perf_counter()-t0
#         name=func.__name__
#         arg_str=','.join(repr(arg) for arg in args)
#         print('[%0.8fs] %s(%s) -> %r' % (elapsed,name,arg_str,result))
#         return result
#     return clocked

# @clock
# def snooze(seconds):
#     time.sleep(seconds)

# @clock
# def factorial(n):
#     return 1 if n <2 else n*factorial(n-1)

# if __name__=='__main__':
#     print('*'*40, 'Calling snooze(.123')
#     snooze(.123)

#     print('*'*40,'Calling factorial(6)')
#     print('6!=',factorial(6))


# registry=set()

# def register(active=True):


#     def decorate(func):
#         print('running register(active=%s) ->decorate(%s)' %(active,func))
#         if active:
#             registry.add(func)
#         else:
#             registry.discard(func)
#         return func
#     return decorate

# @register(active=False)
# def f1():
#     print('running f1()')

# @register()
# def f2():
#     print('running f2()')

# def f3():
#     print('running f3()')

# if __name__=='__main__':

#     print('*' * 40 ,'输出registry')
#     print(registry)

#     print('*' * 40 ,'f1')
#     f1()

#     print('*' * 40 ,'f2')
#     f2()

#     print('*' * 40 ,'f3')
#     register()(f3)

    

def decorate(func):
    print('装饰函数func')
    return func

@decorate
def f():
    print('我是f函数')



def make_func():
    print('高阶函数make_func')

    def funcer():
        print('funcer')
    return funcer

@decorate
def f3():
    print('f3函数')

def main():
    print('main函数')
    f()
    print('--------分割线')
    f2=make_func()
    f2()
    print('--------分割线')
    f3()

if __name__=='__main__':
    main()
