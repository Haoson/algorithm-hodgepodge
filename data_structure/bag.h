/*************************************************************************
  > File Name: bag.h
  > Author:Haoson 
  > Created Time: Sat 27 Sep 2014 02:57:37 AM PDT
  > description:Bag是一种不支持从中删除元素的集合数据类型-它的目的就是帮助用例收集元素并迭代遍历所有收集到的元素
 ************************************************************************/
#ifndef BAG_H_
#define BAG_H_
#include <cstdint>
#include "linked_list.h"
template <typename T>
class Bag{
    public:
        typedef typename LinkedList<T>::iterator  iterator;
        Bag(){
            list.create();
        }
        void add(T x){
            list.insert(list.zeroth(),x);
        }
        bool isEmpty()const{
            return list.isEmpty();
        }
        int32_t size()const{
            return list.length();
        }
        iterator begin()const{
            return list.begin();
        }
        iterator end()const{
            return list.end();
        }
    private:
        LinkedList<T> list;
};
#endif
