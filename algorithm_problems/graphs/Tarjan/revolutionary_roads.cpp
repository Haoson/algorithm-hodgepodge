/*************************************************************************
  > File Name: revolutionary_roads.cpp
  > Author:Haoson 
  > Created Time: Sun 16 Nov 2014 08:14:26 PM PST
  > Description:SGU 525Revolutionary Roads(http://acm.sgu.ru/problem.php?contest=0&problem=525) 
 ************************************************************************/
/**
 *思路：Tarjan缩点，然后dfs
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

#define DEBUG

struct Road{
    size_t id,from_city,to_city;
};

static size_t city_num;
static size_t road_num;
static vector<Road> roads;
static vector<vector<size_t> > adj_matrix;//图的邻接矩阵,adj_matrix[i][j]=1表示城市i能到达城市j,0表示不能到达
static vector<bool> visited;

void processInput();//处理输入
void processOutput();//处理输出
void preProcessAdjMatrix();
void dfs(size_t city,size_t fa_city,vector<bool>&isVisited);

int main(int argc,char*argv[]){
    processInput();
    preProcessAdjMatrix(); 
    processOutput();
    return 0;
}

void dfs(size_t city,size_t fa_city,vector<bool>& isVisited){
    isVisited[city] = true;
    size_t a;
    for(size_t i=1;i!=city_num+1;++i){
        a = adj_matrix[city][i];
        if(a!=0&&!(isVisited[i])&&!(visited[city])){
             dfs(i,city,isVisited);
         }
    }
    for(size_t i=1;i!=city_num+1;++i){
        if((adj_matrix[city][i])!=0)
            adj_matrix[fa_city][i] = 1;
    }
}
void preProcessAdjMatrix(){
    vector<bool> isVisited;
    isVisited.assign(city_num+1,false);
    for(size_t i=1;i!=city_num+1;++i){
        dfs(i,0,isVisited);
        visited[i] = true;
        std::fill(isVisited.begin(),isVisited.end(),false);
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/revolutionary_roads_input.txt","r",stdin);
    if(cin>>city_num>>road_num){
        visited.assign(city_num+1,false);
        adj_matrix.assign(city_num+1,vector<size_t>(city_num+1,0));
        Road temp_road;
        for(size_t i=1;i!=road_num+1;++i){
            cin>>(temp_road.from_city)>>(temp_road.to_city);
            temp_road.id = i;
            roads.push_back(temp_road);
            adj_matrix[temp_road.from_city][temp_road.to_city] = 1;//横行表示能从from_city到达的城市
        }
    }
}

void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/revolutionary_roads_output.txt","w",stdout);
#else
    cout<<"dfs与处理之后的邻接图："<<endl;
    for(size_t i=0;i!=city_num+1;++i){
        for(size_t j=0;j!=city_num+1;++j){
            cout<<(adj_matrix[i][j])<<" ";
        } 
        cout<<endl;
    }
#endif
}
