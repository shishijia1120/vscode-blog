# include "LinkedList.h"
# include <iostream>
# include <stdlib.h>
using namespace std;

template <class T>
void List<T>::makeEmpty(){

    LinkNode<T> * p;
    while (first->link !=NULL)
    {
        p=first->link;
        first->link=p->link;
        delete p;
    }

};

template <class T>
void List<T>::input(T endTag){

    LinkNode<T> * p,* newNode;
    p=first;
    T val;
    cin >>val;

    while(val !=endTag){

        newNode=new LinkNode<T>(val);
        if(newNode == NULL){cerr<<"allocation error!";}
        p->link=newNode;
        p=newNode;
        cin >> val;
    } 
    p->link=NULL;
};

template <class T>
void List<T>::output(){

    LinkNode<T> * p;
    p=first->link;

    cout<<"the elements of shuzu:"<<endl;
    while(p !=NULL){

        cout <<"shuzu:"<< p->data << endl;
        p=p->link; 
    }


};

int main(){

    // List<int> list();
    List<int> list(1);
    list.input(5);
    list.output();
    return 0;
}

// template T有问题