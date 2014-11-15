/*************************************************************************
  > File Name: barcode.cpp
  > Author:Haoson 
  > Created Time: Fri 14 Nov 2014 05:57:22 AM PST
  > Description:Codeforces 225C-Barcode(http://codeforces.com/problemset/problem/225/C)
 ************************************************************************/
/**
 *思路：DP,先预处理出从第一列到i列的白点与黑点的数量。设dp[i][j]为前i列的以颜色为j的合法状态下的最小更改数量
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;

//#define DEBUG

struct Node{
    size_t white,black;//黑白颜色的数目
    Node():white(0),black(0){}
    Node(size_t w,size_t b){
        white = w;
        black  =b;
    }
};
static vector<size_t> dp[2];//dp数组，第一个记录白色，第二个记录黑色
static vector<Node>barcode;//原始图像
static size_t m,x,y;//给定的图像的列数m、单色最小列数x、单色最大列数y

void processInput();
void processOutput(size_t step);
size_t reverseRecursion(size_t col,size_t color);//反向递归，参数表示第col列以color结尾
size_t min(vector<size_t> nums);

int main(int argc,char*argv[]){
    processInput();
    size_t w_e = reverseRecursion(5,0);//第五列以白颜色结束
    size_t b_e =reverseRecursion(5,1);//第五列以黑颜色结束
    processOutput(w_e<b_e?w_e:b_e);
    return 0;
}
//反向递归求解dp值
size_t reverseRecursion(size_t col,size_t color){
    if(col==0)//列数为0的时候直接返回0
        return 0;
    else if(col==1)//只有一列的时候，直接返回要去除的颜色的数目
        return (color==0?(barcode[col].black):(barcode[col].white));
    vector<size_t> temp;//存储col列与col-{x,y}列的去掉的颜色数值,也就是dp问题中的cost
    size_t total =0;
    for(size_t k=x;k!=y+1;++k){
        for(size_t tt=col-k+1;tt!=col+1;++tt)
            total+=(color==0?(barcode[tt].black):(barcode[tt].white));
        temp.push_back(reverseRecursion(col-k,(color+1)%2)+total); 
        total = 0;
    }
    dp[color][col] = min(temp);//以color颜色结束的前col列的dp值
    return dp[color][col]; 
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/barcode_input.txt","r",stdin);
    size_t n;
    char c;
    if(cin>>n>>m>>x>>y){
        dp[0].assign(m+1,0);
        dp[1].assign(m+1,0);
        barcode.assign(m+1,Node());
        for(size_t row=0;row!=n;++row){
            for(size_t col=1;col!=m+1;++col){
                cin>>c;
                if(c=='.')
                    barcode[col].white++;
                else 
                    barcode[col].black++;
            }
        }
    }
}

void processOutput(size_t step){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/barcode_output.txt","w",stdout);
    cout<<step<<endl;
#else
    for(auto it=barcode.begin();it!=barcode.end();++it)
        cout<<"white:"<<((*it).white)<<"black:"<<((*it).black)<<endl;
    for(int i=0;i!=2;++i){
        cout<<"dp["<<i<<"]:";
        for(auto j=dp[i].begin();j!=dp[i].end();++j){
            cout<<(*j)<<" ";
        }
        cout<<endl;
    }
    cout<<"step:"<<step<<endl;
#endif
}
size_t min(vector<size_t> num_v){
    size_t res = num_v[0];
    for(auto it = num_v.begin();it!=num_v.end();++it){
        if(*it<res)
            res = *it;
    }
    return res;
}
