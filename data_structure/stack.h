/*************************************************************************
  > File Name: stack.h
  > Author:Haoson 
  > Created Time: Sat 27 Sep 2014 05:36:32 AM PDT
  > description:stack类是为程序员提供了一个栈的功能 - 即，FILO（先入，最后出）的数据结构的容器适配器
 ************************************************************************/

#ifndef STACK_H_
#define STACK_H_
#include <cstdint>
#include "linked_list.h"
template <typename T>
class Stack{
    public:
        Stack(){
            list.create();
        }
        bool isEmpty()const{
            return list.isEmpty();
        }
        int32_t size()const{
            return list.length();
        }
        T top()const{
           return *(list.begin()); 
        }
        void pop(){
            T temp;
            list.erase(list.begin(),temp);
        }
        void push(const T& x){
            list.insert(list.zeroth(),x);
        }
    private:
       LinkedList<T> list;
};
#endif
