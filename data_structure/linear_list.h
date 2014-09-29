/***********************************************************************
  > File Name: linear_list.h
  > Author:Haoson 
  > Created Time: Wed 24 Sep 2014 07:33:23 AM PDT
 ************************************************************************/

#ifndef LINEAR_LIST_H_
#define LINEAR_LIST_H_
#include<cstdint>
template <typename T>
class LinearList{
    public:
        LinearList(){}
        virtual ~LinearList(){}
        virtual bool create()=0;//创建线性表，二段式构造
        virtual int32_t length()const=0;//线性表数据数目
        virtual bool isEmpty()const=0;//是否为空
        virtual int32_t search(const T& data)=0;//查找线性表中是否存在data，如果存在，返回查找到的第一个索引，否则返回-1
        virtual bool insert(int32_t i,T data)=0;//在索引i处插入数据
        virtual bool insert(T data)=0;//在线性表末尾插入数据
        virtual bool remove(int32_t i,T& data)=0;//删除索引i处的数据，并将删除的数据放入data中
        virtual bool find(int32_t i,T& data)const=0;//查找索引i处的数据，数据放入data中
        virtual void makeEmpty()=0;//将线性表置为空
        virtual void output()const=0;//输出线性表中的数据
};
#endif
