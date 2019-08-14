#ifndef COMMON_H
#define COMMON_H
#include<iostream>
#include<queue>
#include<vector>
#include<functional>

/*
 * 需要是内联的，否则链接出问题:多个定义
 */
inline void printblank(int last,int current,int uint_width=2)
{
    int dx=uint_width/2;
    int i=(current-last)*(uint_width-dx);
    if(last!=0)
        i-=dx;
    while (i-- >0) {
        std::cout<<" ";
    }
    std::cout<<std::flush;
}
/*
 * 中序遍历，用来排序，省去再用nlogn时间排序
 * 需要O(n)
 *
 */

template<typename T>
class  InorderTraversal_class{
public:
    InorderTraversal_class(const T * End):
        end(End){}
    //U是函数符，可以使用方便的lambda
    template<typename TT ,typename U>
    void InorderTraversal(const TT * root,U f)
    {
        if(root!=end){
            InorderTraversal(root->left,f);
            //不允许改变root的值，所以参数需要声明为const
            f(root->item);
            InorderTraversal(root->right,f);
        }
    }

private:
    const T *  end;
};

/*
 * 二分查找
 * 花费O(logn)
 *
 */
template<typename T>
int BinarySearch(const std::vector<T> & v,const T & x)
{
    int l=0,r=v.size()-1,mid=r/2;
    while(l<=r){
        if(v[mid]>x)
            r=mid-1;    //边界
        else if(v[mid]<x)
            l=mid+1;    //边界
        else
            break;
        mid=l+(r-l)/2;  //防止溢出
    }
    return l<=r?mid:-1;

}

/*
 * 整体上花费大概不超过O(n^2)时间复杂度
 * 在终端按照树的形状打印
 *
 */
template <typename T,typename U>
void show_tree(const T * begin, const T * end, std::vector<U> &v,int show_width=2)
{
    const T * x=begin;
    int a=0,b=0;
    int lastpoint=0,current=0;
    std::queue<T *> q;
    InorderTraversal_class<T>(end).InorderTraversal(begin,[&](const U & item){v.push_back(item);});
    q.push(const_cast<T *>(begin));
    a++;
    std::cout.fill('0');
    while(!q.empty()){
        x=q.front();
        q.pop();
        a--;

        if(x->left!=end){
            q.push(x->left);
            b++;
        }
        if(x->right!=end){
            q.push(x->right);
            b++;
        }
        current=BinarySearch(v,x->item);
        printblank(lastpoint,current,show_width);
        lastpoint=current+1;
        std::cout.width(show_width-1);
//        std::cout<<x->item;
        std::cout<<(const_cast<T &>( *x));
        if(a==0){
            std::cout<<std::endl;
            a=b;
            b=0;
            current=lastpoint=0;
        }
    }
    std::cout.fill(' ');
    std::cout<<std::endl;
}

template <typename T,typename U>
void test(std::string s,int aaa,T && avl,std::function< U (int)> f)
{
    using std::cout;
    using std::endl;
    using std::vector;
    vector<U> vv(aaa);
    for(int i=0;i<aaa;i++){
        vv[i]=f(i);
        avl.insert(vv[i]);
    }
    cout<<"这是:"<<s<<endl;
    cout<<"这是测试的数据:"<<endl;
    for(auto x:vv)
        std::cout<<x<<" ";
    cout<<endl;

    vector<U> a(0);
    show_tree(avl.getroot(),avl.getend(),a,3);
}

#endif // COMMON_H
