# include<iostream>
# include "stack.h"
# include <stdlib.h>
# include <assert.h>

using namespace std;

template <class T>

struct LinkNode{

    T data;
    LinkNode<T> * link;
    LinkNode(const T& item,LinkNode<T> * ptr=NULL){
        data =item;link=ptr;
    }

    LinkNode(LinkNode<T> * ptr =NULL){link=ptr;}
};

template <class T>
class LinkedStack{
    public:
        LinkedStack():top(NULL){}
        ~LinkedStack(){makeEmpty();}
        void Push(const T& x);
        void Push1(const T& x);
        bool Pop(T& x);
        void makeEmpty();

        void output();

        bool IsEmpty();        
        bool getTop(T& x);
        int getSize();

        template <typename T2>
        friend ostream& operator << (ostream& os,LinkedStack<T2>& s);

    private:
        LinkNode<T> * top;

};