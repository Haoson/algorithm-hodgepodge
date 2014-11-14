/*************************************************************************
  > File Name: fibonacci.cpp
  > Author:Haoson 
  > Created Time: Thu 13 Nov 2014 08:33:37 PM PST
  > Description:fibonacci数列求值问题 
 ************************************************************************/
/**
 *思路：具有重叠子问题，使用记忆化搜索（空间换时间）
 **/
#include<iostream>
#include<vector>
using namespace std;

typedef long long LL;
static vector<LL> fib_v;
LL fib(size_t n);

int main(int argc,char*argv[]){
    fib_v.push_back(0);
    fib_v.push_back(1);
    for(size_t i=1;i!=30;++i){
        cout<<"fib("<<i<<")="<<fib(i)<<endl;
    }
    return 0;
}
LL fib(size_t  n){
    if(n>(fib_v.size()-1))
        fib_v.push_back(fib(n-1)+fib(n-2));
    return fib_v[n];
}
