/*************************************************************************
  > File Name: doubly_linked_list.h
  > Author:Haoson 
  > Created Time: Fri 26 Sep 2014 03:19:25 AM PDT
  > description:双端循环链表实现，相当于C++ STL中的list的实现
 ************************************************************************/
/*
 * 带头结点的双向循环链表
 */
#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_
#include <iostream>
#define DEFAULT_CAPACITY 16
#include <cstdint>
#include "function_object.h"
template <typename T>
class DList;
template <typename T>
class DListIterator;
template <typename T>
class DListNode{
    public:
        explicit DListNode(T node_data,DListNode<T>*next_node=0,DListNode<T>*pre_node=0):data(node_data),next(next_node),pre(pre_node){}
        DListNode(DListNode<T>*next_node=0,DListNode<T>*pre_node=0):next(next_node),pre(pre_node){}
        bool operator==(const DListNode<T> & ln){
            return data == ln.data;
        }
        bool operator!=(const DListNode<T>&ln){
            return !(*this==ln);
        }
    private:
        DListNode<T>* next;
        DListNode<T>*pre;
        T data;
    friend class DList<T>;
    friend class DListIterator<T>;
};
template <typename T>
class DList{
    public:
        typedef DListIterator<T> iterator;
        DList(int32_t cap = DEFAULT_CAPACITY):head(0),tail(0),size(0),max_size(cap+1){}
        ~DList();
        DList(const DList&);
        DList& operator=(const DList&);
        int32_t capacity()const{
            return max_size;
        }
        int32_t length()const{
            return size;
        }
        bool isEmpty()const{
            return  size==0;
        }
        bool create();
        iterator begin() const;//返回第一个元素的迭代器
        iterator end() const;//返回最后一个元素的后一个元素的迭代器
        iterator insert(iterator pos, const T &x); //插入到迭代器pos位置处，返回插入的元素的迭代器
        iterator remove(iterator pos,T &x); //删除迭代器pos处的元素,并将删除的元素写入到x中
        iterator remove(const T &x);//删除第一个元素X,返回删除元素后面一个元素的迭代器
        iterator find(T& node_data);
        void clear();
        void resize(int32_t new_size); 
        void resize(int32_t new_size,const T& x);//当new_size>size,新加入的元素使用x填充
        void sort();
        template <class Comp>
            void sort(Comp comp);
        void merge(DList<T>& l);//合并两个已排序链表
        template <class Comp>
            void merge(DList<T>& l,Comp comp);
        void output()const;
    private:
        //返回旧链表中的it迭代器在新的节点链表中的迭代器位置
        iterator changeCapacity(int32_t new_max_size,iterator it);
        void moveNode(DListNode<T>* source_node,DListNode<T>* target_node);
        void deleteAllNodes();
        void initFromOther(const DList<T>&);
        template <class Comp>
            void quickSort(iterator first_it,iterator last_it,Comp comp);
        template <class Comp>
            iterator partition(iterator first_it,iterator last_it,Comp comp);
        void swapData(iterator first_it,iterator second_it);
        DListNode<T>* head;
        DListNode<T>* tail;
        int32_t size;//实际容量
        int32_t max_size;//最大容量
};
template <typename T>
class DListIterator{
    public:
        typedef DListIterator<T> iterator;
        DListIterator(DListNode<T>*node=0){
            current = node;
        }
        T& operator*(){ // dereferencing operator
            return current->data;    
        }
        const T& operator*() const { //提供const和非const版本。const成员返回const引用以防止用户改变基础对象
            return current->data;    
        }
        bool operator==(const iterator & rhs) const{
            return (current == rhs.current);
        }
        bool operator!=(const iterator & rhs) const{
            return !(*this == rhs);
        }
        iterator& operator++(){
            current = current->next;
            return *this;
        }
        iterator operator++(int){
            iterator temp(*this);
            ++(*this);
            return temp;
        }
        iterator& operator--(){
            current = current->pre;
            return *this;
        }
        iterator operator--(int){
            iterator temp(*this);
            --(*this);
            return temp;
        }
    private:
        DListNode<T>* current;
    friend class DList<T>;
};

template <typename T>
bool DList<T>::create(){
    bool is_success = false;
    if(max_size>0){
        head = new(std::nothrow) DListNode<T>[max_size];
        if(head){
            for(decltype(max_size) index = 0; index < max_size; ++index){
                (head+index)->next = (head+(index+1)%max_size);
                (head+index)->pre = (head+((index+max_size-1)%max_size));
            }
            tail = head+size+1;
            is_success = true;
        }
    }
    return is_success;
}
template <typename T>
void DList<T>::deleteAllNodes(){
    if(head)
        delete[]head;
}
template <typename T>
void DList<T>::initFromOther(const DList<T>& dl){
    this->size = dl.size;
    this->max_size = dl.max_size;
    if(create()){
        iterator dl_index = dl.begin();
        for(decltype(max_size) index=1;index<=size;++index){
            (head+index)->data = *(dl_index++);
        }
    }
}
template <typename T>
DList<T>::DList(const DList&dl){
    initFromOther(dl);
}
template <typename T>
DList<T>& DList<T>::operator=(const DList<T>& dl){
    if(&dl != this){
        deleteAllNodes();
        initFromOther(dl);
    }
    return *this;
}
template <typename T>
DList<T>::~DList(){
    deleteAllNodes();
}
template <typename T>
typename DList<T>::iterator DList<T>::begin()const{
    if(size>0)
        return iterator(head->next);
    else
        return end();
}
template <typename T>
typename DList<T>::iterator DList<T>::end()const{
    return iterator(tail);
}
template  <typename T>
void DList<T>::clear(){
   size = 0;
   tail = head->next;
}
template <typename T>
void DList<T>::output()const{
    for(iterator start = begin();start!=end();++start){
        std::cout<<*(start);
        std::cout<<" ";
    }
    std::cout<<std::endl;
}
template <typename T>
typename DList<T>::iterator DList<T>::find(T& node_data){
    iterator start = begin();
    for(;start!=end();++start){
        if(*(start)==node_data)
            break;
    }
    return start;
}
template <typename T>
typename DList<T>::iterator DList<T>::changeCapacity(int32_t new_max_size,iterator it){
    iterator result_it;
    DListNode<T>* head_temp = head;
    this->max_size = new_max_size;
    if(create()){
        iterator node_temp = iterator(head_temp->next);
        int32_t index = 1;
        for(;index !=(size+1);++index){
            if(node_temp == it)
                result_it = (head+index);
            (head+index)->data = *(node_temp++);
        }
        tail = head+index;
        if(!(result_it.current))
            result_it = end();
        if(head_temp)
            delete[]head_temp;
    }
    return result_it;
}
template <typename T>
void DList<T>::moveNode(DListNode<T>* source_node,DListNode<T>* target_node){
    //从原位置上remove出来
    DListNode<T>* temp_node = source_node->pre;
    temp_node->next = source_node->next;
    source_node->next->pre = temp_node;
    //插入新位置
    temp_node = target_node->pre;
    temp_node->next = source_node;
    source_node->pre = temp_node;
    source_node->next = target_node;
    target_node->pre = source_node;
}
template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator pos, const T &x){
    //减去2表示去除头结点以及一个空节点，空节点主要为了让tail指向，防止tail指向head
    if(size==(max_size-2))
        pos = changeCapacity(max_size*2,pos); 
    DListNode<T>*temp_tail = tail->next;
    tail->data = x;
    iterator it(tail);
    if(pos.current!=tail)
        moveNode(tail,pos.current);
    tail = temp_tail;
    ++size;
    return it;
}
template <typename T>
typename DList<T>::iterator  DList<T>::remove(iterator pos,T &x){
    iterator result_it = iterator(pos.current->next);
    x = *pos;
    moveNode(pos.current,end().current->next);
    --size;
    if((size<(max_size/4))&&(max_size/2>=DEFAULT_CAPACITY))
        result_it = changeCapacity(max_size/2,result_it);
    return result_it;
}
template <typename T>
typename DList<T>::iterator  DList<T>::remove(const T &x){
    iterator result_it = end();
    for(iterator start = begin();start!=end();++start){
        if(*(start)==x){
            result_it  = iterator(start.current->next);
            moveNode(start.current,end().current->next);
            --size;
            if((size<(max_size/4))&&(max_size/2>DEFAULT_CAPACITY))
                result_it = changeCapacity(max_size/2,result_it);
            break;
        }
    }
    return result_it;
}
template <typename T>
void DList<T>::resize(int32_t new_size){
    size = new_size;
    if(new_size>max_size)
        changeCapacity(new_size*2,iterator());
    else{
        DListNode<T>* temp = head->next;
        for(int32_t index=0;index < size;++index)
            temp = temp->next;
        tail = temp;
    }
} 
template <typename T>
void DList<T>::resize(int32_t new_size,const T& x){
    int32_t temp_size = size;
    size = new_size;
    if(new_size>max_size)
        changeCapacity(new_size*2,iterator());
    else{
        DListNode<T>* temp = head;
        for(int32_t index=0;index < size;++index){
            temp = temp->next;
            if(index>=temp_size)
                temp->data = x;
        }
        tail = temp->next;
    }
}
template <typename T>
void DList<T>::sort(){
    sort(hds::Less<T>());
}
template <typename T>
void DList<T>::swapData(iterator first_it,iterator second_it){
    T temp = *(first_it);
    *(first_it) = *(second_it);
    *(second_it) = temp;
}
template <typename T>
    template <class Comp>
void DList<T>::sort(Comp comp){
    if(size==0||size==1)
        return;
    quickSort(begin(),iterator(end().current->pre),comp);   
}
template <typename T>
    template <class Comp>
void DList<T>::quickSort(iterator first_it,iterator last_it,Comp comp){
    if(first_it!=last_it){
        iterator pivot_it = partition(first_it,last_it,comp);    
        if(pivot_it!=first_it)
            quickSort(first_it,iterator(pivot_it.current->pre),comp);
        if(pivot_it!=last_it)
            quickSort((pivot_it.current->next),last_it,comp);
    }
}
template <typename T>
    template <class Comp>
typename DList<T>::iterator DList<T>::partition(iterator first_it,iterator last_it,Comp comp){
    T pivot_data = *(last_it);
    iterator i = iterator(first_it.current->pre);
    for(iterator j=first_it;j!=last_it;++j){
        if(comp(*(j),pivot_data)){
            ++i;
            swapData(i,j);
        } 
    }
    swapData(++i,last_it);
    return i;
}
template <typename T>
void DList<T>::merge(DList<T>& l){
    merge(l,hds::LessEqual<T>());
}
template <typename T>
    template <class Comp>
void DList<T>::merge(DList<T>& dl,Comp comp){
    if(&dl==this)
        return;
    if((size+dl.size)>=max_size)
        changeCapacity(2*(size+dl.size),iterator());
    iterator this_it = begin();
    iterator dl_it = dl.begin();
    while(this_it!=end()&&(dl_it!=dl.end())){ 
        if(comp(*(dl_it),*(this_it))){
            insert(this_it,*(dl_it));    
            ++dl_it;
        }else{
            ++this_it;
        }
    }
    while(dl_it!=dl.end())
        insert(end(),*(dl_it++));
    dl.size = 0;
    dl.tail = dl.head->next;
}
#endif
