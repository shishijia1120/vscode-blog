
//顺序栈的抽象基类stack.h
#ifndef __STACK_H__
const int maxSize = 10;
using namespace std;

template<class T>
class Stack{                    // 栈的类定义
    public:
    Stack(){};                  // 构造函数
    virtual void Push(const T& x)=0;   // 新元素x进栈
    virtual bool Pop(T& x) = 0;        // 栈顶元素出栈，由x返回
    virtual bool getTop(T& x)const = 0;  // 读取栈顶元素，由x返回
    virtual bool IsEmpty()const = 0;     // 判断栈空否
//    virtual bool IsFull()const = 0;      // 判断栈满否
    virtual int getSize()const = 0;      // 计算栈中元素个数
};
#endif