# include "LinkedList.h"
# include <iostream>
# include <stdlib.h> 
using namespace std;   

template <class T>
List<T> ::List(List<T>& L){


    T value;
    LinkNode<T> * srcptr=L.getHead();
    LinkNode<T> * desptr=first=new LinkNode<T>;
    while(srcptr->link !=NULL){
        value=srcptr->link->data;
        desptr->link=new LinkNode<T>(value);
        desptr=desptr->link;
        srcptr=srcptr->link;
    }
    desptr->link=NULL;
};

template <class T>
void List<T>::makeEmpty(){
    LinkNode<T> * q;
    while(first->link !=NULL){
        q=first->link;
        first->link=q->link;
        delete q;
    }
};


template <class T>
int List<T>::Length()const{
    LinkNode<T> * p=first->link;
    int count=0;
    while(p!=NULL){
        p=p->link;
        count++;
    }
    return count;
}





template <class T>
LinkNode<T> * List<T>::Search(T x){

    LinkNode<T> * current=first->link;
    while (current!=NULL)
        if(current->data==x)break;
        else current=current->link;
    return current;    
};

template <class T>
LinkNode<T> * List<T>::Locate(int i){
    if(i<0)return NULL;
    LinkNode<T> * current =first;
    int k=0;
    while (current !=NULL && k<i)
    {
        /* code */
        current=current->link;
        k++;
    }
    return current;
    
};


// template <class T>
// T * List<T>::getData(int i){
//     if(i<=0)return NULL;
//     LinkNode<T> * current=Locate(i);
//     if(current==NULL)return NULL;
//     else return &current->data;
// };

template<class T>
bool List<T>::getData(int i, T& x)const{

    if(i<=0)return NULL;
    LinkNode<T> *current = Locate(i);
    if(current == NULL)return false;
    else{x = current->data;return true;}
};

template <class T>
void List<T>::setData(int i,T& x){


    if(i<=0)return;
    LinkNode<T> * current=Locate(i);
    if(current==NULL)return;
    else current->data=x;
};


template <class T>
bool List<T>::Insert(int i,T& x){

    LinkNode<T> * current=Locate(i);
    if(current==NULL)return false;
    LinkNode<T> * newNode=new LinkNode<T>(x);
    if(newNode==NULL){cerr << "allocation error!" << endl;exit(1);}
    newNode->link=current->link;
    current->link=newNode;
    return true;
};

template <class T>
bool List<T>::Remove(int i,T& x){
    LinkNode<T> * current=Locate(i-1);
    if(current==NULL || current->link==NULL)return false;
    LinkNode<T> * del=current->link;
    current->link=del->link;
    x=del->data;
    delete del;
    return true;
};


template <class T>
void List<T>::output(){
    LinkNode<T> * current=first->link;
    while(current!=NULL){
        cout << "shu_chu:" <<current->data << endl;
        current=current->link;
    }
};

template<class T>
void List<T>::input(T endTag){

    LinkNode<T> * newNode,*last;T val;
    makeEmpty();
    cin >> val;
    last = first;
    while(val != endTag){              
        newNode = new LinkNode<T>(val);
        if(newNode == NULL){cerr<<"allocation error!"<<endl;exit(1);}
        last->link = newNode;
        last = newNode;
        cin >> val;                   
    }
    last ->link = NULL;               
};


template <class T>
List<T>& List<T>::operator=(List<T>& L){

    T value;
    LinkNode<T> * srcptr=L.getHead();
    LinkNode<T> * desptr=first=new LinkNode<T>;
    while(srcptr->link !=NULL){
        value=srcptr->link->data;
        desptr=desptr->link;
        srcptr=srcptr->link;
    }
    desptr->link=NULL;
    return * this;
};


int main(){
    List<int> list(10);
   // list.output();
    int i = 0;
//    int m = 2;
    list.input(i);  
    list.output();
    int m = 2;
    list.Remove(3,m);
    cout<<"m:"<<m<<endl;
    list.output();
}