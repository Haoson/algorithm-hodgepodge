/*************************************************************************
  > File Name: utility.h
  > Author:Haoson 
  > Created Time: Sun 28 Sep 2014 01:43:37 PM PDT
  > Description:一些实用常用工具函数 
 ************************************************************************/

#ifndef UTILITY_H_
#define UTILITY_H_
namespace hds{
    template <typename T>
    void swap(T&a, T&b){
        T temp = a;
        a = b;
        b = temp;
    }
    template <typename T>
    T min(const T&a ,const T&b){
        return (a<b)?a:b;
    }
    template <typename T>
    T max(const T&a ,const T&b){
        return (a>b)?a:b;
    }
}
#endif
