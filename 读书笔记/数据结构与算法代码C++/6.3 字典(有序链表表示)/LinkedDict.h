# include <assert.h>
template <class E,class K>

struct ChainNode{

    E data;
    ChainNode<E,K> * link;

    ChainNode():link(NULL){};
    ChainNode(E& el, ChainNode<E,K> * next =NULL):data(el),link(next){};
};

template <class E,class K>
class SortedChain{
    public:
        SortedChain(){
            first=new ChainNode<E,K>;
            assert(first !=NULL);
        }

        ~SortedChain();
        
        ChainNode<E,K> * Search(const K k1)const;
        void Insert(const K k1,E& e1);
        bool Remove(const K k1,E& e1);

        // ChainNode<E,K> * Begin(){return first->link;}
        // ChainNode<E,K> * Next(ChainNode,E,K> * current)const{
        //     if(current!=NULL)return current->link;
        //     else return NULL;
        // }

    private:
        ChainNode<E,K> * first;
};