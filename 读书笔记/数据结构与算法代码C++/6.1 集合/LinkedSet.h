# include <iostream>
using namespace std;

// 集合的结点类定义
template <class T>
struct SetNode
{
    T data;
    SetNode<T> * link;

    SetNode():link(NULL){};
    SetNode(const T& x,SetNode<T> * next =NULL):data(x),link(next){};
};


//集合的类定义
template <class T>
class LinkedSet{

    private:
        SetNode<T> * first,* last;

    public:
        LinkedSet(){first=last=new SetNode<T>;}
        LinkedSet(LinkedSet<T>& R);

        ~LinkedSet(){makeEmpty();delete first;};

        void makeEmpty();
        bool addMember(const T& x);
        bool delMember(const T& x);

        LinkedSet<T>& operator = (LinkedSet<T>& R);
        LinkedSet<T> operator + (LinkedSet<T>& R);
        LinkedSet<T> operator * (LinkedSet<T>& R);
        LinkedSet<T> operator - (LinkedSet<T>& R);

        bool Contains(const T x);
        bool operator == (LinkedSet<T>& R);
        bool Min(T& x);
        bool Max(T& x);
       // bool subSet(bitSet<T>& R);

};


