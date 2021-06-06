# include <iostream>
# include "LinkedList.h"
# include "stack.h"

template <class T>
class LinkedStack:public Stack<T>{
    public:
        LinkedStack():top(NULL){};

        ~LinkedStack(){makeEmpty();}

        void Push(const T& x);
        bool Pop(T& x);
        bool getTop(T& x)const;
        bool IsEmpty()const {return (top ==NULL) ? true:false;}

        int getSize()const;
        void makeEmpty();
        
        //friend ostream& operator << (ostream& os,LinkedStack<T>& s);

    template <typename T2>
    friend ostream& operator << (ostream& os, LinkedStack<T2>& s);

    private:
        LinkNode<T> * top; 
};

