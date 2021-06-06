# include "seqList.h"

template <class T>
SeqList<T>::SeqList(int sz){
    
    if(sz > 0){
        maxSize = sz;last = -1;
        data = new T[maxSize];
        if(data == NULL)
            {cerr << "collation Error!"<< endl; exit(1);}
    }
}


template <class T>          
SeqList<T>::SeqList(SeqList<T>& L){
   
    maxSize = L.Size();
    last = L.Length() -1;T value;
    data = new T[maxSize];                        
    if (data == NULL)
        {cerr << "collation Error!"<< endl; exit(1);}
    for (int i = 1; i<= last + 1; i++)
        {L.getData(i, value); data[i-1] = value;}
}


template <class T>
void SeqList<T>::reSize(int newSize){
    
    if (newSize <= 0)                                
        {cerr << "collation Error!"<<endl; return;}
    if (newSize != maxSize){                         
        T * newarray = new T[newSize];               
        if (newarray == NULL)
            {cerr << "collation Error!"<< endl; exit(1);}
        int n = last + 1;
        T * srcptr = data;                           
        T * destptr = newarray;                      
        while(n--)*destptr++=*srcptr++;             
        delete []data;                               
        data = newarray;maxSize = newSize;          
    }
}



template <class T>
int SeqList<T>::Search(T& x)const{
   
    
    for (int i = 0; i<= last; i++)
        if (data[i] == x) return i+1;
    return 0;
}

template <class T>
int SeqList<T>::Locate(int i)const{
   
    if (i>= 1 && i <= last+1)return i;
    else return 0;
}


template <class T>
bool SeqList<T>::Insert(int i, T& x){
    
    if (last == maxSize - 1)return false;                
    if (i < 0 || i > last + 1)return false;            
    for (int j = last; j>=i; j--)
        data[j+1] = data[j];                            
    data[i] = x;                                       
    last ++;                                            
    return true;                                        
}

template <class T>
bool SeqList<T>::Remove(int i, T& x){


    if (last == -1)return false;                         
    if (i < 1 || i > last+1)return false;               
    x = data[i -1];                                      
    for (int j = i; j<= last; j++)
        data[j-1] = data[j];                            
    last--;                                              
    return true;                                       
}


template <class T>
void SeqList<T>::input(){
    
   
    while(1){
        cin >> last;
        if (last <= maxSize - 1)break;
        cout << "size has error,cannot over "<< maxSize-1<<":";
    }
    for (int i = 0; i<= last; i++)
    {cin>>data[i]; cout<<i+1<<endl;}
}

template <class T>
void SeqList<T>::output(){
 
    cout << "the last of shunxubiao is:"<< last << endl;
    for (int i = 0; i<= last; i++)
        cout << "#"<<i+1<<":"<<data[i] << endl;
}


template <class T>
SeqList<T>& SeqList<T>::operator=(SeqList<T>& L){
    if(this==&L){
        return *this;
    }
    if(this->data != NULL){
        delete this->data;
    }
    maxSize = L.Size();
    last = L.Length() -1;T value;
    data = new T[maxSize];                          
    if (data == NULL)
        {cerr << "collation Error!"<< endl; exit(1);}
    for (int i = 1; i<= last + 1; i++)
        {L.getData(i, value); data[i-1] = value;}
        return *this; 
}




int main(){
    // SeqList<int> seq(10);
    // seq.input();
    // seq.output();
    // int m = 0;
    // seq.Remove(2,m);
    // seq.output();
    SeqList<int> seq(10);
    seq.output();


}