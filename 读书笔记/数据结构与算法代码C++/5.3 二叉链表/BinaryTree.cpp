# include <cstdlib>
# include "BinaryTree.h"
# include "stack.h"

template <class T>
void BinaryTree<T>::destroy(BinaryTreeNode<T> *subTree){
    if(subTree !=NULL){
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
};


template <class T>
void BinaryTree<T>::Traverse(BinaryTreeNode<T> * subTree,ostream & out){

    if(subTree != NULL){
        out<<subTree->data<<' ';

        Traverse(subTree->leftChild,out);
        Traverse(subTree->rightChild,out);
    }
};



template <class T>
istream & operator >> (istream & in,BinaryTree<T> & Tree){
    CreateBinTree(in,Tree.root);
};


template <class T>
ostream & operator <<(ostream & out, BinaryTree<T> & Tree){
    cout <<"二叉树的前序遍历\n";
    Tree.Traverse(Tree.root,out);
    out<<endl;
    return out;
};

void CreateBinTree(istream & in ,BinaryTreeNode<char> * & BT){

    Stack<BinaryTreeNode<char> * > s;
    BT=NULL;
    BinaryTreeNode<char> * p,*t;
    int k;
    char ch;
    in >> ch;
    while(ch!=RefValue){
        switch (ch)
        {
        case '(':
            s.Push(p);
            k=1;
            break;
        case ')':
            s.Pop(t);
            break;
        case ',':
            k=2;
            break;
        default:
            p=new BinaryTreeNode(ch);
            if(BT == NULL) BT=p;
            else if(k==1)
            {
                s.getTop(t);
                t->leftChild=p;
            }
            else{
                s.getTop(t);
                t->rightChild=p;
            }
        }
        in >> ch;
    }
};

int main(){

    BinaryTree<char> btree('#');
    
    istream in;
    ostream out;
    in >> btree;
    out << btree;

    return 0;

}