/*************************************************************************
  > File Name: p_cousin.cpp
  > Author:Haoson 
  > Created Time: Sun 16 Nov 2014 05:17:33 AM PST
  > Description:p-cousin问题，由LCA问题演变而来，可以参见UVa OJ 115-Climbing Trees (家谱树)问题，p-cousin问题是家谱树问题的一个简化版问题
  > UVa OJ 115-Climbing Trees(http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=51)
 ************************************************************************/
/**
 *思路：根据p-cousin的定义，首先这题是一个典型的关于LCA算法的题目。由于有范围查询，所以需要将LCA问题转换为RQM问题
 **/
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

//#define DEBUG

typedef pair<int,int> pp;
const int MAX_LOG  =14;//2^14>10000
static size_t rmq_index = 0;
static size_t root;//根节点
static size_t cousin_node;//需要求的node的cousin
static size_t p_cousin_num;//p
static shared_ptr<vector<size_t> > adj_table_ptr; //树的邻接表表示
static shared_ptr<vector<int> > parent_ptr; //每个节点倍增到根节点的数组的数组的指针
static size_t node_num;//比实际节点数多一个，方便计算
static vector<int> depth; //节点到根节点的深度
static shared_ptr<vector<size_t> > same_depth_nodes;//同一深度的节点的集合
static vector<size_t> rmq_left; //RMQ表左下标
static vector<size_t> rmq_right; //RMQ表右下标
static vector<size_t> cousins;

void processInput();
void processOutput();
void dfs(int child_node,int father_node,int depth_to_root);//使用深度优先的方法求出所有节点到根节点的深度和线段树
void pCousin();
int findKthParent(int node1,int k);//找出node1的第k个祖先节点
void preprocessParent();


int main(int argc,char*argv[]){
    processInput();
    dfs(1,-1,0);
#ifdef DEBUG
    for(size_t i=1;i!=node_num;++i){
        cout<<i<<":"<<(rmq_left[i])<<" "<<(rmq_right[i])<<endl;
    }
#endif
    preprocessParent();
    pCousin();
    processOutput();
    return 0;
}

void pCousin(){
    int p_node = findKthParent(static_cast<int>(cousin_node),static_cast<int>(p_cousin_num)); 
    if(p_node!=-1){
        size_t l = rmq_left[static_cast<size_t>(p_node)];
        size_t r = rmq_right[static_cast<size_t>(p_node)];
        for(auto it=same_depth_nodes.get()[depth[cousin_node]].begin();it!=same_depth_nodes.get()[depth[cousin_node]].end();++it){
            if(*it!=cousin_node){
                if(l<rmq_left[(*it)]&&rmq_right[(*it)]<r){
                    cousins.push_back(*it); 
                }
            }
        }
    }
}

int findKthParent(int node1,int k){
    for(size_t i =0;i!=MAX_LOG;++i){
        if((k>>i)&1){
            node1 = parent_ptr.get()[node1][i];
        }
    } 
    return node1;
}
void dfs(int child_node,int father_node,int depth_to_root){
    depth[static_cast<size_t>(child_node)] = depth_to_root;
    same_depth_nodes.get()[depth_to_root].push_back(static_cast<size_t>(child_node));
    parent_ptr.get()[static_cast<size_t>(child_node)][0] = father_node;
    rmq_left[static_cast<size_t>(child_node)] = rmq_index++;    
    for(size_t i=0,j=0;i!=adj_table_ptr.get()[child_node].size();++i,++j){
        if(static_cast<int>(adj_table_ptr.get()[child_node][i])!=father_node){
            dfs(static_cast<int>(adj_table_ptr.get()[child_node][i]),child_node,depth_to_root+1);
        }
    }
    rmq_right[static_cast<size_t>(child_node)] = rmq_index++;
}
void preprocessParent(){
    for(size_t j=1;j!=node_num;++j){ //节点从1开始
        for(size_t i = 0;i!=MAX_LOG-1;++i){
            if(parent_ptr.get()[j][i]<0)
                parent_ptr.get()[j][i+1]  = -1;
            else
                parent_ptr.get()[j][i+1] = parent_ptr.get()[static_cast<size_t>(parent_ptr.get()[j][i]) ][i];
        }
    } 
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/p_cousin_input.txt","r",stdin);
    size_t n;
    size_t child_node,father_node;
    if(cin>>n){
        node_num = n+1;
        root = 1;
        adj_table_ptr = shared_ptr<vector<size_t> >(new vector<size_t>[node_num],[](vector<size_t>* p ){delete[]p;});
        same_depth_nodes = shared_ptr<vector<size_t> >(new vector<size_t>[node_num],[](vector<size_t>* p ){delete[]p;});
        for(size_t i=0;i!=n-1;++i){
            cin>>father_node>>child_node;
            adj_table_ptr.get()[father_node].push_back(child_node); 
            adj_table_ptr.get()[child_node].push_back(father_node); 
        }
        cin>>cousin_node>>p_cousin_num;
        depth.assign(node_num,-1);
        rmq_left.assign(node_num,0); 
        rmq_right.assign(node_num,0); 
        parent_ptr = shared_ptr<vector<int> >(new vector<int>[node_num],[](vector<int> *p){delete[]p;});
        for(size_t i=0;i!=node_num;++i)
            parent_ptr.get()[i].assign(MAX_LOG,-1);
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/p_cousin_output.txt","w",stdout);
    for(auto it=cousins.begin();it!=cousins.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#else
    for(auto it=cousins.begin();it!=cousins.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#endif
}
