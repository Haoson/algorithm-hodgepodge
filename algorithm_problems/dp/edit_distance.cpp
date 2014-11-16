/*************************************************************************
  > File Name: edit_distance.cpp
  > Author:Haoson 
  > Created Time: Sun 16 Nov 2014 01:31:26 AM PST
  > Description:POJ 3356 AGTC(经典DP Edit Distance)(http://poj.org/problem?id=3356) 
 ************************************************************************/
/**
 *思路：最小编辑距离，也是求最长公共子序列，dp[i][j]表示第一个字符串的前i个字符要和第二个字符串的前j个字符匹配需要的最少操作次数
 *状态转移公式：若A[i]==B[j],dp[i][j]=dp[i-1][j-1];若不相等，dp[i][j]=min{dp[i-1][j]+1, dp[i-1][m-1]+1, dp[i][j-1]+1}
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<cstdarg>
using namespace std;

//#define DEBUG

static string source_string[2];
static size_t source_length[2];
static vector<vector<size_t> >dp;//dp[i][j]表示第一个字符串的前i个字符要和第二个字符串的前j个字符匹配需要的最少操作次数

void processInput();
void processOutput();
void computeDistance();
size_t min(size_t num,...);


int main(int argc,char*argv[]){
    processInput();
    computeDistance();
    processOutput();
}

void computeDistance(){
    dp.assign(source_length[0]+1,vector<size_t>(source_length[1]+1,0));    
    for(size_t i=1;i!=source_length[0]+1;++i){
        dp[i][0] = i;
    }
    for(size_t i=1;i!=source_length[1]+1;++i){
        dp[0][i] = i;
    }
    for(size_t i=1;i!=source_length[0]+1;++i){
        for(size_t j=1;j!=source_length[1]+1;++j){
            if(source_string[0][i-1]==source_string[1][j-1]){
                dp[i][j] = dp[i-1][j-1];
            }else{
                dp[i][j] = min(3,dp[i-1][j]+1,dp[i-1][j-1]+1,dp[i][j-1]+1);    
            }
        }
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/edit_distance_input.txt","r",stdin);
    string temp;
    size_t num;
    for(size_t i=0;i!=2;++i){
        cin>>num>>temp;
        source_length[i] = num;
        source_string[i] = temp;
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/edit_distance_output.txt","w",stdout);
    cout<<(dp[source_length[0]][source_length[1]])<<endl;
#else
    cout<<(dp[source_length[0]][source_length[1]])<<endl;
#endif
}
size_t min(size_t num,...){
    size_t res=0,temp;
    va_list vl;
    va_start(vl,num);
    for(size_t i=0;i!=num;++i){
        temp = va_arg(vl,size_t);
        if(i==0)
            res = temp;
        else
            res = (temp<res)?temp:res;
    }
    va_end(vl);
    return res;
}
