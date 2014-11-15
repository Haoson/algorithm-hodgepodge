/*************************************************************************
  > File Name: one_or_zero_knapsack.cpp
  > Author:Haoson 
  > Created Time: Fri 14 Nov 2014 10:56:38 PM PST
  > Description:0/1 背包问题,题目同无限背包问题 
 ************************************************************************/
/**
 *思路：F(w,j) = max{F(W,j-1), F(W-Wj,j-1)+Vj}.可以采用正向两重循环或者反向递归的方式
 **/
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

//#define DEBUG

struct Item{
    size_t id,weight,value;
    Item():id(0),weight(0),value(0){}
    Item(size_t i,size_t w,size_t v){
        id = i;
        weight = w;
        value = v;
    }
    friend bool operator < (const Item&it1,const Item&it2){
        return it1.weight<it2.weight;
    }
};
static size_t max_weight;//承载量w
static vector<Item> items;

void processInput();
void processOutput(size_t max_value);
size_t knapsackMaxValue(size_t max_w,size_t index);
size_t max(size_t a,size_t b);

int main(int argc,char*argv[]){
    processInput();
    size_t max_value = knapsackMaxValue(max_weight,items.size()-1);
    processOutput(max_value);
}

size_t  knapsackMaxValue(size_t max_w,size_t index){
    if(max_w==0)
        return 0;
    if(index==1)//当只有一件商品的时候，如果负载量大于等于这一个商品，选择它，否则，不选择
        return (items[index].value<=max_w)?(items[index].value):0;
    size_t temp_value = items[index].weight;
    size_t a = knapsackMaxValue(max_w,index-1);
    if(temp_value<=max_w){
        size_t b  =knapsackMaxValue(max_w-temp_value,index-1)+items[index].value;
        return max(a,b);
    }else{
        return a; 
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/knapsack_input.txt","r",stdin);
    size_t n;
    if(cin>>n){
        items.assign(n+1,Item());//第0个不存放数据
        for(size_t i=1;i!=n+1;++i){
            cin>>(items[i]).id>>(items[i]).weight>>(items[i]).value;
        }
        cin>>max_weight;
        std::sort(items.begin(),items.end());//按照重量排序，这样可以按照重量从小到大处理dp
    }
}
void processOutput(size_t max_value){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/one_or_zero_knapsack_output.txt","w",stdout);
    cout<<max_value<<endl;
#else
    for(auto it=items.begin();it!=items.end();++it){
        cout<<"id="<<((*it).id)<<"weight="<<((*it).weight)<<"value="<<((*it).value)<<endl;
    }
    cout<<"max_value="<<max_value<<endl;
#endif
}
size_t max(size_t a,size_t b){
    return (a>b)?a:b;
}
