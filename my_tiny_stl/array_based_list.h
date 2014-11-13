/*************************************************************************
  > File Name: array_based_list.h
  > Author:Haoson 
  > Created Time: Wed 24 Sep 2014 08:14:00 AM PDT
  > description:动态数组实现的list，相当于vector
 ************************************************************************/

#ifndef ARRAY_BASED_LIST_H_
#define ARRAY_BASED_LIST_H_
#include<iostream>
#include<cstdint>
#include<new>
#include "linear_list.h"
#define DEFAULT_SIZE 16
template <typename T>
class ArrayBasedList :public LinearList<T>{
    private:
        T* data_array;
        int32_t current_size;
        int32_t max_size;
        bool resize(int32_t max);
        void initFromOther(const ArrayBasedList<T>& abl);
    public:
       ArrayBasedList(int32_t sz= DEFAULT_SIZE);
       ArrayBasedList(const ArrayBasedList<T> &abl);
       ArrayBasedList<T>& operator=(const ArrayBasedList<T>&);
       ~ArrayBasedList();
       int32_t length()const{
        return current_size;
       }
       bool isEmpty()const{
        return current_size==0;
       }
       bool create();
       int32_t search(const T& data);
       bool insert(int32_t i,T data);
       bool insert(T data);
       bool remove(int32_t i,T&data);
       bool find(int32_t i,T& data)const;
       void makeEmpty(){
        current_size = 0;
       }
       void output()const;
       T& operator[](const size_t);
       const T& operator [](const size_t)const;
};

template <typename T>
ArrayBasedList<T>::ArrayBasedList(int32_t sz){
    if(sz>0){
        max_size = sz;
        current_size = 0;
    }
}
template <typename T>
bool ArrayBasedList<T>::create(){
    bool is_success =false;
    if(max_size){
        data_array  = new(std::nothrow) int32_t[max_size];
        if(data_array!=0){
            is_success = true;
        }
    }
    return is_success;
}
template <typename T>
ArrayBasedList<T>::~ArrayBasedList(){
    if(data_array!=0){
        delete []data_array;
    }
}
template <typename T>
void ArrayBasedList<T>::output()const{
    std::cout<<"[";
    for(int index=0;index<current_size;++index){
        if(index==current_size-1)
            std::cout<<*(data_array+index);
        else
            std::cout<<*(data_array+index)<<",";
    }
    std::cout<<"]"<<std::endl;
}
template <typename T>
int32_t ArrayBasedList<T>::search(const T& data){
    int32_t result = -1;
    for(int index=0;index<current_size;++index){
        if(data==*(data_array+index)){
            result=index;
            break;
        }
    }
    return result;
}
template <typename T>
bool ArrayBasedList<T>::resize(int32_t new_size){
    bool is_success = false;
    T* temp = new(std::nothrow) T[new_size];
    if(temp!=0){
        for(int index=0;index<current_size;++index){
            *(temp+index) =  *(data_array+index);
        }
        delete[]data_array;
        data_array = temp;
        max_size = new_size;
        is_success = true;  
    }
    return is_success;
}
template <typename T>
ArrayBasedList<T>::ArrayBasedList(const ArrayBasedList<T>& abl){
   initFromOther(abl); 
}

template <typename T>
ArrayBasedList<T>& ArrayBasedList<T>::operator=(const ArrayBasedList<T>& abl){
    if(&abl!=this){//防止自身赋值
        if(data_array!=0)
            delete[]data_array;
        initFromOther(abl);
    }
    return *this;
}
template <typename T>
void ArrayBasedList<T>::initFromOther(const ArrayBasedList<T>& abl){
    max_size = abl.max_size;
    current_size = abl.current_size;
    data_array = new(std::nothrow) T[max_size];
    if(data_array!=0){
        for(int index = 0;index < current_size;++index){
            *(data_array+index) = *(abl.data_array+index);
        }
    }
}
template <typename T>
bool ArrayBasedList<T>::find(int32_t i,T& data)const{
    bool is_success = false;
    if(i>-1&&i<current_size){
        data = *(data_array+i);
        is_success = true;
    }
    return is_success;
}
template <typename T>
bool ArrayBasedList<T>::remove(int32_t i,T& data){
    bool is_success = false;
    if(i>-1&&i<current_size){
        data = *(data_array+i);
        for(int32_t add =1;(i+add)<current_size;++add){
            *(data_array+i+add-1) = *(data_array+i+add);
        }
        current_size--;
        //保证动态调整的数组实际大小是数组最大容量的1/4之上
        if(current_size>DEFAULT_SIZE && current_size == (max_size/4)){
            resize(max_size/2);
        }
        is_success = true;
    }
    return is_success;
}
template <typename T>
bool ArrayBasedList<T>::insert(int32_t i,T data){
    bool is_success = false;
    if(i>-1&&i<=current_size){
        for(int32_t index = current_size;index>i;--index){
            *(data_array+index) = *(data_array+index-1);
        }
        *(data_array+i) = data;
        current_size++;
        //当数组实际容量和最大容量相等时，将最大容量加倍
        if(current_size==max_size){
            resize(max_size*2);
        }
        is_success = true;
    }
    return is_success;
}
template <typename T>
bool ArrayBasedList<T>::insert(T data){
    return insert(current_size,data);
}
template <typename T>
T& ArrayBasedList<T>::operator[](const size_t index){
    return data_array[index];
}
template <typename T>
const T& ArrayBasedList<T>::operator [](const size_t index)const{
    return data_array[index];
}
#endif
