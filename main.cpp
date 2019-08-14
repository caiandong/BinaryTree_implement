#include <iostream>
//#include"bst_tree.h"
#include"treap.h"
#include"avltree.h"
#include"rbtree.h"

#include<cstdlib>
#include<ctime>

#include <regex>
#include "study.h"
#define ARRAY_SIZE 63
using namespace std;



int main(int argc,char ** argv)
{
//    int aaa=ARRAY_SIZE;
//    //int array[ARRAY_SIZE]={96,16,26 ,23 ,38 ,68 ,94 ,61 ,43 ,49};
//    if(argc>1)
//        aaa=atoi(argv[1]);
//    srand(static_cast<unsigned int>(time(nullptr)));
//    auto lamb=[](int i){return rand()%100;};
//    test<Treap,int>("Treap",aaa,Treap(),[](int i){return rand()%100;});
//    test<AVLtree,int>("AVLtree",aaa,AVLtree(),[](int i){return i;});
//    test<RBtree,int>("RBtree",aaa,RBtree(),lamb);

//    RBtree::testRbTreeRemove(5);

//	example_regex();
    string fuck("R 25");
    //i insert r remove s show
    regex rr("((i\\S*)|(r\\S*)|(s\\S*))\\s+\\d{1,2}",regex::icase);
    smatch sm;

    if(regex_match(fuck,sm,rr)){
    	cout<<sm.str()<<endl;
    }
//    show_tree();
    RBtree::testRbTreeInsertAndRemove(5);
    return 0;
}
