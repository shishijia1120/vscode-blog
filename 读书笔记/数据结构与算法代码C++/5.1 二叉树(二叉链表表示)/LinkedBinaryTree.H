# include <iostream>
# include <stdlib.h>

using namespace std;

template <class T>
struct BinaryTreeNode
{
    T data;
    BinaryTreeNode<T> * leftChild, * rightChild;
    BinaryTreeNode():leftChild(NULL),rightChild(NULL){}
    BinaryTreeNode(T x, BinaryTreeNode<T> * l=NULL,BinaryTreeNode<T> * r=NULL):data(x),leftChild(l),rightChild(r){}
};

template <class T>
class BinaryTree{
    public:
        BinaryTree():root(NULL){}
        BinaryTree(T value):RefValue(value),root(NULL){}
        BinaryTree(BinaryTree<T>& s);
        ~BinaryTree(){destory(root);}

        bool IsEmpty(){return (root ==NULL)? true:false;}

        BinaryTreeNode<T> * Parent(BinaryTreeNode<T> * current){
            return (root == NULL || root ==current)?NULL:Parent(root,current);}
        
        BinaryTreeNode<T> * LeftChild(BinaryTreeNode<T> * current){
            return (current !=NULL)?current->leftChild:NULL; }

        BinaryTreeNode<T> * RightChild(BinaryTreeNode<T> * current){
            return (current !=NULL)?current->rightChild:NULL; }

        int Height(){return Height(root);}
        int Size(){return Size(root);}

        BinaryTreeNode<T> * getRoot()const {return root;}
        
        void preOrder( void (* visit) (BinaryTreeNode<T> * p)){
            preOrder(root,visit);}
        void inOrder( void (* visit) (BinaryTreeNode<T> * p)){
            inOrder(root,visit);}
        void postOrder( void (* visit) (BinaryTreeNode<T> * p)){
            postOrder(root,visit);}
        void levelOrder( void (* visit) (BinaryTreeNode<T> * p));

        int Insert(const T item);
        BinaryTreeNode<T> * Find(T item)const;

    protected:
        BinaryTreeNode<T> * root;
        T RefValue;

        void CreateBinTree(istream& in,BinaryTreeNode<T> *& subTree);
        bool Insert(BinaryTreeNode<T> *& subTree,const T& x);
        void destory(BinaryTreeNode<T> *& subTree);
        bool Find(BinaryTreeNode<T> * subTree,const T& x)const;
        BinaryTreeNode<T> * Copy(BinaryTreeNode<T> * originode);
        int Height(BinaryTreeNode<T> * subTree);
        int Size(BinaryTreeNode<T> * subTree);

        BinaryTreeNode<T> * Parent(BinaryTreeNode<T> * subTree, BinaryTreeNode<T> * current);
        BinaryTreeNode<T> * Find(BinaryTreeNode<T> * subTree,const T& x)const;

        void Traverse(BinaryTreeNode<T> * subTree, ostream& out);
        void preOrder(BinaryTreeNode<T> & subTree, void(* visit) (BinaryTreeNode<T> * p));
        void inOrder(BinaryTreeNode<T> & subTree, void(* visit) (BinaryTreeNode<T> * p));
        void postOrder(BinaryTreeNode<T> & Tree, void(* visit) (BinaryTreeNode<T> * p));
        friend istream& operator >> (istream& in, BinaryTreeNode<T>& Tree);
        friend ostream& operator << (ostream& out,BinaryTreeNode<T>& Tree);


};
