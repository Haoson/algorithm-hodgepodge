/*************************************************************************
  > File Name: missile_silos.cpp
  > Author:Haoson 
  > Created Time: Thu 13 Nov 2014 11:32:14 PM PST
  > Description:Codeforces 144D. Missile Silos 最短路(http://codeforces.com/problemset/problem/144/D) 
 ************************************************************************/
/**
 *思路：首先用dijkstra算法求出每个节点到s的最短路d[]数组，属于DP里面的求解的问题有重叠子问题
 **/
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<limits>
using namespace std;
//#define DEBUG

typedef pair<size_t,size_t> pa;//第一个参数表示顶点，第二个参数表示顶点到源点的距离
struct Node{
    size_t id,from_node_id,weight;
    Node(){}
    Node(size_t f,size_t i,size_t w){
        from_node_id = f;
        id = i;
        weight = w;
    }
};
//函数对象，重载优先队列中的Comp
struct Less{
    bool operator()(const pa&a,const pa&b){
        return a.second<b.second;
    }
};
static vector<vector<Node> > graph;
static vector<Node>edges;//存储所有边
static vector<size_t> distance_to_capital;//所有点距离源点的最短距离
static size_t capital;//源点
static size_t road_num;//道路的数目
static size_t  l_distance;//从源点到建导弹发射井的距离

void processInput();
void dijkstra(size_t s);//用dijkstra算法求出每个节点到源点的最短距离
int computeMissileSilosNum();
void processOutput(int num);

int main(int argc,char*argv[]){
    processInput();
    dijkstra(capital);
    int res  =computeMissileSilosNum();
    processOutput(res);
    return 0;
}

void dijkstra(size_t s){
    priority_queue<pa,vector<pa>,Less> pq;
    pa p_temp = pa(s,0);
    distance_to_capital[capital] = 0;
    pq.push(p_temp);
    Node temp_node;
    while(!pq.empty()){
        p_temp = pq.top();
        pq.pop();
        //取出当前点的邻接点
        for(size_t i=0;i!= graph[p_temp.first].size();++i){
            temp_node = graph[p_temp.first][i]; 
            if((p_temp.second+temp_node.weight)<distance_to_capital[temp_node.id]){
                distance_to_capital[temp_node.id] = p_temp.second+temp_node.weight;
                pq.push(pa(temp_node.id,distance_to_capital[temp_node.id]));
            }
        }
    }
}

int computeMissileSilosNum(){
    int res = 0;
    //计算顶点到capital的距离，如符合要求，则可以建导弹发射井
    for(auto it = distance_to_capital.begin();it!=distance_to_capital.end();++it)
        if(*it==l_distance)
            ++res;
    //计算是否可以在每天边上建立导弹发射井
    for(auto it = edges.begin();it!=edges.end();++it){
        if((l_distance>distance_to_capital[(*it).from_node_id])&&((*it).weight+distance_to_capital[(*it).from_node_id]>l_distance)&&
                (l_distance+(l_distance-distance_to_capital[(*it).from_node_id])<(distance_to_capital[((*it).id)]+(*it).weight)))//在靠近from_node_id顶点的边上
            ++res;
        if((l_distance>distance_to_capital[(*it).id])&&((*it).weight+distance_to_capital[(*it).id]>l_distance)&&
                (l_distance+(l_distance-distance_to_capital[(*it).id])<(distance_to_capital[((*it).from_node_id)]+(*it).weight)))//在靠近id顶点的边上
            ++res;
        if((l_distance>distance_to_capital[(*it).id])&&((*it).weight+distance_to_capital[(*it).id]>l_distance)&&
                 (2*l_distance==distance_to_capital[(*it).from_node_id]+(distance_to_capital[((*it).id)]+(*it).weight)))//在from_node_id和id两个node的边上的正中间
            ++res;
    } 
    return res;
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/missile_silos_input.txt","r",stdin);
    size_t n;
    if(cin>>n>>road_num>>capital){
        graph.assign(n+1,vector<Node>());
        distance_to_capital.assign(n+1,std::numeric_limits<int>::max());
        size_t v,u,w;
        for(size_t i=0;i!=road_num;++i){
            cin>>v>>u>>w;
            graph[static_cast<size_t>(v)].push_back(Node(v,u,w));
            graph[static_cast<size_t>(u)].push_back(Node(u,v,w));
            edges.push_back(Node(u,v,w));
        }    
        cin>>l_distance;
    } 
}

void processOutput(int num){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/missile_silos_output.txt","w",stdout);
    cout<<num<<endl;
#else
    for(size_t i=0;i!=graph.size();++i){
        cout<<"第"<<i<<"个节点，邻接点有:";
        for(size_t j=0;j!=graph[i].size();++j){
            cout<<"节点="<<(graph[i][j].id)<<",权重="<<(graph[i][j].weight)<<" ";
        }
        cout<<endl;
    }
    cout<<"顶点到源点的最短距离：";
    for(size_t i=0;i!=distance_to_capital.size();++i){
        cout<<"顶点="<<i<<";距离="<<(distance_to_capital[i])<<endl;
    }
    for(auto it=edges.begin();it!=edges.end();++it){
        cout<<"边："<<((*it).from_node_id)<<"-"<<((*it).id)<<"-"<<((*it).weight)<<endl;
    }
    cout<<"可以建立的导弹发射井的数目="<<num<<endl;
#endif
}
