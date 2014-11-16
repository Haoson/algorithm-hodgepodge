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

#define DEBUG

typedef pair<int,int> pp;
const int MAX_LOG  =14;//2^14>10000
static size_t root;//根节点
static size_t cousin_node;//需要求的node的cousin
static size_t p_cousin_num;//p
static shared_ptr<vector<size_t> > adj_table_ptr; //树的邻接表表示
static size_t node_num;//比实际节点数多一个，方便计算
static vector<int> depth; //节点到根节点的深度

void processInput();
void processOutput();
void dfs(int child_node,int father_node,int depth_to_root);//使用深度优先的方法求出所有节点到根节点的深度和线段树

int main(int argc,char*argv[]){
    processInput();

    processOutput();
    return 0;
}


void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/p_cousin_input.txt","r",stdin);
    size_t n;
    size_t child_node,father_node;
    if(cin>>n){
        node_num = n+1;
        root = 1;
        adj_table_ptr = shared_ptr<vector<size_t> >(new vector<size_t>[node_num],[](vector<size_t>* p ){delete[]p;});
        for(size_t i=0;i!=n-1;++i){
            cin>>father_node>>child_node;
            adj_table_ptr.get()[father_node].push_back(child_node); 
            adj_table_ptr.get()[child_node].push_back(father_node); 
        }
        cin>>cousin_node>>p_cousin_num;
        depth.assign(static_cast<size_t>(node_num),-1);
    }
}
void processOutput(){
#ifndef
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/p_cousin_output.txt","r",stdin);
#else
#endif
}
