#ifndef AVLTREE_H
#define AVLTREE_H

#include"basetree.h"

using namespace std;

class AVLtree:public BaseTree<int>
{
private:
    template<typename T>
    class Node
    {
    public:
        T item;
        int height;
        Node<T> * left;
        Node<T> * right;
        Node(const T & x,int h=0,Node<T> * l=nullptr,Node<T>* r=nullptr):
            item(x),height(h),left(l),right(r){}
        friend std::ostream & operator << (std::ostream & out,Node & node){
            out<<node.item;
            return out;
        }
    };
public:
    AVLtree();
    ~AVLtree(){}

    // Tree interface
public:
    void insert(const int & x){insert(root,x);}
    void remove(const int & x){remove(root,x);}
    void InorderTraversal();
     Node<int> * getroot()const{return root;}
     Node<int> * getend()const{return nullptr;}
private:
    void insert(Node<int> * & root,int x);
    void remove(Node<int> * & root,int x);
    void InorderTraversal(const Node<int> * root,vector<int> & v)const;
    void free(Node<int> * &root);
    void balancetree(Node<int> * & root);
    void rotationWithLeftChild(Node<int> * &root);
    void rotationWithRightChild(Node<int> * &root);
    int height(const Node<int> * root)const;
    int maxheight(const Node<int> * left,const Node<int> * right)const;
    int findmin(const Node<int> * root)const;
    Node<int> * root;
};

#endif // AVLTREE_H
