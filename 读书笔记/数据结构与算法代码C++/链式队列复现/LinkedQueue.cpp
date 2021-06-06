# include "LinkedQueue.h"

template <class T>
void LinkedQueue<T>::makeEmpty(){

    LinkNode<T> * p;
    while (front !=NULL)
    {
        p=front;
        front=front->link;
        delete p;
    }
    

};



template <class T>
bool LinkedQueue<T>::EnQueue(const T& x){

    if(front==NULL){
        front=rear=new LinkNode<T>(x);
        if(front==NULL)return false;
    }

    else {
        rear->link=new LinkNode<T>(x);
        if(rear->link == NULL)return false;
        rear=rear->link;
    }
    return true;
};

template <class T>
bool LinkedQueue<T>::DeQueue(T& x){

    if(IsEmpty()==true)return false;
    LinkNode<T> * p=front;
    x=front->data;
    front=front->link;
    delete p;
    return true;
};

template <class T>
bool LinkedQueue<T>::getFront(T& x)const{
    if(front==NULL)return false;
    x=front->data;
    return true;
};

template <class T>
int LinkedQueue<T>::getSize()const{

    LinkNode<T> * p=front;
    int size=0;
    while(p!=NULL){
        
        p=p->link;
        size++;
    }
    return size;
};


template <class T>
ostream& operator << (ostream& os, LinkedQueue<T>& Q){

    os<<"the size of the LinkedQueue is:"<<Q.getSize()<<endl;
    LinkNode<T> * p=Q.front;

    while(p!=NULL){

        os<<p->data<<endl;
        p=p->link;
    }
    return os;
};





int main(){

    LinkedQueue<int> linkedqueue;
    linkedqueue.EnQueue(1);
    linkedqueue.EnQueue(2);
    linkedqueue.EnQueue(3);

    // int f;
    // linkedqueue.getFront(f);
    // cout<<"the size of LinkedQueue is:"<<linkedqueue.getSize()<<endl;
    // cout <<"the front of LinkedQueue is:"<<f<<endl;
    cout << linkedqueue;
    return 0;
}