# include "LinkedStack.h"
# include<assert.h>

template <class T>
void LinkedStack<T>::makeEmpty(){

    LinkNode<T> * p;
    while (top!=NULL)
    {
        p=top;
        top=top->link;
        delete p;
    }
    
};

template <class T>
void LinkedStack<T>::Push(const T& x){
    top=new LinkNode<T>(x,top);
    assert(top!=NULL);
};

template <class T>
bool LinkedStack<T>::Pop(T& x){
    if(IsEmpty()==true)return false;
    LinkNode<T> * p=top;
    top=top->link;
    x=p->data;
    delete p;
    return true;
};

template <class T>
bool LinkedStack<T>::getTop(T& x)const{
    if(IsEmpty()==true) return false;
    x=top->data;
    return true;
};

template <class T>
int LinkedStack<T>::getSize()const{
    LinkNode<T> * p =top;
    int k=0;
    while(p!=NULL){
        p=p->link;
        k++;
    }
    return k;
};

template <class T>
ostream& operator << (ostream& os,LinkedStack<T>& s){
    os<<"yuansu geshu="<<s.getSize()<<endl;
    LinkNode<T> * p=s.top;
    int i=0;
    while(p!=NULL)
        os << ++i<<":"<<p->data<<endl;
    return os;
};

int main(){
    LinkedStack<int> linkedstack;
    int m;
    int j;
    int num;
    int num_1;
    linkedstack.Push(3);  
    linkedstack.Push(10); 
    linkedstack.Push(8);
    linkedstack.Push(4);
    linkedstack.Push(7);
    num_1 = linkedstack.getSize();   
    linkedstack.Pop(m);      
    linkedstack.getTop(j);   
    num = linkedstack.getSize();    
    cout << "����֮ǰջ�Ĵ�С�ǣ�"<<num_1<<endl;
    cout << "������Ԫ��ֵ�ǣ�"<< m <<endl;
    cout << "ջ��Ԫ�ص�ֵΪ:"<<j<<endl;
    cout << "ջ�Ĵ�С�ǣ�"<<num<<endl;
    return 0;
}