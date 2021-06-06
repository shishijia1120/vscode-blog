# include "SeqStack.h"


template <class T>
SeqStack<T>::SeqStack(int sz):top(-1),maxSize(sz){
    elements =new T[maxSize];
    assert(elements!=NULL);
};

const int stackIncreament = 20;    
template <class T>
void SeqStack<T>::overflowProcess(){
    cout<<"���������?..."<<endl;
    T * newArray =new T[maxSize+stackIncreament];
    if(newArray==NULL){cerr<<"allocation error!"<<endl;exit(1);}
    for(int i=0;i<=top;i++)newArray[i]=elements[i];
    maxSize=maxSize+stackIncreament;
    delete []elements;
    elements=newArray;
    cout<<"����������"<<endl;
};


template<class T>
void SeqStack<T>::Push(const T& x){
 
    if(IsFull()==true)
    overflowProcess();     
    elements[++top] = x;
};



template <class T>
bool SeqStack<T>::Pop(T& x){
    if(IsEmpty()==true)return false;
    x=elements[top--];
    return true;
};

template <class T>
bool SeqStack<T>::getTop(T& x)const{
    if(IsEmpty()==true)return false;
    x=elements[top];
    return true;
    
};



template<class T>
ostream& operator<<(ostream& os,SeqStack<T>& s){
   
    os << "top="<<s.top<<endl;   
    for(int i = 0;i <= s.top; i++)
        os << i << ":"<<s.elements[i] << endl;
    return os;
};

int main(){
    SeqStack<int> seqstack(3);  
    int m;
    int j;
    seqstack.Push(3);          // ѹջ
    seqstack.Push(10);
    seqstack.Push(8);
    seqstack.Push(4);
    seqstack.Push(7);   
    seqstack.Pop(m);
    seqstack.getTop(j);    
    cout << "������Ԫ��ֵ�ǣ�"<< m <<endl;
    cout << "ջ��Ԫ�ص�ֵΪ:"<<j<<endl;
    return 0;

}




