# include<assert.h>
# include <iostream>
# include "stack.h"

template <class T>
class SeqStack:public Stack<T> {
    public:
        SeqStack(int sz=10);
        ~SeqStack(){delete []elements;}
        
        void Push(const T& x);
        bool Pop(T& x);
        bool getTop(T& x)const;
        bool IsEmpty()const {return (top==-1)? true:false;}
        bool IsFull()const {return (top==maxSize-1)? true:false;}
        int getSize()const {return top+1;}
        void MakeEmpty(){top=-1;}
        
        template<typename T1>
        friend ostream& operator<<(ostream& os,SeqStack<T1>& s);
       
        //friend ostream& operator <<(ostream& os,SeqStack<T>& s);

    private:
        T * elements;
        int top;
        int maxSize;
        void overflowProcess();
};

