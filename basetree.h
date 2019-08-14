#ifndef TREE_H
#define TREE_H

#include"common.h"

template<typename T>
class BaseTree
{
public:
    BaseTree(){}
    virtual ~BaseTree(){}
    virtual void insert(const T & x)=0;
    virtual void remove(const T & x)=0;
    virtual void InorderTraversal()=0;

//    int * getroot()const{}
//    int * getend()const{}

};

#endif // TREE_H
