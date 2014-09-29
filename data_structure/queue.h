/*************************************************************************
  > File Name: queue.h
  > Author:Haoson 
  > Created Time: Sun 28 Sep 2014 10:02:51 AM PDT
  > Description:A container giving FIFO behavior 
 ************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_
#include <cstdint>
#include "deque.h"
template <typename T>
class Queue{
    public:
        bool isEmpty() const{ 
            return sc.isEmpty();
        }
        int32_t length()const{
            return sc.length();
        }
        T& front(){
            return sc.front();
        }
        T& front()const{
            return sc.front();
        }
        T& back(){
            return sc.back();
        }
        T& back()const{
            return sc.back();
        }
        void push(const T& x){
            sc.push_back(x);
        }
        void pop(){
            sc.pop_front();
        }
    protected:
        Deque<T> sc;
    template<typename Tp1>
    friend bool operator==(const Queue<Tp1>&, const Queue<Tp1>&);
    template<typename Tp1>
    friend bool operator!=(const Queue<Tp1>&, const Queue<Tp1>&);
};
template<typename Tp1>
bool operator==(const Queue<Tp1>& q1, const Queue<Tp1>& q2){
    return q1.sc == q2.sc;
}
template<typename Tp1>
bool operator!=(const Queue<Tp1>& q1, const Queue<Tp1>& q2){
    return q1.sc != q2.sc;
}
#endif
