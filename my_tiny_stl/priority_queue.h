/*************************************************************************
  > File Name: priority_queue.h
  > Author:Haoson 
  > Created Time: Mon 29 Sep 2014 05:42:25 AM PDT
  > Description:基于堆的优先队列的实现 
 ************************************************************************/

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_
#include <iostream>
#include <cstdint>
#include "function_object.h"
#include "../algorithm_implementation/utility.h"
template <typename T,typename Comp=hds::Less<T> >
class PriorityQueue{
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef int32_t size_type;

        explicit PriorityQueue(size_type init_c = default_capacity,const Comp c = Comp()):comp(c),capacity(init_c+1),size(0){
            heap_array_ptr = std::shared_ptr<T>(new T[capacity],[](T* p){delete[]p;}); 
        }
        template <typename RandomAcessIterator>
        PriorityQueue(RandomAcessIterator begin,RandomAcessIterator last,const Comp c=Comp()):comp(c){
            initContainerWithData(begin,last);
        }
        PriorityQueue(const PriorityQueue& pq){
            initFromOther(pq);
        }
        PriorityQueue& operator=(const PriorityQueue& pq){
            initFromOther(pq);
        }
        ~PriorityQueue(){}
        bool isEmpty()const{
            return 0==size; 
        }
        size_type length()const{
            return size;
        }
        void pop();
        void push(const value_type&);
        const_reference top()const;
        void output()const;
    protected:
        Comp comp;
        size_type capacity;
        size_type size;
        std::shared_ptr<T> heap_array_ptr;    
        static const size_type default_capacity = 16;//默认的堆大小16
    private:
        void initFromOther(const PriorityQueue&);
        template <typename RandomAcessIterator>
        void initContainerWithData(RandomAcessIterator begin,RandomAcessIterator last);
        //自动扩容函数
        void resize(size_type new_capacity);
        template <typename RandomAcessIterator>
        void makeHeap(RandomAcessIterator begin,RandomAcessIterator last);
        //构建堆的构成中，由上自下的堆有序化（下沉函数）
        template <typename RandomAcessIterator>
        void sink(RandomAcessIterator begin,RandomAcessIterator last,RandomAcessIterator sink_it);
        //添加新元素辅助函数，新元素添加至数组末尾，新元素可能打破平衡性，需要由下至上的堆有序化（上浮函数）
        template <typename RandomAcessIterator>
        void swim(RandomAcessIterator begin,RandomAcessIterator swim_it);
};

template <typename T,typename Comp>
void PriorityQueue<T,Comp>::initFromOther(const PriorityQueue& pq){
    comp = pq.comp;
    capacity = pq.capacity;
    size = pq.size;
    heap_array_ptr = std::shared_ptr<T>(new T[capacity],[](T* p){delete[]p;}); 
    for(decltype(size) i = 1; i!= (size+1);++i){
        heap_array_ptr.get()[i] = pq.heap_array_ptr.get()[i];
    }
}
template <typename T,typename Comp>
    template <typename RandomAcessIterator>
void PriorityQueue<T,Comp>::initContainerWithData(RandomAcessIterator begin,RandomAcessIterator last){
    RandomAcessIterator begin_temp = begin;
    size = last-begin;
    capacity = 2*size;
    heap_array_ptr = std::shared_ptr<T>(new T[capacity],[](T* p){delete[]p;}); 
    //堆元素从数组第一个位置开始放置
    for(size_type i=1;i !=(size+1);++i){
        heap_array_ptr.get()[i] = *begin_temp++;
    }
    //第0个元素不做任何用，主要是为了计算方便（当前节点索引为k时，子节点索引：2k和2k+1;父节点索引：k/2）
    makeHeap(heap_array_ptr.get(),heap_array_ptr.get()+size+1); 
}
template <typename T,typename Comp>
    template <typename RandomAcessIterator>
void PriorityQueue<T,Comp>::sink(RandomAcessIterator begin,RandomAcessIterator last,RandomAcessIterator sink_it){
    auto k = sink_it-begin;
    auto actual_size = last - begin - 1;//由于数组第一个元素空置未使用，所以实际长度应该再减去1
    auto child_index = 2*k;
    //下沉操作过程中，将子节点较大的元素提上去，父节点降下去,直到平衡(不需要下沉)为止
    while(child_index<=actual_size){
        if(child_index<actual_size&&comp(*(begin+child_index+1),*(begin+child_index))) //选取2k和2k+1这两个子节点中较大的那一位(假设是最大堆)
            ++child_index;
        if(!comp(*(begin+child_index),*(begin+k)))//当当前下沉元素不小于两个子节点中较大的那个的时候，停止下沉(假设最大堆)
            break;
        hds::swap(*(begin+k),*(begin+child_index));//如果要继续下沉，先将下沉节点的元素值和子节点中较大者交换（假设最大堆）
        k = child_index;
        child_index = 2*k;
    }
}
template <typename T,typename Comp>
    template <typename RandomAcessIterator>
void PriorityQueue<T,Comp>::makeHeap(RandomAcessIterator begin,RandomAcessIterator last){
    //通过下沉方式构建堆，从右往左扫，可以跳过大小为1的堆开始构建，所以k取值为中间，后面的都是大小为1的堆
    for(auto k = (last-begin)/2;k!=0;--k){
        sink(begin,last,begin+k);   
    }
}
template <typename T,typename Comp>
void PriorityQueue<T,Comp>::output()const{
    for(size_type i = 1;i!=(size+1);++i){
        std::cout<<heap_array_ptr.get()[i]<<" ";
    }  
    std::cout<<std::endl;
}
template <typename T,typename Comp>
typename PriorityQueue<T,Comp>::const_reference PriorityQueue<T,Comp>::top()const{
   return heap_array_ptr.get()[1];
}
template <typename T,typename Comp>
void PriorityQueue<T,Comp>::pop(){
    heap_array_ptr.get()[1] = heap_array_ptr.get()[size--];
    sink(heap_array_ptr.get(),heap_array_ptr.get()+size+1,heap_array_ptr.get()+1);
    if(size==(capacity/4)&&(capacity/2)>default_capacity)
        resize(capacity/2);
}
template <typename T,typename Comp>
    template <typename RandomAcessIterator>
void PriorityQueue<T,Comp>::swim(RandomAcessIterator begin,RandomAcessIterator swim_it){
    auto distance = swim_it-begin;
    while(distance>1&&comp(*(begin+distance),*(begin+distance/2))){
        hds::swap(*(begin+distance),*(begin+distance/2));
        distance /= 2;
    }
}
template <typename T,typename Comp>
void PriorityQueue<T,Comp>::push(const value_type& x){
    heap_array_ptr.get()[++size] = x;
    swim(heap_array_ptr.get(),heap_array_ptr.get()+size);
    if(size==(capacity-1))
        resize(2*capacity);
}
template <typename T,typename Comp>
void PriorityQueue<T,Comp>::resize(size_type new_capacity){
    std::shared_ptr<T> temp_pre = std::shared_ptr<T>(new T[new_capacity],[](T* p){delete[]p;}); 
    for(size_type i=1;i!=(size+1);++i){
        temp_pre.get()[i] = heap_array_ptr.get()[i];
    }
    heap_array_ptr = temp_pre;
}
#endif
