# include "SeqQueue.h"
using namespace std;

template <class T>
SeqQueue<T>::SeqQueue(int sz):front(0),rear(0),maxSize(sz){
    elements=new T[maxSize];
    assert(elements !=NULL);
};

template <class T>
bool SeqQueue<T>::EnQueue(const T&x){

    if(IsFull()==true)return false;
    elements[rear]=x;
    rear=(rear+1)% maxSize;
    return true;
};

template <class T>
bool SeqQueue<T>::DeQueue(T& x){
    if(IsEmpty()==true)return false;
    x=elements[front];
    front=(front+1)% maxSize;
    return true;
};

template <class T>
bool SeqQueue<T>::getFront(T& x)const{
    if(IsEmpty()==true) return false;
    x=elements[front];
    return true;
};

template <class T>
ostream& operator << (ostream& os,SeqQueue<T>& Q) {
    // 输出栈中元素的重载操作 <<
    os << "front =" << Q.front <<", rear="<<Q.rear<<endl;
    for (int i = Q.front; i!= Q.rear; i = (i+1) % maxSize)
    os << i << ":"<< Q.elements[i] << endl;
    return os;
};

int main(){
    int i;
    int j;
    SeqQueue<int> queue(10);
    queue.EnQueue(3);     // 队列插入元素
    queue.EnQueue(5);
    queue.EnQueue(10);
    queue.DeQueue(j);    // 弹出队头元素
    queue.getFront(i);   // 获取队头元素
    cout << "队头元素的值是："<< i <<endl;
    cout << j << endl;
    return 0;
}

