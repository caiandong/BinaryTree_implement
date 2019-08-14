#include "avltree.h"

AVLtree::AVLtree()
{
    root=nullptr;
}

void AVLtree::insert(Node<int> *&root, int x)
{
    if(root==nullptr)
        root=new Node<int>(x);
    else if(x<root->item)
        insert(root->left,x);
    else if(x>root->item)
        insert(root->right,x);
    else
        ;
    balancetree(root);
}

void AVLtree::remove(Node<int> *&root, int x)
{
    if(root==nullptr)
        return;
    if(x<root->item)
        remove(root->left,x);
    else if(x>root->item)
        remove(root->right,x);
    else{
        if(root->left!=nullptr&&root->right!=nullptr){
            root->item=findmin(root->right);
            remove(root->right,root->item);
        }
        else if(root->left==nullptr){
            Node<int> * pold=root;
            root=root->right;
            delete pold;
        }
        else {
            Node<int> * pold=root;
            root=root->left;
            delete pold;
        }
    }
    if(root)
        balancetree(root);
}

void AVLtree::InorderTraversal(const Node<int> *root, vector<int> &v) const
{
    if(root!=nullptr){
        InorderTraversal(root->left,v);
        v.push_back(root->item);
        InorderTraversal(root->right,v);
    }
}

void AVLtree::InorderTraversal()
{
    cout<<"遍历开始"<<endl;
    InorderTraversal_class<Node<int>>(getend()).InorderTraversal(root,[](const int & item){cout<<item<<" ";});
    cout<<"\n遍历结束"<<endl;
}


void AVLtree::balancetree(Node<int> *&root)
{
    int hleft=root->left?root->left->height:-1;
    int hright=root->right?root->right->height:-1;
    if(hleft-hright>1){
        if(height(root->left->right)>height(root->left->left))
            rotationWithRightChild(root->left);
        rotationWithLeftChild(root);
    }
    else if(hright-hleft>1){
        if(height(root->right->left)>height(root->right->right))
             rotationWithLeftChild(root->right);
        rotationWithRightChild(root);
    }
    else
        ;
    root->height=maxheight(root->left,root->right)+1;

}

void AVLtree::rotationWithLeftChild(Node<int> *&root)
{
    Node<int> * leftchild=root->left;
    root->left=leftchild->right;
    leftchild->right=root;
    root->height=maxheight(root->left,root->right)+1;
    leftchild->height=maxheight(leftchild->left,leftchild->right)+1;
    root=leftchild;
}

void AVLtree::rotationWithRightChild(Node<int> *&root)
{
    Node<int> * rightchild=root->right;
    root->right=rightchild->left;
    rightchild->left=root;

    root->height=maxheight(root->left,root->right)+1;
    rightchild->height=maxheight(rightchild->left,rightchild->right)+1;
    root=rightchild;
}

int AVLtree::height(const Node<int> *root) const
{
    return root!=nullptr?root->height:-1;
}

int AVLtree::maxheight(const Node<int> *left, const Node<int> *right) const
{
    int hleft=left?left->height:-1;
    int hright=right?right->height:-1;
    return hleft>hright?hleft:hright;
}

int AVLtree::findmin(const Node<int> *root) const
{
    const Node<int> * i=root;
    while (i->left!=nullptr) {
        i=i->left;
    }
    return i->item;
}
