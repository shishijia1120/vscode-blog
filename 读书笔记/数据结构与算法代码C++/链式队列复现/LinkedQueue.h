# include "Queue.h"
# include <iostream>
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
class LinkedQueue:public Queue<T>{

    public:
        LinkedQueue(){
            front=NULL;
            rear=NULL;
        }

        ~LinkedQueue(){makeEmpty();}

        void makeEmpty();

        bool EnQueue(const T& x);
        bool DeQueue(T& x);

        bool getFront(T& x)const;

        bool IsEmpty()const{return (front==NULL)?true:false;};

        int getSize()const;

        template <class T2>
        friend ostream& operator << (ostream& os,LinkedQueue<T2>& Q);

    private:
        LinkNode<T> * front,*rear;
        
};