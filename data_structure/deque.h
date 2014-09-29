/*************************************************************************
  > File Name: Deque.h
  > Author:Haoson 
  > Created Time: Sat 27 Sep 2014 07:46:29 AM PDT
  > Description:Deque-双端队列的实现
 ************************************************************************/

#ifndef Deque_H_
#define Deque_H_
#include <iostream>
#include <cstdint>
#include <exception>
#include "iterator_base.h"
#define DEFAULT_MAP_SIZE 32
template <typename T>
struct DequeIterator;
template <typename T>
class Deque;

template <typename T>
typename DequeIterator<T>::difference_type operator -(const DequeIterator<T>&it1,const DequeIterator<T>&it2);
template <typename T>
bool operator >(const DequeIterator<T>&it1,const DequeIterator<T>&it2);
template <typename T>
bool operator >=(const DequeIterator<T>&it1,const DequeIterator<T>&it2);
template <typename T>
bool operator <(const DequeIterator<T>&it1,const DequeIterator<T>&it2);
template <typename T>
bool operator <=(const DequeIterator<T>&it1,const DequeIterator<T>&it2);

template <typename T>
bool operator== (const Deque<T>& lhs, const Deque<T>& rhs);
template <typename T>
bool operator!= (const Deque<T>& lhs, const Deque<T>& rhs);

template <typename T>
class Deque{
    public:
        typedef DequeIterator<T> iterator;
        explicit Deque();
        Deque(const Deque<T>&);
        ~Deque();
        Deque<T>& operator=(const Deque<T>&);
        iterator begin();
        iterator end();
        int32_t length()const{
            return element_num; 
        }
        bool isEmpty()const{
            return element_num==0;
        }
        T& front();
        const T& front()const;
        T& back();
        const T& back()const;
        T& operator[](int32_t index);
        const T& operator[](int32_t index)const;
        void push_back(const T& x);
        void push_front(const T& x);
        void pop_back();
        void pop_front();
        iterator insert(iterator pos,const T& x);
        iterator erase(iterator pos);
        void clear();
        void output()const;
    private:
        struct dqPosition{
            int32_t block_index;
            int32_t element_index;
        };
        dqPosition indexAt(int32_t n)const;
        void expandMapSize();//将block map的容量加倍
        void cleanUp();
        void initFromOther(const Deque<T>&);
        int32_t element_num;//Deque中元素的数量
        T** block_map;//指向map array（堆上分配）的一个指针
        int32_t map_size;//map array的长度
        int32_t first_block;//map array中的第一个元素的索引位置
        int32_t first_element;//在第一个block中的第一个元素的索引位置
        static int32_t num_element_in_block;//每一个block中元素个数
        const static int32_t block_size = 4096;//每一个block大小为4096 byte
    friend bool operator== <T>(const Deque<T>& lhs, const Deque<T>& rhs);
    friend bool operator!= <T>(const Deque<T>& lhs, const Deque<T>& rhs);
};
template <typename T>
int32_t Deque<T>::num_element_in_block = Deque<T>::block_size/sizeof(T);

template <typename T>
Deque<T>::Deque(){
    try{
        element_num = 0;
        map_size = DEFAULT_MAP_SIZE;
        block_map = new T*[map_size];
        for(int32_t temp = 0;temp!=map_size;++temp){
            block_map[temp]  = new T[num_element_in_block];
        }
        first_block = map_size/2;//从中间往两头展开
        first_element = 0;
    }catch(const std::exception& e){
        std::cerr<<"deque constructor exception!"<<std::endl; 
        std::cerr<<e.what()<<std::endl;
        exit(1);
    }    
}
template <typename T>
void Deque<T>::cleanUp(){
    for(int32_t index = 0 ;index != map_size;++index)
        delete[](block_map[index]);
    delete []block_map;
    block_map = nullptr;
}
template <typename T>
void Deque<T>::initFromOther(const Deque<T>& d){
    element_num = d.element_num;
    map_size = d.map_size;
    try{
        block_map = new T*[map_size];
        for(int32_t temp = 0;temp!=map_size;++temp){
            block_map[temp]  = new T[num_element_in_block];
        }
    }catch(const std::exception& e){
        std::cerr<<"deque copy constructor exception!"<<std::endl; 
        std::cerr<<e.what()<<std::endl;
        exit(1);
    }
    first_block = d.first_block;
    first_element = d.first_element;
    dqPosition pos;
    for(int32_t temp = 0;temp!=element_num;++temp){
        pos = indexAt(temp);
        block_map[pos.block_index][pos.element_index] = d.block_map[pos.block_index][pos.element_index];
    }
}
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& d){
    if(&d != this){
        cleanUp();
        initFromOther(d);
    }
    return *this;
}
template <typename T>
Deque<T>::Deque(const Deque<T>& d){
    initFromOther(d);
}
template <typename T>
Deque<T>::~Deque(){
    cleanUp();
}

template <typename T>
struct DequeIterator : public hds::iterator_base<hds::random_access_iterator_tag,T>{
    public:
        typedef DequeIterator<T> iterator;
        DequeIterator(Deque<T>* ptr=nullptr,int32_t deque_index =0):deque_ptr(ptr),index(deque_index){}
        T& operator*(){ // dereferencing operator
            return (*deque_ptr)[index];    
        }
        const T& operator*() const { //提供const和非const版本。const成员返回const引用以防止用户改变基础对象
            return (*deque_ptr)[index];    
        }
        bool operator==(const iterator & rhs) const{
            return (deque_ptr==rhs.deque_ptr)&&(index==rhs.index);
        }
        bool operator!=(const iterator & rhs) const{
            return !(*this == rhs);
        }
        iterator& operator++(){
            ++index;
            return *this;
        }
        iterator operator++(int){
            iterator temp(*this);
            ++(*this);
            return temp;
        }
        iterator& operator--(){
            --index;
            return *this;
        }
        iterator operator--(int){
            iterator temp(*this);
            --(*this);
            return temp;
        }
        iterator& operator +=(typename DequeIterator<T>::difference_type index); 
        iterator& operator -=(typename DequeIterator<T>::difference_type  index); 
    friend DequeIterator<T> operator +(typename DequeIterator<T>::difference_type  n,DequeIterator<T> it){
        it.index += n;
        return it;
    }
    friend DequeIterator<T> operator + (DequeIterator<T> it1,typename DequeIterator<T>::difference_type  n){
        return n+it1;
    }
    friend DequeIterator<T> operator - (DequeIterator<T> it1,typename DequeIterator<T>::difference_type n){//写成内联形式表示只实例化申明的类型
        return (-n)+it1;
    }
    //先声明，再写成友元函数，<T>表示只实例化该申明的类型，然后再在外部实现，比较啰嗦
    friend typename DequeIterator<T>::difference_type operator - <T>(const iterator&it1,const iterator&it2);
    friend bool operator > <T>(const iterator&it1,const iterator&it2);
    friend bool operator >= <T>(const iterator&it1,const iterator&it2);
    friend bool operator < <T>(const iterator&it1,const iterator&it2);
    friend bool operator <= <T>(const iterator&it1,const iterator&it2);
    private:
        Deque<T> * deque_ptr;
        int32_t index;
    friend class Deque<T>;
};
template <typename T>
typename DequeIterator<T>::iterator& DequeIterator<T>::operator +=(typename DequeIterator<T>::difference_type  n){
    this->index += n; 
    return *this;
}
template <typename T>
typename DequeIterator<T>::iterator& DequeIterator<T>::operator -=(typename DequeIterator<T>::difference_type  n){
    return  (*this) += -n; 
} 
template <typename T>
typename DequeIterator<T>::difference_type operator -(const DequeIterator<T>&it1,const DequeIterator<T>&it2){
    return (it1.index - it2.index); 
}
template <typename T>
bool operator<(const DequeIterator<T>&it1,const DequeIterator<T>&it2){
    return (it1.index < it2.index); 
}
template <typename T>
bool operator>(const DequeIterator<T>&it1,const DequeIterator<T>&it2){
    return it2<it1;
}
template <typename T>
bool operator>=(const DequeIterator<T>&it1,const  DequeIterator<T>&it2){
    return !(it1<it2);
}
template <typename T>
bool operator<=(const DequeIterator<T>&it1,const DequeIterator<T>&it2){
    return !(it1>it2);
}


template <typename T>
T& Deque<T>::front(){
    return block_map[first_block][first_element];
}
template <typename T>
const T& Deque<T>::front()const{
    return block_map[first_block][first_element];
}
template <typename T>
typename Deque<T>::dqPosition Deque<T>::indexAt(int32_t index)const{
    dqPosition pos;
    if(index < 0){
        pos.block_index = -1;
        pos.element_index = -1;
        return pos;
    }
    pos.block_index = first_block;
    if(index < (num_element_in_block - first_element)){
        pos.element_index = index + first_element;
    }else{
        index -= num_element_in_block - first_element;
        ++pos.block_index;
        int k = index / num_element_in_block;
        pos.block_index += k;
        pos.element_index = index - k*num_element_in_block;

    }
    return pos;
}
template <typename T>
T& Deque<T>::operator[](int32_t index){
    dqPosition pos = indexAt(index);
    return block_map[pos.block_index][pos.element_index];
}
template <typename T>
const T& Deque<T>::operator[](int32_t index)const{
    dqPosition pos = indexAt(index);
    return block_map[pos.block_index][pos.element_index];
}
template <typename T>
T& Deque<T>::back(){
    dqPosition pos = indexAt(element_num-1);
    return block_map[pos.block_index][pos.element_index];
}
template <typename T>
const T& Deque<T>::back()const{
    dqPosition pos = indexAt(element_num-1);
    return block_map[pos.block_index][pos.element_index];
}
template <typename T>
void Deque<T>::expandMapSize(){
    T** new_map = new(std::nothrow) T*[2*map_size];
    if(new_map){
        std::fill_n(new_map,2*map_size,nullptr); 
        int32_t temp = element_num - (num_element_in_block-first_element);
        int32_t last_block;
        if(temp<=0){
            last_block = first_block+1;
        }else{
            last_block =first_block+(element_num-temp)/(num_element_in_block)+1;
            if(!((element_num-temp)%(num_element_in_block)))
                ++last_block;
        }
        temp = (2*map_size-last_block+first_block)/2;
        std::copy(block_map+first_block,block_map+last_block,new_map+temp);//将原来block_map中的指针复制到新的map中，开始的位置是中间
        std::copy(block_map,block_map+first_block,new_map);//将原来的first_block之前的指针复制到新的map中，开始位置是零索引处
        std::copy(block_map+last_block,block_map+map_size,new_map+first_block);//将原来的last_block以及之后的指针复制到新的map中，开始位置接上一个位置
        //以下是将新map空缺位置新创建一个block
        for(int32_t index = (map_size-last_block+first_block);index!=temp;++index){
            new_map[index] = new(std::nothrow) T[num_element_in_block]; 
        }
        for(int32_t index = (last_block-first_block+temp);index!=2*map_size;++index){
            new_map[index] = new(std::nothrow) T[num_element_in_block]; 
        }
        delete[] block_map;
        block_map = new_map;
        first_block =temp;
        map_size *= 2;
    }
}
template <typename T>
void Deque<T>::push_back(const T& x){
    dqPosition pos = indexAt(element_num);
    block_map[pos.block_index][pos.element_index] = x;
    ++element_num;
    if((pos.block_index == (map_size-1))&&(pos.element_index == (num_element_in_block-1)))
        expandMapSize();
}
template <typename T>
void Deque<T>::push_front(const T& x){
    if((--first_element)<0){
        first_element += num_element_in_block;
        --first_block;
    }
    dqPosition pos = indexAt(0);
    block_map[pos.block_index][pos.element_index] = x;
    ++element_num;
    if((0==pos.block_index)&&(0==pos.element_index))
        expandMapSize();

}
template <typename T>
void Deque<T>::pop_back(){
    if(0!=element_num)
        --element_num;    
}
template <typename T>
void Deque<T>::pop_front(){
    if(0!=element_num){
        --element_num; 
        if((++first_element)==num_element_in_block){
            first_element -= num_element_in_block;
            ++first_block;
        }
    }
}
template <typename T>
void Deque<T>::clear(){
    element_num = 0;    
    //复位
    first_block = map_size/2;
    first_element = 0;
}
template <typename T>
void Deque<T>::output()const{
    dqPosition pos;
    for(int32_t index = 0;index!=element_num;++index){
        pos = indexAt(index);
        std::cout<<(block_map[pos.block_index][pos.element_index])<<" ";
    }
    std::cout<<std::endl;
}
template <typename T>
typename Deque<T>::iterator Deque<T>::begin(){
    return iterator(this,0);
}
template <typename T>
typename Deque<T>::iterator Deque<T>::end(){
    return iterator(this,element_num);
}
template <typename T>
typename Deque<T>::iterator Deque<T>::insert(iterator pos,const T& x){
    int32_t n = pos.index;
    dqPosition dp_test;
    if(n>element_num/2){//往后移动数据
        ++element_num; 
        dqPosition dp_pos,dp_pos_pre;
        for(int32_t temp=(element_num-1);temp!=n;--temp){
            dp_pos = indexAt(temp);           
            dp_pos_pre = indexAt(temp-1);           
            block_map[dp_pos.block_index][dp_pos.element_index] =block_map[dp_pos_pre.block_index][dp_pos_pre.element_index];
        }
        dp_pos = indexAt(n);
        block_map[dp_pos.block_index][dp_pos.element_index] = x;
        dp_test = indexAt(element_num);
        if((dp_test.block_index == (map_size-1))&&(dp_test.element_index == (num_element_in_block-1)))
            expandMapSize();
    }else{//往前移动数据
        if((--first_element)<0){
            first_element += num_element_in_block;
            --first_block;
        }
        dqPosition dp_pos,dp_pos_pre;
        for(int32_t temp=0;temp!=n;++temp){
            dp_pos = indexAt(temp);           
            dp_pos_pre = indexAt(temp+1);           
            block_map[dp_pos.block_index][dp_pos.element_index] =block_map[dp_pos_pre.block_index][dp_pos_pre.element_index];
        }
        dp_pos = indexAt(n);
        block_map[dp_pos.block_index][dp_pos.element_index] = x;
        ++element_num;
        dp_test = indexAt(0);
        if((0==dp_test.block_index)&&(0==dp_test.element_index))
            expandMapSize();
    }
    return pos;
}
template <typename T>
typename Deque<T>::iterator Deque<T>::erase(iterator pos){
    if(pos>=end()||pos<begin())
        return pos;
    int32_t n = pos.index;
    if(n>element_num/2){//后面数据往前推
        dqPosition dp_pos,dp_pos_pre;
        for(int32_t temp=n;temp!=(element_num-1);++temp){
            dp_pos = indexAt(temp);           
            dp_pos_pre = indexAt(temp+1);           
            block_map[dp_pos.block_index][dp_pos.element_index] =block_map[dp_pos_pre.block_index][dp_pos_pre.element_index];
        }
    }else{//前面数据往后推
        dqPosition dp_pos,dp_pos_pre;
        for(int32_t temp=n;temp!=0;--temp){
            dp_pos = indexAt(temp);           
            dp_pos_pre = indexAt(temp-1);           
            block_map[dp_pos.block_index][dp_pos.element_index] =block_map[dp_pos_pre.block_index][dp_pos_pre.element_index];
        }
        if((++first_element)==num_element_in_block){
            first_element -= num_element_in_block;
            ++first_block;
        }
    }
    --element_num;
    return pos;
}
template <class T>
bool operator== (const Deque<T>& lhs, const Deque<T>& rhs){
    bool is_equal = true;
    if(lhs.element_num==rhs.element_num){
        for(int32_t n = 0;n != lhs.element_num;++n){
            if(lhs[n]!=rhs[n]){
                is_equal = false;
                break;
            }
        } 
    }else{
        is_equal = false;
    }
    return is_equal;
}
template <class T>
bool operator!= (const Deque<T>& lhs, const Deque<T>& rhs){
    return !(lhs == rhs);
}
#endif
