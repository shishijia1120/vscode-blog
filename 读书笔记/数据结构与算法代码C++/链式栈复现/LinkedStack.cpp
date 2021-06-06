# include "LinkedStack.h"

template <class T>
void LinkedStack<T>::makeEmpty(){
    LinkNode<T> * p;
    while(top !=NULL){
        p=top;
        top=top->link;
        delete p;
    }
};

template <class T>
void LinkedStack<T>::Push(const T& x){
    top =new LinkNode<T>(x,top);
    assert(top!=NULL);

};


template <class T>
void LinkedStack<T>::Push1(const T& x ){
    LinkNode<T> * newNode =new LinkNode<T>(x);
    newNode->link=top;
    top=newNode;
    assert(top!=NULL);
};


template <class T>
bool LinkedStack<T>::Pop(T& x){
    LinkNode<T> * p=top;
    top=top->link;
    x=p->data;
    delete p;
    return true;

};


template <class T>
void LinkedStack<T>::output(){

    LinkNode<T> * p=top;
    cout<<"all elements of the stack:"<<endl;
    while(p!=NULL){

        cout << p->data << endl;
        p=p->link;

    }
};

template <class T>
int LinkedStack<T>::getSize(){

    LinkNode<T> * p=top;
    int size=0;
    while(p!=NULL){
        size++;
        p=p->link;
    }
    return size;
};

template <class T>
bool LinkedStack<T>::IsEmpty(){
    return(top == NULL)? true:false;
};

template <class T>
bool LinkedStack<T>::getTop(T& x){
    if(IsEmpty()==true)return false;
    x=top->data;
    return true;

};


template <class T>
ostream& operator <<(ostream& os,LinkedStack<T>& s){

    os<<s.getSize()<<endl;
    s.output();
    return os;
};



int main(){

    LinkedStack<int> linkedstack;
    linkedstack.Push(3);
    linkedstack.Push(2);
    linkedstack.Push(1);
    // int p;
    // linkedstack.Pop(p);
    // cout << p;
    // linkedstack.output();
    // cout<<"the size of stack is:"<<linkedstack.getSize()<<endl;

    // int t;
    // linkedstack.getTop(t);
    // cout<<"the top element of stack is:"<<t<<endl;
    cout << linkedstack;
    return 0;
}