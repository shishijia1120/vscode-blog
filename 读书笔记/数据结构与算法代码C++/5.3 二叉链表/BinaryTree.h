# include <iostream>

using namespace std;

template <class T>
struct BinaryTreeNode
{
    T data;
    BinaryTreeNode<T> * leftChild,*rightChild;

    BinaryTreeNode():leftChild(NULL),rightChild(NULL){}
    BinaryTreeNode(T x, BinaryTreeNode<T> * l =NULL , BinaryTreeNode<T> * r=NULL):data(x),leftChild(l),rightChild(r){}
};


template <class T>
class BinaryTree{
    public:
        BinaryTree():root(NULL){}
        BinaryTree(T value):RefValue(value),root(NULL){}

        BinaryTree(BinaryTree<T> & s);
        ~BinaryTree(){destroy(root);}


    protected:
        BinaryTreeNode<T> * root;
        T RefValue;

        //从文件读入建树
        void CreateBinTree(istream & in,BinaryTreeNode<T> * & subTree);

        // 删除
        void destroy(BinaryTreeNode<T> * & subTree);

        // 前序遍历输出
        void Traverse(BinaryTreeNode<T> * subTree,ostream & out);

        //重载操作，输入
        friend istream & operator >> (istream & in,BinaryTree<T> & Tree);

        //重载操作，输出    
        friend ostream & operator <<(ostream & out ,BinaryTree<T> & Tree);


};