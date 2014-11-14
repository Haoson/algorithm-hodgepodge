/*************************************************************************
  > File Name: barcode.cpp
  > Author:Haoson 
  > Created Time: Fri 14 Nov 2014 05:57:22 AM PST
  > Description:Codeforces 225C-Barcode(http://codeforces.com/problemset/problem/225/C)
 ************************************************************************/
/**
 *思路：DP,先预处理出从第一列到i列的白点与黑点的数量。设dp[i][j]为前i列的以第i列结尾的颜色为j的合法状态下的最小更改数量
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;

#define DEBUG

struct Node{
    int white,black;//黑白颜色的数目
    Node():white(0),black(0){}
};
static vector<int> dp[2];
static vector<Node>barcode;

void processInput();
void processOutput();

int main(int argc,char*argv[]){
    processInput();

    processOutput();
    return 0;
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/barcode_input.txt","r",stdin);
    size_t n,m,x,y;
    string str;
    if(cin>>n>>m>>x>>y){
        barcode.assign(m,Node());
        for(size_t row=0;row!=n;++row){
            cin>>str;
            for(size_t col=0;col!=m;++col){
                if(str[col]=='#')
                    ++(barcode[col].black);
                else if(str[col]=='.')
                    ++(barcode[col].white);
            }
            for(auto it=barcode.begin();it!=barcode.end();++it)
                cout<<"time="<<row<<"  white:"<<((*it).white)<<" black:"<<((*it).white)<<endl;
            str.clear();
        }
    }
}

void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/barcode_output.txt","w",stdout);
#else
    for(auto it=barcode.begin();it!=barcode.end();++it)
        cout<<"white:"<<((*it).white)<<"black:"<<((*it).white)<<endl;
#endif
}
