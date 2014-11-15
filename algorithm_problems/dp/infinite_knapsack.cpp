/*************************************************************************
  > File Name: infinite_knapsack.cpp
  > Author:Haoson 
  > Created Time: Fri 14 Nov 2014 10:57:44 PM PST
  > Description:无限背包问题(给定承载量W，给定商品重量weight以及这个商品的value，使得不超重的情况下value最大化) 
 ************************************************************************/
/**
 *思路：dp,F(W) = max{F(W-Wj)+Vj},(Wj<W).可以采用反向递归的方法或者正向两层for循环的方法
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
static vector<size_t> dp;

void processInput();
void processOutput(size_t max_value);
size_t knapsackMaxValue(size_t max_w);
size_t max(size_t a,size_t b);

int main(int argc,char*argv[]){
    processInput();
    size_t max_value = knapsackMaxValue(max_weight);
    processOutput(max_value);
}

size_t  knapsackMaxValue(size_t max_w){
    size_t temp;
    for(size_t i=0;i!=items.size();++i){
       for(size_t j=temp=items[i].weight;j<=max_w;++j){
            dp[j] = max(dp[j],dp[j-temp]+items[i].value);    
        } 
    }
    return dp[max_w];
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/knapsack_input.txt","r",stdin);
    size_t n;
    if(cin>>n){
        Item it;
        for(size_t i=0;i!=n;++i){
            cin>>it.id>>it.weight>>it.value;
            items.push_back(it);
        }
        cin>>max_weight;
        dp.assign(max_weight+1,0);
        std::sort(items.begin(),items.end());//按照重量排序，这样可以按照重量从小到大处理dp
    }
}
void processOutput(size_t max_value){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/infinite_knapsack.txt","w",stdout);
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
