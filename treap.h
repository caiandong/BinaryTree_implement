#ifndef TREAP_H
#define TREAP_H
#include<climits>
#include<cstdlib>
#include"common.h"

#define Infinite INT_MAX

class Treap
{
public:
    class Node
    {
    public:
        int priority;
        int item;
        Node * left;
        Node * right;
        Node(int p,int x,Node * l=nullptr,Node * r=nullptr):priority(p),item(x),left(l),right(r){}
        friend std::ostream & operator << (std::ostream & out,Node & node){
            out<<node.item;
            return out;
        }
    };
public:
    Treap();
    ~Treap(){ free(root);delete NIL;}
    void insert(int x){ insert(root,x);}
    void remove(int x){ remove(root,x);}
    Node * getroot()const{return root;}
    Node * getend()const{return NIL;}
    std::vector<int> & InorderTraversal(std::vector<int> & v);
    void show_tree(std::vector<int> &)const;
private:
    void InorderTraversal(const Node * root,std::vector<int> & v);
    void insert(Node * &root,int x);
    void remove(Node * &root,int x);
    void free(Node * &root);
    void rotationWithLeftChild(Node * &root);
    void rotationWithRightChild(Node * &root);
    Node * root;
    Node * NIL;
};

#endif // TREAP_H
