# include <assert.h>
# include <iostream>
# include "Queue.h"
using namespace std;
template <class T>
class SeqQueue:public Queue<T>{
    public:
        SeqQueue(int sz=10);
        ~SeqQueue(){delete [] elements;}

        bool EnQueue(const T& x);
        bool DeQueue(T& x);
        bool getFront(T& x)const;
        void makeEmpty(){front=rear=0;}
        bool IsEmpty()const {return (front ==rear)? true:false;}

        bool IsFull()const{return ((rear+1) % maxSize==front)?true:false;}

        int getSize()const{return (rear-front+maxSize)% maxSize;}

        //friend ostream& operator << (ostream& os,SeqQueue<)

        template <typename T2>
        friend ostream& operator << (ostream& os,SeqQueue<T2>& Q);


    protected:
        int rear,front;
        T * elements;
        int maxSize;
};


