/*************************************************************************
  > File Name: graph_coloring.cpp
  > Author:Haoson 
  > Created Time: Sat 15 Nov 2014 09:48:29 PM PST
  > Description: poj 1419 Graph Coloring (http://poj.org/problem?id=1419) 
 ************************************************************************/
/**
 *思路： 图着色问题，求的是最大独立集，这题可以使用dfs（搜索问题），也可以使用dp（动态规划问题），
 *这里使用dp,其实也相当于0/1背包问题,但是限制条件不好表示，dfs直观明了
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

//#define DEBUG

struct Edge{
    size_t from_id,to_id;
    Edge():from_id(0),to_id(0){}
};
static size_t node_num;//点的个数
static size_t edge_num;//边的个数
static size_t max_num;//最大独立集中的节点个数
static vector<vector<size_t> > adjacency_list;
static vector<bool> visited;
static vector<size_t> chosen_nodes;//最大独立集中的节点

void processInput();
void processOutput();
void output();
void dfsColoring(size_t node_index,size_t total_num);//对节点node_index进行dfs着色

int main(int argc,char*argv[]){
    processInput();
    processOutput();
    int time;
    Edge edge;
    if(cin>>time){
        while(time--){
            cin>>node_num>>edge_num;
            adjacency_list.assign(node_num+1,vector<size_t>());
            visited.assign(node_num+1,false);
            max_num = 0;
            for(size_t i=0;i!=edge_num;++i){
                cin>>(edge.from_id)>>(edge.to_id);    
                adjacency_list[edge.from_id].push_back(edge.to_id);
                adjacency_list[edge.to_id].push_back(edge.from_id);
            }
            dfsColoring(1,0);
            output();
        }
    }
    return 0;
}
void dfsColoring(size_t node_index,size_t total){
    if(node_index>node_num){
        if(total>max_num){
            max_num = total;
            chosen_nodes.clear();
            for(size_t i=1;i!=node_num+1;++i){
                if(visited[i])
                    chosen_nodes.push_back(i);
            }
        } 
        return;
    }
    for(auto it=adjacency_list[node_index].begin();it!=adjacency_list[node_index].end();++it){
        if(visited[(*it)]){//邻接点有黑色的点
            dfsColoring(node_index+1,total);
            return;
        }
    }
    visited[node_index] = true;//自身加入独立集
    dfsColoring(node_index+1,total+1);
    visited[node_index] = false;//自身不加入独立集
    dfsColoring(node_index+1,total);
}
void output(){
    cout<<max_num<<endl;
    for(size_t i=0;i!=chosen_nodes.size();++i){
        cout<<(chosen_nodes[i])<<" ";
    }
    cout<<endl;
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/graph_coloring_input.txt","r",stdin);
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/graph_coloring_output.txt","w",stdout);
#endif
}
