#include "treap.h"
//#include"common.h"

Treap::Treap()
{
    root=NIL=new Node(Infinite,1);
    NIL->left=NIL->right=NIL;

}

std::vector<int> &Treap::InorderTraversal(std::vector<int> &v)
{
    InorderTraversal(root,v);
    return v;

}

void Treap::InorderTraversal(const Treap::Node *root, std::vector<int> &v)
{
    if(root!=NIL){
        InorderTraversal(root->left,v);
        v.push_back(root->item);
        InorderTraversal(root->right,v);
    }

}

void Treap::insert(Treap::Node *&root, int x)
{
    if(root==NIL)
        root=new Node(rand()%500,x,NIL,NIL);
    else if(x<root->item){
        insert(root->left,x);
        if(root->priority>root->left->priority)
            rotationWithLeftChild(root);
    }
    else if(x>root->item){
        insert(root->right,x);
        if(root->priority>root->right->priority)
            rotationWithRightChild(root);
    }
    else
        ;
}

void Treap::remove(Treap::Node *&root, int x)
{

}

void Treap::free(Treap::Node *&root)
{
    if(root!=NIL){
        free(root->left);
        free(root->right);
        delete root;
        root=nullptr;
    }
}

void Treap::rotationWithLeftChild(Treap::Node *&root)
{
    Node * tem=root;
    root=tem->left;
    tem->left=root->right;
    root->right=tem;

//    Node * leftchild=root->left;
//    root->left=leftchild->right;
//    leftchild->right=root;
    //    root=leftchild;
}

void Treap::rotationWithRightChild(Treap::Node *&root)
{
    Node * rightchild=root->right;
    root->right=rightchild->left;
    rightchild->left=root;
    root=rightchild;
}
void Treap::show_tree(std::vector<int> & v) const
{
    Node * x=nullptr;
    int a=0,b=0;
    int lastpoint=0,current=0;
    std::queue<Node *> q;
    q.push(const_cast<Node *>(root));
    a++;
//    InorderTraversal(root,v);
    std::cout.fill('0');
    while(!q.empty()){
        x=q.front();
        q.pop();
        a--;

        if(x->left!=NIL){
            q.push(x->left);
            b++;
        }
        if(x->right!=NIL){
            q.push(x->right);
            b++;
        }
        current=BinarySearch(v,x->item);
        printblank(lastpoint,current);
        lastpoint=current+1;
        std::cout.width(2);
        std::cout<<x->item;

        if(a==0){
            std::cout<<std::endl;
            a=b;
            b=0;
            current=lastpoint=0;
        }
    }
    std::cout.fill(' ');
}
