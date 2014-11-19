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
#include<set>
#include<algorithm>
using namespace std;

//#define DEBUG

struct Road{
    size_t id,from_city,to_city;
};

static size_t city_num;
static size_t road_num;
static vector<Road> roads;
static vector<vector<size_t> > adj_matrix;//图的邻接矩阵,adj_matrix[i][j]=1表示城市i能到达城市j,0表示不能到达
static vector<bool> visited;
static set<size_t> rev_roads;//能变成revolutionary roads的道路的编号
static size_t max_w=0;//最大强连通分量的节点个数
static size_t rev_road_id;//revolutionary road 编号

void processInput();//处理输入
void processOutput();//处理输出
void preProcessAdjMatrix();//对邻接矩阵进行预处理，处理出来每个节点能达到的所有节点（行）和能到此节点的所有节点（列）
void dfs(size_t city,size_t fa_city,vector<bool>&isVisited);//dfs处理邻接矩阵
void changeRoad();//将每条路变成revolutionary roads，查找最大强连通分量

int main(int argc,char*argv[]){
    processInput();
    preProcessAdjMatrix(); 
    changeRoad();
    processOutput();
    return 0;
}
void changeRoad(){
    size_t temp = 0;
    for(auto it = roads.begin();it!=roads.end();++it){
        temp = 0;
        for(size_t i=1;i!=city_num+1;++i){//做交集
            if((adj_matrix[(*it).from_city][i])&(adj_matrix[i][(*it).from_city]|adj_matrix[i][(*it).to_city])){
                ++temp;
            }
        } 
        if(temp>max_w){
            max_w = temp;
            rev_roads.clear();
            rev_roads.insert((*it).id);
        }else if(temp==max_w){
            rev_roads.insert((*it).id);
        }
    }
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
        adj_matrix[i][i] = 1;
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
    cout<<max_w<<endl;
    cout<<(rev_roads.size())<<endl;
    for(auto it=rev_roads.begin();it!=rev_roads.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#else
    cout<<"dfs与处理之后的邻接图："<<endl;
    for(size_t i=0;i!=city_num+1;++i){
        for(size_t j=0;j!=city_num+1;++j){
            cout<<(adj_matrix[i][j])<<" ";
        } 
        cout<<endl;
    }
    cout<<"max w="<<max_w<<endl;
    cout<<"可替换的rev road个数："<<(rev_roads.size())<<endl;
    for(auto it=rev_roads.begin();it!=rev_roads.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#endif
}
