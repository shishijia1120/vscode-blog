# include "LinkedDict.h"
# include<iostream>
using namespace std;

template <class E,class K>
ChainNode<E,K> * SortedChain<E,K>::Search(const K k1)const{
    ChainNode<E,K> * p =first->link;
    while (p!=NULL && p->data <k1)
    {
        p=p->link;
    }

    if(p!=NULL && p->data == k1)return p;
    if(p!=NULL && p->data ==k1) return p;
    else return NULL;
    
};

template <class E,class K>
void SortedChain<E,K>::Insert(const K k1 ,E& e1){
    ChainNode<E,K> * p=first->link, *pre=first,* newNode;
    while(p!=NULL && p->data <k1){
        pre=p;p=p->link;
    }

    if(p!=NULL && p->data==k1){
        p->data=e1;
        return;
    }

    newNode =new ChainNode<E,K>(e1);
    if(newNode==NULL){
        cerr<<"allocation error!"<<endl;exit(1);
    }
    newNode->link=p;
    pre->link=newNode;
};


template <class E,class K>
bool SortedChain<E,K>::Remove(const K k1,E& e1){

    ChainNode<E,K> * p =first->link,* pre=first;
    while (p!=NULL && p->data <k1)
    {
        pre=p;
        p=p->link;
    }
    if(p!=NULL && p->data==k1){
        pre->link=p->link;
        e1=p->data;
        delete p;
        return true;
    }
    else return false;
    
};


int main(){

    SortedChain<int,int> sortedchain;
    sortedchain.Insert(1,10);
    ChainNode<int,int> * p=sortedchain.Search(1);
    cout << p->data;
    return 0;
}