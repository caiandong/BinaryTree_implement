#ifndef RBTREE_H
#define RBTREE_H

#include <regex>
#include"basetree.h"
/*
 * 具体算法参考算法导论
 *
 */

class RBtree: public BaseTree<int> {
private:
	enum Color {
		Red, Black
	};

	template<typename T>
	class Node {
	public:
		T item;
		Node<T> *parent;
		Node<T> *left;
		Node<T> *right;
		Color color;
		Node(const T &_item, Node<T> *_parent = nullptr, Node<T> *_left =
				nullptr, Node<T> *_right = nullptr, Color _Color = Red) :
				item(_item), parent(_parent), left(_left), right(_right), color(
						_Color) {
		}
		friend std::ostream& operator <<(std::ostream &out, Node<T> &node) {
			out << node.item;
			out.flush();
			out << (node.color == Red ? 'r' : 'b');
			return out;
		}
	};
public:
	RBtree();

	// BaseTree interface
public:
	virtual void insert(const int &x) override;
	virtual void remove(const int &x) override;
	virtual void InorderTraversal() override;
	Node<int>* getroot() const {
		return root;
	}
	Node<int>* getend() const {
		return NIL;
	}
	template<class T>
	static void testRbTreeInsertAndRemove(T f);
private:
	void insert(Node<int> *&root, Node<int> *parent, int x);
	void remove(Node<int> *&root, Node<int> *parent, int x);
	void rotationWithLeftChild(Node<int> *&root);
	void rotationWithRightChild(Node<int> *&root);
	void insertionFixUpOfDoubleRed(Node<int> *root);
	void removeFixUpOfLostOfBlack(Node<int> *root);
	Node<int>*& getParentReference(Node<int> *child) {
		if (child->parent == NIL)
			return this->root;
		return child == child->parent->left ?
				child->parent->left : child->parent->right;
	}
	int findmin(const Node<int> *root) const;
private:
	Node<int> *root;
	Node<int> *NIL;
};

template<class T>
void RBtree::testRbTreeInsertAndRemove(T f) {
	using namespace std;
	cout << "插入删除测试" << "\n 例如:插入输入[insert 20];删除[remove 30]"
			"\n 忽略大小写，[rEmOve 30]"
			"\n 还可以简写成 [i 20]或者[r 30]"
			"\n 按q退出"
			"\n请输入:" << endl;
	string s;
	char cc;
	int x = 0;
	//((i\\S*)|(r\\S*)|(s\\S*))\\s+(\\d{1,2})
	regex rr("(\\S+)\\s(\\d{1,2}\\s*)?", regex::icase);
	regex insert("i|(insert)", regex::icase);
	regex remove("r|(remove)", regex::icase);
	regex show("s|(show)", regex::icase);
	smatch sm;
	RBtree rb;
	vector<int> a(0);
	while (getline(cin,s) && s != "q") {
		if (regex_match(s, sm, rr)) {
//			for(auto i=0;i<sm.size();i++)
//				if(sm[i].length()>0)
//					cout<<i<<": "<<sm[i].str()<<endl;
			s=sm[1].str();
			x=atoi(sm[2].str().c_str());
			if(regex_match(s,insert))
				rb.insert(x);
			else if(regex_match(s,remove))
				rb.remove(x);
			else if(regex_match(s,show))
				;
			else{
				cout<<"不匹配，重新输入:";
				continue ;
			}
			show_tree(rb.getroot(),rb.getend(),a,3);
			a.empty();
			a.clear();
			cout<<"请继续,按q退出:";
		}else
		{
			cout<<"不匹配，重新输入:";
		}
	}
	cout<<"退出"<<endl;
}

#endif // RBTREE_H
