/*************************************************************************
  > File Name: flower_arrangement.cpp
  > Author:Haoson 
  > Created Time: Sat 15 Nov 2014 01:49:48 AM PST
  > Description:Little shop of flowers(http://acm.sgu.ru/problem.php?contest=0&problem=104) 
 ************************************************************************/
/**
 *思路：F(i,j) = max{F(i,j-1),F(i-1,j-1)+Vij},前i束花摆在前j个花瓶里
 */
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<limits>
using namespace std;

//#define DEBUG 

const int INF = std::numeric_limits<int>::max();
static size_t f,v;
static vector<vector<int> > values;
static vector<vector<int> > dp;
static stack<size_t> path;

void processInput();
void processOutput();
void flowerArrangement();
void findPath();
size_t max(size_t a,size_t b);


int main(int argc,char*argv[]){
    processInput();
    flowerArrangement();
    findPath();
    processOutput();
}

void flowerArrangement(){
    for(size_t i=0;i!=v;++i)
        dp[0][i] = 0;//零束花放在前i个瓶子里产生的value都是零
    for(size_t i=0;i!=f;++i){//i束花放入j个花瓶中产生的value值
        for(size_t j=0;j!=v;++j){
            if(j>=i)
                dp[i+1][j+1] = max(dp[i+1][j],dp[i][j]+values[i+1][j+1]);    
        }
    }
}
void findPath(){
    size_t temp_v = v;
    for(size_t i=f;i!=0;--i){        
        if((dp[i][temp_v-1])<(dp[i-1][temp_v-1]+values[i][temp_v])){//判断第i束花是否放在temp_v这个位置上
            path.push(temp_v);
        }else{//第i束花不是放在temp_v处，所以这束花需要继续找到自己的位置
            ++i;
        }
        --temp_v;
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/flower_arrangement_input.txt","r",stdin);
    if(cin>>f>>v){
        values.assign(f+1,vector<int>(v+1,0));
        dp.assign(f+1,vector<int>(v+1,-INF));
        for(size_t i=0;i!=f;++i){
            for(size_t j=0;j!=v;++j){
                cin>>(values[i+1][j+1]);
            }
        }
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/flower_arrangement_output.txt","w",stdout);
    cout<<(dp[f][v])<<endl;
    while(!path.empty()){
        cout<<(path.top())<<" ";
        path.pop();
    }
    cout<<endl;
#else
    cout<<"原始数据："<<endl;;
    for(size_t i=0;i!=f;++i){
        for(size_t j=0;j!=v;++j){
            cout<<(values[i+1][j+1])<<" ";
        }
        cout<<endl;
    }
    cout<<"最大value="<<(dp[f][v])<<endl;
    cout<<"路径=";
    while(!path.empty()){
        cout<<(path.top())<<" ";
        path.pop();
    }
    cout<<endl;

#endif
}
size_t max(size_t a,size_t b){
    return (a>b)?a:b;
}
