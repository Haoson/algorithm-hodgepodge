/*************************************************************************
  > File Name: cursor_based_list.h
  > Author:Haoson 
  > Created Time: Thu 25 Sep 2014 05:34:49 AM PDT
  > description:游标实现的定长list
 ************************************************************************/

#ifndef CURSOR_BASED_LIST_H_
#define CURSOR_BASED_LIST_H_
#include <cstdint> 
#include <iostream>
#define DEFAULT_SIZE 16 //默认数组长16
template <typename T>
class CursorList;
template <typename T>
class CursorListIterator;

template <typename T>
class CursorNode{
    public:
        CursorNode():is_free(true),next(0){}
        CursorNode(T x){
            this->CursorNode(x,0);
        }
        CursorNode(T x,int n):is_free(true),data(x),next(n){}
    private:
        bool is_free;
        T data;
        int32_t next;
    friend class CursorList<T>;
    friend class CursorListIterator<T>;
};
template <typename T>
class CursorListIterator{
    public:
        typedef CursorListIterator<T> iterator;
        CursorListIterator(CursorNode<T>*begin_node, CursorNode<T>*node=0):head_node(begin_node),current(node){}
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
            current = (head_node+(current->next));
            return *this;
        }
        iterator operator++(int){
            iterator temp(*this);
            ++(*this);
            return temp;
        }
    private:
        CursorNode<T>* head_node;
        CursorNode<T>* current;
    friend class CursorList<T>;
};
template <typename T>
class CursorList{
    public:
        typedef T value_type;
        typedef CursorListIterator<T> iterator;
        CursorList(int32_t sz = DEFAULT_SIZE):size(sz+2),cursor_space(0){}
        CursorList(const CursorList<T>&);
        CursorList<T>& operator=(const CursorList<T>&);
        ~CursorList();
        bool isEmpty()const{
            return  (cursor_space+1)->next == 0;
        }
        bool create();
        iterator zeroth();//返回第1个元素（已分配出去的）前面的那个元素的迭代器
        iterator first();//返回第一个元素的迭代器
        iterator last();//返回最后一个元素的后一个元素的迭代器
        bool insert(iterator pos, const T &x); //插入到迭代器pos之后
        bool remove(const iterator & pos,T &x); //删除迭代器pos处的元素
        bool remove(const T &x);//删除第一个元素X
        iterator find(T& node_data);
        void makeEmpty();
        void output()const;
    private:
        void initFromOther(const CursorList<T>&);
        void freeAllSpace();
        int32_t findPrevious(int32_t current_pos,int32_t start_pos);
        bool cursorSpaceAlloc(int32_t&);
        void cursorSpaceFree(int32_t pos);
        int32_t size;
        CursorNode<T>* cursor_space;
};

template <typename T>
bool CursorList<T>::create(){
    bool is_success = false;
    cursor_space = new(std::nothrow) CursorNode<T>[size];
    if(cursor_space){
        cursor_space->next = 2;//位置0链接到位置2,因为前两个位置不存放数据
        for(int i = 2; i < (size-1); ++i){
            (cursor_space+i)->next = i+1;  
        }
        is_success = true;
    }
    return is_success;
}
template <typename T>
void CursorList<T>::initFromOther(const CursorList<T>&cl){
    this->size = cl.size;
    create();
    for(int i = 0; i < size; ++i){
        (cursor_space+i)->next = (cl.cursor_space+i)->next;
        (cursor_space+i)->data = (cl.cursor_space+i)->data;
    }
    
}
template <typename T>
void CursorList<T>::freeAllSpace(){
    if(cursor_space){
        delete[]cursor_space;
    }
    cursor_space = 0;
    size = DEFAULT_SIZE;
}
template <typename T>
CursorList<T>::CursorList(const CursorList<T>& cl){
    initFromOther(cl);
}
template <typename T>
CursorList<T>& CursorList<T>::operator=(const CursorList<T>& cl){
    if(&cl != this){
        freeAllSpace();
        initFromOther(cl);
    }
    return *this;
}
template <typename T>
CursorList<T>::~CursorList(){
    freeAllSpace();
}
template <typename T>
void CursorList<T>::makeEmpty(){
    while((cursor_space+1)->next)
        remove((cursor_space+((cursor_space+1)->next))->data);
}
template <typename T>
void CursorList<T>::output()const{
    int32_t pos = (cursor_space+1)->next;
    while(pos){
        std::cout<<((cursor_space+pos)->data);
        pos = (cursor_space+pos)->next;
        if(pos)
            std::cout<<"->";
        else
            std::cout<<std::endl;
    }
}
template <typename T>
bool CursorList<T>::cursorSpaceAlloc(int32_t& alloc_pos){
    alloc_pos = cursor_space->next;
    if(alloc_pos){
        int32_t pre_pos = findPrevious(alloc_pos,0);//将此位置从未分配链接中去除
        (cursor_space+pre_pos)->next = (cursor_space+alloc_pos)->next;    
        //将此位置加入已分配的链接中，这一步由实际插入时候做
        //(cursor_space+alloc_pos)->next=(cursor_space+1)->next;
        //(cursor_space+1)->next = alloc_pos;
    }
    return (alloc_pos!=0);
}
template <typename T>
int32_t CursorList<T>::findPrevious(int32_t current_pos,int32_t start_pos){
    while(((cursor_space+start_pos)->next)&&(current_pos != ((cursor_space+start_pos)->next)))
        start_pos = (cursor_space+start_pos)->next;
    if(current_pos != ((cursor_space+start_pos)->next))
        return 0;
    else
        return start_pos;
}
template <typename T>
void CursorList<T>::cursorSpaceFree(int32_t pos){
    //将收回的位置从已分配的链接中去除,由remove方法处理
    //int32_t pre_pos = findPrevious(pos,1);
    //(cursor_space+pre_pos)->next = (cursor_space+pos)->next; 
    (cursor_space+pos)->next = cursor_space->next;//将收回的位置放入未分配的链接中
    cursor_space->next = pos;
}
template <typename T>
typename CursorList<T>::iterator CursorList<T>::first(){
    int32_t pos = (cursor_space+1)->next;
    if(!pos)
        return last();
    else
        return iterator(cursor_space,cursor_space+pos);
}
template <typename T>
typename CursorList<T>::iterator CursorList<T>::zeroth(){
    return iterator(cursor_space,cursor_space+1);
}
template <typename T>
typename CursorList<T>::iterator CursorList<T>::last(){
    return iterator(cursor_space);
}
template <typename T>
typename CursorList<T>::iterator CursorList<T>::find(T& node_data){
    int32_t pos = (cursor_space+1)->next;
    while(pos&&(((cursor_space+pos)->data)!=node_data))
        pos = (cursor_space+pos)->next;
    if(pos)
        return iterator(cursor_space,cursor_space+pos);
    else
        return last();
}
template <typename T>
bool CursorList<T>::insert(iterator it, const T &x){
    int32_t alloc_pos;
    bool is_alloc_success = cursorSpaceAlloc(alloc_pos);
    if(is_alloc_success){
        (cursor_space+alloc_pos)->data = x;
        //挂入it之后的位置
        (cursor_space+alloc_pos)->next = it.current->next;
        it.current->next = alloc_pos;
    }
    return is_alloc_success;
}
template <typename T>
bool CursorList<T>::remove(const iterator &it,T&x){
    if(it==last())
        return false;
    int32_t current = findPrevious(it.current->next,1);
    int32_t pre = findPrevious(current,1); 
    if(pre){//remove只可能在已分配的链中，所以pre不可能为0，最小为1
        x = (cursor_space+current)->data;
        (cursor_space+pre)->next = (cursor_space+current)->next;
        cursorSpaceFree(current);
    }
    return pre!=0;
}
template <typename T>
bool CursorList<T>::remove(const T&x){
    int32_t pre_pos = 1;
    int32_t start = (cursor_space+pre_pos)->next;
    while(start&&(cursor_space+start)->data != x){
        pre_pos = start;
        start = (cursor_space+start)->next;
    }
    if(start){
        (cursor_space+pre_pos)->next = (cursor_space+start)->next;
        cursorSpaceFree(start);
    }
    return (start!=0);
}
#endif
