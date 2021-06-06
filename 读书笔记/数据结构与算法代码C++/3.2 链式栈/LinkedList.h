// # include "linearList.h"
# include <stdlib.h>
using namespace std;

template <class T>
struct LinkNode
{
   T data;                                       // 数据域
    LinkNode<T> * link;                           // 链指针域
    LinkNode(LinkNode<T> * ptr = NULL){link = ptr;}// 仅初始化指针成员的构造函数    
    LinkNode(const T& item,LinkNode<T> * ptr=NULL)
    {data = item;link = ptr;}                     // 初始化数据与指针成员的构造函数

    
};

template <class T>
class List{
public:
    List(){first=new LinkNode<T>;} //构造函数
    List(const T& x){first = new LinkNode<T>(x);} 

    List(List<T>& L);

    
    ~List(){makeEmpty();}
    void makeEmpty();       //将链表置为空表
    int Length()const;      //计算链表的长度
    LinkNode<T> * getHead()const {return first;}    //返回附加头结点地址
    void setHead(LinkNode<T> * p){first=p;}

    LinkNode<T> * Search(T x);
    LinkNode<T> * Locate(int i);

    // T * getData(int i);
    bool getData(int i,T& x)const;   

    void setData(int i,T& x);
    bool Insert(int i,T& x);
    bool Remove(int i,T& x);
    bool IsEmpty()const{return first->link==NULL?true:false;}
    bool IsFull()const{return false;}
    void Sort();
    void input(T endTag);
    void output();
    List<T>& operator=(List<T>& L);

protected:
    LinkNode<T> * first;

};



