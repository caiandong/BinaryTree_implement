#include "rbtree.h"

RBtree::RBtree() {
	root = NIL = new Node<int>(-9999);
	NIL->color = Black;
	NIL->parent = NIL->left = NIL->right = NIL;
}

void RBtree::insert(const int &x) {
	insert(root, root->parent, x);
}

void RBtree::remove(const int &x) {
	remove(root, root->parent, x);
}

void RBtree::InorderTraversal() {

}

void RBtree::insert(Node<int> *&root, Node<int> *parent, int x) {
	if (root == NIL) {
		root = new Node<int>(x, parent, NIL, NIL);
		if (parent->color == Red)
			insertionFixUpOfDoubleRed(root);
	} else if (x < root->item)
		insert(root->left, root, x);
	else if (x > root->item)
		insert(root->right, root, x);
	else
		;	//重复
}

void RBtree::remove(Node<int> *&root, Node<int> *parent, int x) {
	if (root == NIL)
		return;
	else if (x < root->item)
		remove(root->left, root, x);
	else if (x > root->item)
		remove(root->right, root, x);
	else {
		if (root->left != NIL && root->right != NIL) {  //双节点
			int x_new = findmin(root->right);
			root->item = x_new;
			remove(root->right, root, x_new);
		} else {
			Node<int> *replaced = root;
			Node<int> *replacing = nullptr;
			Color origin_color = replaced->color;
			Node<int> *pold = replaced;
			replacing =
					replaced->left != NIL ? replaced->left : replaced->right;
			replacing->parent = parent;
			root = replacing;
			delete pold;
			if (origin_color == Black)
				removeFixUpOfLostOfBlack(root);
		}
	}
}

void RBtree::rotationWithLeftChild(Node<int> *&root) {
	Node<int> *left_child = root->left;

	root->left = left_child->right;
	left_child->right->parent = root;

	left_child->right = root;
	left_child->parent = root->parent;

	root->parent = left_child;
	root = left_child;
}

void RBtree::rotationWithRightChild(Node<int> *&root) {
	Node<int> *right_child = root->right;

	root->right = right_child->left;
	right_child->left->parent = root;

	right_child->left = root;
	right_child->parent = root->parent;

	root->parent = right_child;
	root = right_child;
}

void RBtree::insertionFixUpOfDoubleRed(Node<int> *root) {
	while (root->parent->color == Red) {
		if (root->parent == root->parent->parent->left) {
			if (root->parent->parent->right->color == Red) {  //case 1
				root->parent->color = Black;
				root->parent->parent->right->color = Black;
				root->parent->parent->color = Red;
				root = root->parent->parent;
			} else {
				Node<int> *&gp = getParentReference(root->parent->parent);
				if (root == root->parent->right) {   //case 2
					root = root->parent;
					rotationWithRightChild(getParentReference(root));
				}
				rotationWithLeftChild(gp);    //case 3
				gp->color = Black;
				gp->right->color = Red;
				break;
			}
		} else {
			if (root->parent->parent->left->color == Red) {
				root->parent->color = Black;
				root->parent->parent->left->color = Black;
				root->parent->parent->color = Red;
				root = root->parent->parent;
			} else {
				Node<int> *&gp = getParentReference(root->parent->parent);
				if (root == root->parent->left) {
					root = root->parent;
					rotationWithLeftChild(getParentReference(root));
				}
				rotationWithRightChild(gp);
				gp->color = Black;
				gp->left->color = Red;
				break;
			}
		}
	}
	this->root->color = Black;
}

void RBtree::removeFixUpOfLostOfBlack(Node<int> *root) {
	while (root->color == Black && root != this->root) {
		Node<int> *root_brother = nullptr;
		if (root == root->parent->left) {
			root_brother = root->parent->right;
			if (root_brother->color == Red) {	//case 1
				Node<int> *&gp = getParentReference(root->parent);
				rotationWithRightChild(gp);
				gp->color = Black;
				gp->left->color = Red;
				root_brother = root->parent->right;
			}
			if (root_brother->left->color == Black
					&& root_brother->right->color == Black) {	//case 2
				root->color = Red;
				root_brother->color = Red;
				root = root->parent;
			} else {
				Node<int> *&root_parent = root->parent;
				if (root_brother->left->color == Red) {	//case 3
					rotationWithLeftChild(getParentReference(root_brother));
					root_parent->right->color = Black;
					root_parent->right->right->color = Red;
				}
				rotationWithRightChild(root_parent);	//case 4
				root_parent->color = root_parent->left->color;
				root_parent->left->color = Black;
				root_parent->right->color = Black;
				root = this->root;
			}
		} else {
			root_brother = root->parent->left;
			if (root_brother->color == Red) {	//case 1
				Node<int> *&gp = getParentReference(root->parent);
				rotationWithLeftChild(gp);
				gp->color = Black;
				gp->right->color = Red;
				root_brother = root->parent->left;
			}
			if (root_brother->left->color == Black
					&& root_brother->right->color == Black) {	//case 2
				root->color = Red;
				root_brother->color = Red;
				root = root->parent;
			} else {
				Node<int> *&root_parent = root->parent;
				if (root_brother->right->color == Red) {	//case 3
					rotationWithRightChild(getParentReference(root_brother));
					root_parent->left->color = Black;
					root_parent->left->left->color = Red;
				}
				rotationWithLeftChild(root_parent);	//case 4
				root_parent->color = root_parent->right->color;
				root_parent->left->color = Black;
				root_parent->right->color = Black;
				root = this->root;
			}
		}
	}
	root->color = Black;
}

int RBtree::findmin(const Node<int> *root) const {
	const Node<int> *temp = root;
	while (temp->left != NIL) {
		temp = temp->left;
	}
	return temp->item;
}

