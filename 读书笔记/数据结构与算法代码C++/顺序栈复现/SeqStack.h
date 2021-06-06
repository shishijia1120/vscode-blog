# include "stack.h"
# include <assert.h>
# include <iostream>
using namespace std;


template <class T>
class SeqStack: public Stack<T>{
    public:
        SeqStack(int sz=50);
        ~SeqStack(){delete []data;}

        void Push(const T& x);
        bool Pop(T& x);
        void makeEmpty(){top=-1;}
        int getSize()const{return top+1;}
        bool getTop (T& x)const;

        bool IsFull()const{return (top==maxSize-1)? true:false;};
        bool IsEmpty()const {return (top==-1)? true:false;};

    private:
        T * data;
        int maxSize;
        int top;
       // void overflowProcess();

};