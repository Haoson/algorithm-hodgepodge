/*************************************************************************
  > File Name: popular_cows.cpp
  > Author:Haoson 
  > Created Time: Sun 16 Nov 2014 04:38:06 PM PST
  > Description:poj 2186 Popular Cows(http://poj.org/problem?id=2186)
  >模型转换：给定有向图，满足X使得图中任意的顶点Y都存在Y-->X的路径，计算X满足条件的顶点总数
 ************************************************************************/
/**
 *思路：极大强连通分量+缩点问题。可以通过Tarjan算法或者Kosataju算法求有向图的极大强连通分量，这里使用后者
 *【Kosataju算法步骤】
 *1)在该图的逆图（所有边做反向）上运行dfs；
 *2)在原图上，按第一步得出的后序编号的逆序进行dfs。也就是说，在第二次dfs时，每次都挑选当前未访问的结点中具有最大后序编号的顶点作为dfs树的树根。
 **/
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

//#define DEBUG

struct Edge{
    size_t from,to;
    Edge():from(0),to(0){}
};

static int k_times = 0;
static vector<vector<Edge> >adj;
static vector<vector<Edge> >reverse_adj;
static size_t node_num;
static size_t edge_num;
static vector<int> k_left;
static vector<int> k_right;
static vector<size_t> lcc_nodes;//最大汇连通分量中的所有节点
static pair<size_t,int>  reverse_max_r_node(0,-1);//逆向图中的右边界最大的节点与之对应的边界值

void processInput();
void processOutput();
void dfsReverseAdj(size_t node_index);
void dfsLCC(size_t node_index);

int main(int argc,char*argv[]){
    processInput();
    for(size_t i=1;i!=node_num+1;++i)
        dfsReverseAdj(i);
    dfsLCC(reverse_max_r_node.first);
    processOutput();
    return 0;
}
void dfsLCC(size_t node_index){
    lcc_nodes.push_back(node_index);
     for(auto it=adj[node_index].begin();it!=adj[node_index].end();++it){
         if((*it).to==reverse_max_r_node.first)
             return;
         else
            dfsLCC((*it).to); 
    }
}
void dfsReverseAdj(size_t node_index){
    if(k_left[node_index]!=-1){
        return;
    }
    k_left[node_index] = k_times++;
    for(auto it=reverse_adj[node_index].begin();it!=reverse_adj[node_index].end();++it){
        dfsReverseAdj((*it).to); 
    }
    k_right[node_index] = k_times++;
    if(k_right[node_index]>reverse_max_r_node.second){
        reverse_max_r_node.second = k_right[node_index];
        reverse_max_r_node.first = node_index;
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/popular_cows_input.txt","r",stdin);
    if(cin>>node_num>>edge_num){
        adj.assign(node_num+1,vector<Edge>());
        reverse_adj.assign(node_num+1,vector<Edge>());
        Edge temp_edge,reverse_edge;
        for(size_t i=1;i!=edge_num+1;++i){
            cin>>(temp_edge.from)>>(temp_edge.to);
            reverse_edge.from = temp_edge.to;
            reverse_edge.to = temp_edge.from;
            adj[temp_edge.from].push_back(temp_edge);
            reverse_adj[reverse_edge.from].push_back(reverse_edge);
        }
        k_left.assign(node_num+1,-1);
        k_right.assign(node_num+1,-1);
    }
}

void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/popular_cows_output.txt","w",stdout);
    for(auto it=lcc_nodes.begin();it!=lcc_nodes.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#else
    cout<<"逆序dfs之后的线段树："<<endl;
    for(size_t i=1;i!=node_num+1;++i){
        cout<<"节点"<<i<<": "<<(k_left[i])<<" "<<(k_right[i])<<endl;
    }
    cout<<"最大汇连通分量的所有节点：";
    for(auto it=lcc_nodes.begin();it!=lcc_nodes.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#endif
}
