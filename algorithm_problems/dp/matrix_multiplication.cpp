/*************************************************************************
  > File Name: matrix_multiplication.cpp
  > Author:Haoson 
  > Created Time: Sat 15 Nov 2014 04:17:26 AM PST
  > Description:矩阵链乘问题，使得矩阵相乘的复杂度最小（http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=284）.矩阵复杂度：若A=n*m,B=m*p,则A*B的复杂度为n*m*p 
 ************************************************************************/
/**
 *思路：M[i,j]  =  min{M[i,k]+M[k+1,j]+di*dk+1*dj+1}(i<=k<=j-1)其中di是矩阵Ai的第一维,dk+1是断开处矩阵Ak的第二维（即Ak+1的第一维），
 *dj+1是最后一个矩阵 Aj 的第二维。
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<limits>
using namespace std;

#define DEBUG

typedef long long LL;
struct Matrix{
    size_t row,col;
};
const LL INF = std::numeric_limits<LL>::max();
static size_t matrix_num;
static vector<Matrix> matrixs;
static vector<vector<LL> > dp;
static vector<vector<size_t> > path;

void processInput();
void processOutput();
void matrixMulti();
void print(size_t i,size_t j);

int main(int argc,char*argv[]){
    processInput();
    matrixMulti();
    processOutput();
}
void matrixMulti(){
    dp.assign(matrix_num+1,vector<LL>(matrix_num+1,INF));
    path.assign(matrix_num+1,vector<size_t>(matrix_num+1,0));
    for(size_t i=0;i!=matrix_num+1;++i)
        dp[i][i] = 0;
    LL res; 
    for(size_t len=1;len!=matrix_num;++len){
        for(size_t i=1,j =i+len;j!=matrix_num+1;++i,++j){//处理长度从1到(matrix_num-1)的矩阵链乘结果
            for(size_t k=i+1;k<=j;++k){
                res = dp[i][k-1]+dp[k][j]+static_cast<LL>(matrixs[i].row*matrixs[k].row*matrixs[j].col);  
                if(res<dp[i][j]){
                    dp[i][j] = res;
                    path[i][j] = k;
                }
            }
        }
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/matrix_multiplication_input.txt","r",stdin);
    while(cin>>matrix_num&&matrix_num){
        matrixs.clear();
        dp.clear();
        path.clear();
        matrixs.assign(matrix_num,Matrix());
        for(size_t i=0;i!=matrix_num;++i){
            cin>>(matrixs[i].row)>>(matrixs[i].col);
        }
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/matrix_multiplication_output.txt","w",stdout);
    print(1,matrix_num);
#else
    print(1,matrix_num);
#endif
}
void print(size_t i,size_t j) {
    if(j==i)
        cout<<"A"<<i;
    if(j-i==1) 
        cout<<"A"<<i<<" * "<<"A"<<j;
    else{
        size_t flag = path[i][j];
        cout<<"(";
        print(i,flag-1);     
        cout<<" * ";
        if(flag!=0)
            cout<<"(";
        print(path[i][j],j);     
        if(flag!=0)
            cout<<")";
        cout<<")";
    }
}
