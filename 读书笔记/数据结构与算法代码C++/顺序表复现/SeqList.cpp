# include "SeqList.h"

template <class T>
SeqList<T>::SeqList(int sz){

    maxSize=sz;
    data =new T[maxSize];
    last=-1;
    if(data ==NULL){cout<< "allocation error!"<<endl;}
};

template <class T>
void SeqList<T>::input(){
    T val;
    cout<<"input the size of shuzu:";
    cin >> last;
    for(int i=0;i<last;i++)
        {
            cin >> val;
            data[i]=val;
        }

};


template <class T>
void SeqList<T>::output(){
for(int i=0;i<last;i++)
    cout<<data[i];

};



int main(){

    SeqList<int> seq(5);
    seq.input();
    seq.output();

    return 0;
}

