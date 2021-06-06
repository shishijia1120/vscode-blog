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
    // ���ջ��Ԫ�ص����ز��� <<
    os << "front =" << Q.front <<", rear="<<Q.rear<<endl;
    for (int i = Q.front; i!= Q.rear; i = (i+1) % maxSize)
    os << i << ":"<< Q.elements[i] << endl;
    return os;
};

int main(){
    int i;
    int j;
    SeqQueue<int> queue(10);
    queue.EnQueue(3);     // ���в���Ԫ��
    queue.EnQueue(5);
    queue.EnQueue(10);
    queue.DeQueue(j);    // ������ͷԪ��
    queue.getFront(i);   // ��ȡ��ͷԪ��
    cout << "��ͷԪ�ص�ֵ�ǣ�"<< i <<endl;
    cout << j << endl;
    return 0;
}

