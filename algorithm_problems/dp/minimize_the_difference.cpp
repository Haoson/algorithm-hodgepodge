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
using namespace std;

#define DEBUG

static vector<int> numbers;
static vector<vector<int> >dp;

void processInput();
void processOutput();
void minimize();

int main(int argc,char* argv[]){
    processInput();
    minimize();
    processOutput();
}
void minimize(){
    size_t sz =numbers.size()+1; 
    dp.assign(sz,vector<int>(sz,0));

}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/minimize_the_difference_input.txt","r",stdin);
    int i;
    while(cin>>i){
        numbers.push_back(i);    
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/minimize_the_difference_output.txt","w",stdout);
#else
    for(auto it=numbers.begin();it!=numbers.end();++it){
        cout<<(*it)<<" ";
    }
    cout<<endl;
#endif
}
