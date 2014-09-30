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
        value_type get(const key_type& k);
        void put(const key_type& k,const value_type &v);

        key_type& min()const;   //最小键
        key_type& max()const;   //最大键
        key_type& floor(const key_type&)const; //向上取整
        key_type& ceiling(const key_type&)const;//向下取整

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

    protected:
        BSTNode* root;
};
template <typename K,typename V>
typename BST<K,V>::value_type BST<K,V>::get(const key_type& k){
    
}
template <typename K,typename V>
void BST<K,V>::put(const key_type& k,const value_type &v){

}

#endif
