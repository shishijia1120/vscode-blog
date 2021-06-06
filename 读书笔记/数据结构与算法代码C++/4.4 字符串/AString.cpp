# include "AString.h"

AString::AString(int sz){
    maxSize =sz;
    ch =new char[maxSize+1];
    if(ch==NULL){cerr << "Allocation Error\n"; exit(1);}
    curLength=0;
    ch[0]='\0';
};



AString::AString(const char * init){
    int len =strlen(init);
    maxSize=(len>defaultSize)? len:defaultSize;
    ch=new char[maxSize+1];
    if(ch==NULL){cerr<<"Allocation Error\n";exit(1);}
    curLength=len;
    strcpy(ch,init);
};

AString::AString(const AString& ob){
    maxSize=ob.maxSize;
    ch=new char[maxSize+1];
    if(ch==NULL){cerr<<"Allocation Error\n";exit(1);}
    curLength=ob.curLength;
    strcpy(ch,ob.ch);
};

AString AString::operator()(int pos,int len){

    AString temp;
    if(pos <0 || pos+len-1 >=maxSize || len <0){
        temp.curLength=0;
        temp.ch[0]='\0';
    }
    else{
        if(pos+len-1>=curLength)len=curLength-pos;
        temp.curLength=len;
        for(int i=0,j=pos;i<len;i++,j++)temp.ch[i]=ch[j];
        temp.ch[len]='\0';
    }
    return temp;
};

AString& AString::operator=(const AString& ob){

    if(&ob!=this){
        delete []ch;
        ch=new char[maxSize+1];
        if(ch==NULL){cerr<<"allocation error!\n";exit(1);}
        curLength=ob.curLength;
        strcpy(ch,ob.ch);
    }
    else cout<<"string itself fuzhi chucuo!\n";
    return * this;
};

AString& AString::operator+=(const AString& ob){
    char * temp=ch;
    int n=curLength+ob.curLength;
    int m=(maxSize >= n)?maxSize:n;
    ch=new char[m];
    if(ch==NULL){cerr << "allocation error! \n";exit(1);}
    maxSize=m;
    curLength=n;
    strcpy(ch,ob.ch);
    delete []temp;
    return this;
};


char AString::operator[](int i){
    if(i<=||i>=curLength){
        cout<<"zifuchuan xiabiao chaojie!\n";
        exit(1);
    }
};


void AString:: input(){

    cout<<"now start build string,please input size:";
    int size;
    while(1){
        cin >> size;
        if(size <= maxSize)break;
        cout<<"size has error,cannot over" << maxSize <<";";
    }
    curLength=size-1;

    for(int i=0;i<=curLength;i++){
        cin>>ch[i];
    }
};

void AString:: output(){
    cout<<"output string :"<<endl;
    for(int i=0;i<=curLength;i++){
        cout<<ch[i];
    }
    cout<<endl;
};



int main(){

    AString as(10);
    as.input();
    as.output();
}