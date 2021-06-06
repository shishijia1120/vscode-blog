# include "LinkedSet.h"

template <class T>
LinkedSet<T>::LinkedSet(LinkedSet<T>& R){

    SetNode<T> * srcptr =R.first->link;
    first=last=new SetNode<T>;
    while(srcptr !=NULL){
        last->link=new SetNode<T>(srcptr->data);
        last=last->link;
        srcptr=srcptr->link;
    }
    
};


template <class T>
void LinkedSet<T>::makeEmpty(){

    SetNode<T> * p;
    while (first !=NULL)
    {
        p=first->link;
        first=first->link;
        delete p;
    }

};





// template <class T>
// bool LinkedSet<T>::Contains(const T& x){

//     SetNode<T> * temp = first->link;

//     while (temp !=NULL && temp->data < x)
//     {
//         temp=temp->link;
//     }
//     if(temp != NULL && temp->data ==x)return true;
//     else return false;
    
// };


template <class T>
bool LinkedSet<T>::addMember(const T& x){
    SetNode<T> * p=first->link, * pre=first;

    while(p!=NULL && p->data <x){
        pre=p;p=p->link;
    }

    if(p!=NULL && p->data ==x){cout <<"this element has existed!!!"<<endl;return false;}
    SetNode<T> * s =new SetNode<T>(x);

    s->link=p;pre->link=s;
    if(p==NULL)last=s;
    return true;

};


template <class T>
bool LinkedSet<T>:: delMember(const T& x){
    SetNode<T> * p=first->link, * pre =first;

    while(p !=NULL && p->data <x){
        pre=p; p=p->link;
    }

    if(p !=NULL && p->data==x){
        pre->link=p->link;
        if(p==last)last=pre;
        delete p; return true;
    }
    else return false;
};

int main(){
    LinkedSet<int> linkedset;

    linkedset.addMember(1);
    linkedset.addMember(1);


    return 0;

}