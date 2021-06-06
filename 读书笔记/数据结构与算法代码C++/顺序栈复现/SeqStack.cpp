# include "SeqStack.h"

template <class T>
SeqStack<T>::SeqStack(int sz){
    top=-1;
    maxSize=sz;
    data=new T[maxSize];
    assert(data!=NULL);
};


template <class T>
void SeqStack<T>::Push(const T& x){

    data[++top]=x;
};


template <class T>
bool SeqStack<T>::Pop(T& x){
    if(IsEmpty()==true)return false;
    x=data[top--];
    return true;
};


template <class T>
bool SeqStack<T>::getTop(T& x)const{

    if(IsEmpty()==true)return false;
    x=data[top];
    return true;

};

int main(){

    SeqStack<int> seqstack;
    seqstack.Push(1);
    seqstack.Push(2);
    seqstack.Push(3);
    int t;
    seqstack.getTop(t);
    cout<<"the top elements of stack is:"<<t<<endl;
    cout <<"the size of seqstack is:"<<seqstack.getSize()<<endl;
    return 0;
}



