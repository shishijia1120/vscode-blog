# include <stdlib.h>
template <class T>

struct LinkNode{

    T data;
    LinkNode<T> * link;
    LinkNode(const T& item,LinkNode<T> * ptr=NULL){
        data =item;link=ptr;
    }

    LinkNode(LinkNode<T> * ptr =NULL){link=ptr;}
};

template <class T>
class List{
    public:
        List(){first=new LinkNode<T>;}
        List(const T& x){first=new LinkNode<T>(x);}
        ~List(){makeEmpty();}

        void makeEmpty();


        void input(T endTag);
        void output();
    private:
        LinkNode<T> * first;

};