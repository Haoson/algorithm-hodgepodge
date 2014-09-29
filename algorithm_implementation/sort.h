/*************************************************************************
  > File Name: sort.h
  > Author:Haoson 
  > Created Time: Sun 28 Sep 2014 01:21:56 PM PDT
  > Description:一些排序算法的实现 
 ************************************************************************/

#ifndef ALGORITHM_H_
#define ALGORITHM_H_
#include <iostream>
#include "../data_structure/iterator_base.h"
#include "utility.h"
#include "../data_structure/function_object.h"
#define LITTLE_ARRAY_LENGTH 15
namespace hds{
    template <typename RandomAccessIterator,typename Comp>
    void selectionSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void selectionSort(RandomAccessIterator begin,RandomAccessIterator last);
    
    template <typename RandomAccessIterator,typename Comp>
    void insertionSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void insertionSort(RandomAccessIterator begin,RandomAccessIterator last);

    template <typename RandomAccessIterator,typename Comp>
    void shellSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void shellSort(RandomAccessIterator begin,RandomAccessIterator last);

    template <typename RandomAccessIterator,typename Comp>
    void mergeSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void mergeSort(RandomAccessIterator begin,RandomAccessIterator last);
    template <typename RandomAccessIterator,typename Comp>
    void mergeSortBU(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void mergeSortBU(RandomAccessIterator begin,RandomAccessIterator last);
    template <typename RandomAccessIterator,typename Comp,typename T>
    void mergeInPlace(RandomAccessIterator begin,RandomAccessIterator last,Comp comp,std::shared_ptr<T> auxiliary_array);
    template <typename RandomAccessIterator,typename Comp,typename T>
    void mergeSortTopDown(RandomAccessIterator begin,RandomAccessIterator last,Comp comp,std::shared_ptr<T> auxiliary_array);

    template <typename RandomAccessIterator,typename Comp>
    void quickSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void quickSort(RandomAccessIterator begin,RandomAccessIterator last);
    template <typename RandomAccessIterator,typename Comp>
    void quick3WaySort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAccessIterator>
    void quick3WaySort(RandomAccessIterator begin,RandomAccessIterator last);
    template <typename RandomAccessIterator,typename Comp>
    RandomAccessIterator partition(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);

    template <typename RandomAccessIterator>
    void heapSort(RandomAccessIterator begin,RandomAccessIterator last);
    template <typename RandomAccessIterator,typename Comp>
    void heapSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp);
    template <typename RandomAcessIterator,typename Comp>
    void sink(RandomAcessIterator begin,RandomAcessIterator last,RandomAcessIterator sink_it,Comp comp);


    //选择排序
    template <typename RandomAccessIterator,typename Comp>
    void selectionSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        typename hds::iterator_traits<RandomAccessIterator>::difference_type min = 0,inner_index = 0;
        while(begin!=last){
            min = 0;
            inner_index = 1;
            //将*(begin+i)与*(begin+i+1)~*(--last)之间的最小者交换
            for(auto temp = begin+1;temp!=last;++temp){
                if(comp(*temp,*(begin+min)))
                    min = inner_index;
                ++inner_index;
            }
            hds::swap(*begin,*(begin+min));
            ++begin;
        }
    }
    template <typename RandomAccessIterator>
    void selectionSort(RandomAccessIterator begin,RandomAccessIterator last){
        selectionSort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());
    }

    //插入排序
    template <typename RandomAccessIterator,typename Comp>
    void insertionSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        if(begin==last)
            return;
        auto begin_save = begin;
        typename hds::iterator_traits<RandomAccessIterator>::value_type data_temp;
        while((++begin)!=last){
            auto temp = begin;
            data_temp = *temp;  
            //将*(begin+i)插入到*(begin+i-1),*(begin+i-2),*(begin+i-3)...*(begin+i-i)中
            for(;temp!=begin_save&&comp(data_temp,*(temp-1));--temp){
                *temp = *(temp-1); 
            }
            *temp = data_temp;
        } 
    }
    template <typename RandomAccessIterator>
    void insertionSort(RandomAccessIterator begin,RandomAccessIterator last){
        insertionSort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());    
    }

    //希尔排序
    template <typename RandomAccessIterator,typename Comp>
    void shellSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type d_t;
        d_t size = last - begin;
        d_t h = 1;    //增幅h的初始值设置为1
        while(h < size/3)//递增序列是1,4,13,40...
            h = 3*h + 1;

        typename hds::iterator_traits<RandomAccessIterator>::value_type data_temp;
        while(h>=1){
            //将数组变成h有序
            for(auto i = h;i < size;++i){
                auto j= i;
                data_temp = *(begin+(j));
                //将*(begin+i)插入到*(begin+i-h),*(begin+i-2h),*(begin+i-3h)...中
                for(;j >=h && comp(data_temp,*(begin+(j-h)));j -= h){
                    *(begin+(j)) = *(begin+(j-h)); 
                } 
                *(begin+(j)) = data_temp;
            } 
            h /= 3;
        }
    }
    template <typename RandomAccessIterator>
    void shellSort(RandomAccessIterator begin,RandomAccessIterator last){
        shellSort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());
    }

    //归并排序
    
    //归并排序辅助函数:自顶向下归并
    template <typename RandomAccessIterator,typename Comp,typename T>
    void mergeSortTopDown(RandomAccessIterator begin,RandomAccessIterator last,Comp comp,std::shared_ptr<T> auxiliary_array){
        if(last-begin==1)//一个元素的时候结束递归调用
            return;
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type d_t;
        d_t size = last-begin;
        RandomAccessIterator mid = begin+size/2;
        mergeSortTopDown(begin,mid,comp,auxiliary_array);
        mergeSortTopDown(mid,last,comp,auxiliary_array);
        mergeInPlace(begin,last,comp,auxiliary_array);
    }
    //归并排序辅助函数:原地归并
    template <typename RandomAccessIterator,typename Comp,typename T>
    void mergeInPlace(RandomAccessIterator begin,RandomAccessIterator last,Comp comp,std::shared_ptr<T> auxiliary_array){
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type d_t;
        d_t size = last-begin;
        d_t mid_index = size/2;
        d_t mutable_mid = mid_index;
        d_t begin_index = 0;
        for(d_t i = 0;i!=size;++i){
            auxiliary_array.get()[i] = *(begin+i); 
        }
        for(d_t i=0;i!=size;++i){
            if(begin_index==mutable_mid)                             //左半边元素被取完情况
                *(begin+i) = auxiliary_array.get()[mid_index++];
            else if(mid_index==size)                                 //右半边元素被取完情况
                *(begin+i) = auxiliary_array.get()[begin_index++];
            else if(comp(auxiliary_array.get()[mid_index],auxiliary_array.get()[begin_index]))   //右半边当前元素小于左半边当前元素情况
                *(begin+i) = auxiliary_array.get()[mid_index++];
            else                                                     //右半边当前元素小于左半边当前元素情况
                *(begin+i) = auxiliary_array.get()[begin_index++];
        }
    }

    //归并排序对外接口
    template <typename RandomAccessIterator,typename Comp>
    void mergeSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        if(begin==last)
            return;
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type d_t;
        typedef typename hds::iterator_traits<RandomAccessIterator>::value_type v_t;
        const d_t size = last-begin;    
        std::shared_ptr<v_t> aux_ptr(new v_t[size],[](v_t * p){delete[]p;});  //辅助数组，也就是归并排序所需要的额外空间，提前分配好 
        mergeSortTopDown(begin,last,comp,aux_ptr);
    }
    //归并排序对外接口
    template <typename RandomAccessIterator>
    void mergeSort(RandomAccessIterator begin,RandomAccessIterator last){
        mergeSort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());
    }
    //归并排序对外接口:自底向上的归并
    template <typename RandomAccessIterator,typename Comp>
    void mergeSortBU(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type d_t;
        d_t size = last-begin; 
        std::shared_ptr<d_t> aux_ptr(new d_t[size],[](d_t* p){delete[]p;}); 
        //子数组两两归并
        for(d_t sz = 1;sz<size;sz *= 2){  //sz为子数组大小
            for(d_t low = 0;low < size-sz;low += 2*sz){
                mergeInPlace(begin+low,begin+hds::min(size,low+2*sz),comp,aux_ptr);
            }
        }
    } 
    //归并排序对外接口:自顶向上的归并
    template <typename RandomAccessIterator>
    void mergeSortBU(RandomAccessIterator begin,RandomAccessIterator last){
        mergeSortBU(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());
    }
    
    //快排
    
    //快排辅助函数：切分函数
    template <typename RandomAccessIterator,typename Comp>
    RandomAccessIterator partition(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        typedef typename hds::iterator_traits<RandomAccessIterator>::value_type v_t;
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type d_t;
        //三取样切分,并将取样元素放在末尾作为"哨兵"防止越界
        d_t size = last-begin;
        d_t pivot_pos = (*(begin)>*(begin+size/2))?0:(size/2);
        pivot_pos = (*(begin+pivot_pos)>*(begin+size-1))?(size-1):pivot_pos;
        hds::swap(*(begin+pivot_pos),*(begin+size-1)); 
        v_t pivot_data = *(begin+size-1);

        RandomAccessIterator increment_it = begin;
        RandomAccessIterator decrement_it = begin+size-2; 
        while(true){
            if(decrement_it<=increment_it)
                break;
            while(comp(*increment_it,pivot_data))++increment_it; //保证increment_it迭代器左边使得函数对象为真
            while(comp(pivot_data,*decrement_it))--decrement_it; //保证decrement_it迭代器右边使得函数对象为真
            hds::swap(*increment_it++,*decrement_it--); //一圈未走完的时候，调换不符合上述条件的数据
        }
        hds::swap(*(increment_it),*(begin+size-1));//一轮切分结束后，将取样元素放到最终正确的位置上
        return increment_it;
    }

    //快排对外接口
    template <typename RandomAccessIterator,typename Comp>
    void quickSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        typedef typename hds::iterator_traits<RandomAccessIterator>::difference_type  d_t;
        d_t size = last-begin;
        if(size< LITTLE_ARRAY_LENGTH){ //排序小数组时切换到插入排序
            insertionSort(begin,last,comp);
            return;
        }

        RandomAccessIterator pivot_it = partition(begin,last,comp);
        quickSort(begin,pivot_it,comp);
        quickSort(pivot_it+1,last,comp);
    }
    //快排对外接口
    template <typename RandomAccessIterator>
    void quickSort(RandomAccessIterator begin,RandomAccessIterator last){
        quickSort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>()); 
    }

    //三向切分的快速排序
    /**
     *comp:谓词函数或者函数对象选用Less或者Greater最佳，在这里少用LessEquals或者GreaterEquals
     *原因:三向切分的快排就是应对重复元素的基本快排改进版
     */
    template <typename RandomAccessIterator,typename Comp>
    void quick3WaySort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        if(last-begin <= 1)
            return;
        auto pivot_data = *begin;
        RandomAccessIterator gt = last-1;  //gt迭代器右边的元素使得comp(pivote_data,some_data)为真
        RandomAccessIterator lt = begin;  //lt迭代器左边的元素使得comp(some_data,pivote_data)为真
        RandomAccessIterator mid_it = begin+1; 
        while(mid_it<=gt){
            if(comp(*mid_it,pivot_data))
                hds::swap(*lt++,*mid_it++);
            else if(comp(pivot_data,*mid_it))
                hds::swap(*mid_it,*gt--);
            else
                mid_it++;
        }
        quick3WaySort(begin,lt,comp);
        quick3WaySort(gt+1,last,comp);
    }
    template <typename RandomAccessIterator>
    void quick3WaySort(RandomAccessIterator begin,RandomAccessIterator last){
        quick3WaySort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template <typename RandomAcessIterator,typename Comp>
    void sink(RandomAcessIterator begin,RandomAcessIterator last,RandomAcessIterator sink_it,Comp comp){
        auto k = sink_it-begin;
        auto actual_index = last - begin -1;
        auto child_index = 2*k+1;
    //下沉操作过程中，将子节点较大的元素提上去，父节点降下去,直到平衡(不需要下沉)为止
    while(child_index<=actual_index){
        if(child_index<actual_index&&comp(*(begin+child_index),*(begin+child_index+1))) //选取2k+1和2k+2这两个子节点中较大的那一位(假设是最大堆)
            ++child_index;
        if(!comp(*(begin+k),*(begin+child_index)))//当当前下沉元素不小于两个子节点中较大的那个的时候，停止下沉(假设最大堆)
            break;
        hds::swap(*(begin+k),*(begin+child_index));//如果要继续下沉，先将下沉节点的元素值和子节点中较大者交换（假设最大堆）
        k = child_index;
        child_index = 2*k+1;
    }
}
    template <typename RandomAccessIterator>
    void heapSort(RandomAccessIterator begin,RandomAccessIterator last){
        heapSort(begin,last,hds::Less<typename hds::iterator_traits<RandomAccessIterator>::value_type>());
    }
    template <typename RandomAccessIterator,typename Comp>
    void heapSort(RandomAccessIterator begin,RandomAccessIterator last,Comp comp){
        auto it_size = last-begin;
        //1)构造堆
        //通过下沉方式构建堆，从右往左扫，可以跳过大小为1的堆开始构建，所以k取值为中间，后面的都是大小为1的堆
        for(auto k = it_size/2;k>=0;--k){
            sink(begin,last,begin+k,comp);   
        }
        //2)排序
        while(it_size>1){
            hds::swap(*begin,*(begin+it_size-1));
            sink(begin,begin+(--it_size),begin,comp);
        }
    }
}
#endif
