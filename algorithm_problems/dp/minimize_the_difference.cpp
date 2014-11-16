/*************************************************************************
  > File Name: minimize_the_difference.cpp
  > Author:Haoson 
  > Created Time: Sat 15 Nov 2014 08:01:20 AM PST
  > Description: 给出一组数据，要求分成两组，使得两组数字的和相差最少 
 ************************************************************************/
/**
 *思路：要使得两组数字的和相差最少，那么每一组的和都应该尽量靠近总和的一半，那么也就是说，从这n个数字中选出一部分，使其和尽可能接近sum/2。显然这是一个0-1背包问题。
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

//#define DEBUG

static vector<size_t> numbers;
static vector<vector<size_t> >dp;
static vector<size_t> path;
static size_t half_of_sum;

void processInput();
void processOutput();
void minimize();
void findPath();
size_t max(size_t a,size_t b);

int main(int argc,char* argv[]){
    processInput();
    minimize();
    findPath();
    processOutput();
}
void minimize(){
    size_t sz =numbers.size(); 
    size_t sum=0;
    std::for_each(numbers.begin()+1,numbers.end(),[&](size_t n){sum+=n;});
    half_of_sum = sum/2;
    dp.clear();
    dp.assign(sz,vector<size_t>(half_of_sum+1,0));
    std::sort(numbers.begin()+1,numbers.end());
    for(size_t i=1;i!=sz;++i){
        if(numbers[i]>half_of_sum)
            dp[i][half_of_sum] = dp[i-1][half_of_sum];
        for(size_t num = numbers[i];num<=half_of_sum;++num){
            dp[i][num] = dp[i-1][num];
            dp[i][num] = max(dp[i][num],dp[i-1][num-numbers[i]]+numbers[i]); 
        }
    }
}
void findPath(){
    size_t index =numbers.size()-1,sum_temp = half_of_sum; 
    for(size_t i=1;i!=numbers.size();++i){
        if(dp[index][sum_temp]>dp[index-1][sum_temp]){
            path.push_back(numbers[index]);
            sum_temp-=numbers[index];
        } 
        --index;
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/minimize_the_difference_input.txt","r",stdin);
    size_t i;
    numbers.push_back(0);//占位，不存储原始数据
    while(cin>>i){
        numbers.push_back(i);    
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/minimize_the_difference_output.txt","w",stdout);
    cout<<(dp[numbers.size()-1][half_of_sum])<<endl;
    for(auto it=path.begin();it!=path.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;

#else
    for(auto it=numbers.begin();it!=numbers.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
    cout<<"接近一半的数目是："<<(dp[numbers.size()-1][half_of_sum])<<endl;
#endif
}
size_t max(size_t a,size_t b){
    return (a>b)?a:b;
}
