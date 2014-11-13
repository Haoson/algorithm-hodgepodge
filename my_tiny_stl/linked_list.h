/*************************************************************************
  > File Name: linked_list.h
  > Author:Haoson 
  > Created Time: Wed 24 Sep 2014 05:59:13 PM PDT
  > description:单链表实现的list
 ************************************************************************/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include<iostream>
template <typename T>
class LinkedList;
template <typename T>
class LinkedListIterator;
template <typename T>
class ListNode{
    public:
        ListNode(T node_data,ListNode<T> *next_node=0):data(node_data),next(next_node){}
        ListNode(){
            next = 0;
        }
        bool operator==(const ListNode<T> & ln){
            return data == ln.data;
        }
        bool operator!=(const ListNode<T>&ln){
            return !(*this==ln);
        }
    private:
        T data;
        ListNode<T> * next;
    friend class LinkedList<T>;
    friend class LinkedListIterator<T>;
};

template <typename T>
class LinkedList{
    public:
        typedef LinkedListIterator<T> iterator; 
        LinkedList():head(0),size(0){}
        ~LinkedList();
        LinkedList(const LinkedList<T>&ln);
        LinkedList<T>& operator=(const LinkedList<T>& ln); 
        int32_t length()const{
            return size;
        }
        bool isEmpty()const{
            return  head->next == 0;
        }
        bool create();
        bool search(const T& node_data)const;
        iterator zeroth() const;//返回head的迭代器 
        iterator begin() const;//返回第一个元素的迭代器
        iterator end() const;//返回最后一个元素的后一个元素的迭代器
        bool insert(const iterator pos, const T &x); //插入到迭代器pos之后
        bool erase(const iterator & pos,T &x); //删除迭代器pos处的元素
        bool erase(const T &x);//删除第一个元素X
        iterator find(T& node_data);
        void makeEmpty();
        void output()const;
    private:
        void deleteAllNodes();
        void initFromOther(const LinkedList<T>&);
        iterator findPrevious(const iterator&);
        ListNode<T> * head;
        int32_t size;
};

template <typename T>
class LinkedListIterator{
    public:
        typedef LinkedListIterator<T> iterator;
        LinkedListIterator(ListNode<T>*node=0){
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
    private:
       ListNode<T>*current; 
    friend class LinkedList<T>;
};

template <typename T>
bool LinkedList<T>::create(){
    head  = new(std::nothrow) ListNode<T>;
    return head == 0?false:true;
}
template <typename T>
LinkedList<T>::~LinkedList(){
    deleteAllNodes();
}
template <typename T>
void LinkedList<T>::deleteAllNodes(){
    ListNode<T>* temp = head;
    while(head->next){
        head = head->next;
        delete temp;
        temp = head;
    }
    delete temp;
}
template <typename T>
void LinkedList<T>::output()const{
    ListNode<T>* temp = head->next;
    while(temp){
        std::cout<<temp->data;
        temp = temp->next;
        if(temp)
            std::cout<<"->";
        else
            std::cout<<std::endl;
    }
}
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::zeroth() const{ //typename 指出后面紧跟着的名称是一个类型
    return iterator(head); 
}
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const{ //typename 指出后面紧跟着的名称是一个类型
    return iterator(head->next); 
}
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() const{
    return iterator();
}
template <typename T>
bool LinkedList<T>::insert(const iterator pos, const T & x){
    bool is_success = false;
    ListNode<T>* node = pos.current;
    ListNode<T>* new_node;    
    if(node){
        new_node =new ListNode<T>(x,node->next);
        node->next = new_node;
        size++;
        is_success = true;
    }
    return is_success; 
}
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::findPrevious(const iterator&cu){
    if(cu.current==head)
        return iterator();
    ListNode<T>* temp = head;
    while(temp->next && temp->next != cu.current){
        temp = temp->next;
    }
    return iterator(temp);
}
template <typename T>
bool LinkedList<T>::erase(const iterator & pos,T & x){
    bool is_success = false;
    ListNode<T>* node = pos.current;    
    if(node){
        x = node->data;
        iterator pre = findPrevious(pos);
        if(pre.current){
            pre.current->next = node->next;
            delete node;
            size--; 
            is_success = true;
        }
    }
   return is_success; 
} 
template <typename T>
bool LinkedList<T>::erase(const T & x){
    T temp_x = x;
    iterator xit = find(temp_x);
    T temp_t;
    return erase(xit,temp_t);
} 
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::find(T& data){
    ListNode<T>* temp = head->next;
    while(temp&&temp->data!=data){
        temp = temp->next;
    }
    return iterator(temp); 
}
template <typename T>
bool LinkedList<T>::search(const T& data)const{
    ListNode<T>* temp = head->next;
    while(temp&&temp->data!=data){
        temp = temp->next;
    }
    return (temp!=0); 
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& abl){
   initFromOther(abl); 
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& abl){
    if(&abl!=this){//防止自身赋值
        deleteAllNodes();
        initFromOther(abl);
    }
    return *this;
}
template <typename T>
void LinkedList<T>::initFromOther(const LinkedList<T>& abl){
    size = abl.size;
    head = new(std::nothrow) ListNode<T>;
    if(head){
        ListNode<T>*abl_temp = abl.head->next,*current_temp = head,*new_node;
        while(abl_temp){
            new_node = new(std::nothrow)ListNode<T>(abl_temp->data);
            if(new_node){
                current_temp->next = new_node;
                current_temp = current_temp->next;
            }
            abl_temp = abl_temp->next;
        }
    }
}
template <typename T>
void LinkedList<T>::makeEmpty(){
    ListNode<T>*temp = head->next,*save_node = head->next;
    while(temp){
        temp = temp->next;
        delete save_node;
        save_node = temp;
    }
    head->next = 0;
    size  =0;
}
#endif
