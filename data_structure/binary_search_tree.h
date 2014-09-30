/*************************************************************************
  > File Name: binary_search_tree.h
  > Author:Haoson 
  > Created Time: Mon 29 Sep 2014 04:57:26 PM PDT
  > Description:二叉查找树的实现 
 ************************************************************************/

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_
#include <iostream>
#include "doubly_linked_list.h"
template <typename KEY,typename VALUE>
class BST{
    class BSTNode{
        public:
            KEY key;
            VALUE value;
            BSTNode* left;  //指向左子树的链接
            BSTNode* right; //指向右子树的链接
            size_t node_num; //表示以该节点为根的子树中的节点总数
            BSTNode(KEY k,VALUE v,size_t num,BSTNode* l = nullptr,BSTNode r = nullptr):key(k),value(v),left(l),right(r),node_num(num){}
    };

    public:
        typedef KEY key_type;
        typedef VALUE value_type;
        typedef size_t size_type ;
        typedef typename DList<KEY>::iterator iterator;

        BST(BSTNode* r = nullptr):root(r){}
        BST(const BST& bst);
        BST& operator=(const BST&);
        ~BST();
        size_type size(){
            size(root);
        }
        bool get(const key_type& k,value_type& v);
        void put(const key_type& k,const value_type &v);

        key_type& min()const;   //最小键
        key_type& max()const;   //最大键
        bool floor(const key_type& k,key_type& res)const; //向上取整,当不存在比给定的k大的键时，返回false，存在时，返回true，并将找到的key写入res中
        bool ceiling(const key_type&,key_type&)const;//向下取整

        key_type& select(size_type n)const; //找出排名为n的节点 
        size_type rank(const key_type& k)const; //找出键k的排名

        void deleteMin();
        void deleteMax();
        void deleteKey(const key_type&);

        iterator keys();  
    private:
        size_t size(BSTNode* node){
            return (node!=nullptr)?node->node_num:0;
        } 
        bool get(BSTNode* node,const key_type& k,value_type& v);
        BSTNode* put(BSTNode* node,const key_type& k,const value_type& v);
        BSTNode* floor(BSTNode*,const key_type&,key_type&);
    protected:
        BSTNode* root;
};
template <typename K,typename V>
bool BST<K,V>::get(const key_type& k,value_type& v){
    return get(root,k,v);     
}
template <typename K,typename V>
bool BST<K,V>::get(BSTNode* node,const key_type& k,value_type& v){
    if(!node)
        return false;
    if(k < (node->key)){
        return get(node->left,k,v);
    }
    else if(k > (node->key)){
        return get(node->right,k,v);
    }
    else{
        v = node->value;
        return true;
    }
}
template <typename K,typename V>
void BST<K,V>::put(const key_type& k,const value_type &v){
    root = put(root,k,v);
}
template <typename K,typename V>
typename BST<K,V>::BSTNode* BST<K,V>::put(BSTNode* node,const key_type& k,const value_type& v){
    //如果key存在，则更新key对应的value值，若不存在，创建一个新节点
    if(!node){
        return new BSTNode(k,v,1);
    }
    if(k < (node->key)){
        node->left = put(node->left,k,v);
    }else if(k < (node->key)){
        node->right = put(node->right,k,v);
    }else{
        node->value = v; 
    }
    node->node_num = size(node->left)+size(node->right)+1;
    return node;
}

template <typename K,typename V>
typename BST<K,V>::key_type& BST<K,V>::min()const{
    BSTNode* temp_node = root;
    while((temp_node->left))
        temp_node = temp_node->left;
    return temp_node->value;
}
template <typename K,typename V>
typename BST<K,V>::key_type& BST<K,V>::max()const{
    BSTNode* temp_node = root;
    while((temp_node->right))
        temp_node = temp_node->right;
    return temp_node->value;
}
template <typename K,typename V>
bool BST<K,V>::floor(const key_type& k,key_type& res)const{
    BSTNode* temp_node = floor(root,k,res); 
    if(temp_node){
        res = temp_node->key;
    }
    return (temp_node!=nullptr);
}
template <typename K,typename V>
typename BST<K,V>::BSTNode* BST<K,V>::floor(BSTNode* node,const key_type& k,key_type& res){
    if(!node)
        return nullptr;
    if(k < (node->key)){
    
    }else if(k > (node->key)){
     
    }else{
        return node;
    }
}
template <typename K,typename V>
bool BST<K,V>::ceiling(const key_type& k,key_type& res)const{

}
#endif
