# include "LinkedBinaryTree.H"
# include "stack.h"

template <class T>
void BinaryTree<T>::destory(BinaryTreeNode<T> * subTree){
    if(subTree !=NULL){
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
};

template <class T>
BinaryTreeNode<T> * BinaryTree<T>::Parent(BinaryTreeNode<T> * subTree,BinaryTreeNode<T> * current){

    if(subTree == NULL)return NULL;
    if(subTree->leftChild == current || subTree->rightChild==current)return subTree;

    BinaryTreeNode<T> * p;
    if((p=Parent(subTree->leftChild,current)) != NULL)return p;

    else return Parent(subTree->rightChild,current);
};



template <class T>
void BinaryTree<T>::Traverse(BinaryTreeNode<T> * subTree,ostream& out){
    if(subTree !=NULL){
        out << subTree->data << '';
        Traverse(subTree->leftChild,out);
        Traverse(subTree->rightChild,out);
    }
};

template <class T>
istream& operator >> (istream& in ,BinaryTree<T>& Tree){
    CreateBinTree(in,Tree,root);
    return in;
};

template <class T>
ostream& operator  << (ostream& out,BinartTree<T>& Tree){

    out<< "二叉树的前序遍历\n";
    Tree.Traverse(Tree.root,out);
    out << endl;
    return out;
};

int main(){


    return 0;
}

void CreateBinTree(istream& in,BinaryTreeNode<char> * &BT){
    Stack<BinaryTreeNode<char> * > s;

    BT=NULL;

    BinaryTreeNode<char> * p,*t;
    int k;
    char ch;
    in >> ch;
    while(ch !=RefValue){
        switch(ch){

            
        }
    }
}