/*************************************************************************
  > File Name: pushing_box.cpp
  > Author:Haoson 
  > Created Time: Tue 11 Nov 2014 04:23:57 AM PST
  > Description:POJ 1475 Pushing Boxes(http://poj.org/problem?id=1475) 
 ************************************************************************/
/**
 *思路：两重BFS，第一重是搜索箱子，第二重搜索人能不能到达推箱子的地方;Hash方法记录状态去重
 **/
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

const int MAX_N = 20;//迷宫最大的行和列数
static int r,c,bx,by,px,py,tx,ty;//迷宫行列r,c;盒子初始位置bx,by;人初始位置px,py;目标初始位置tx,ty
static char maps[MAX_N+2][MAX_N+2];//迷宫
static string ans;//结果存放在ans中 

void processInOut();
void output(int time);
void boxBfs();
int peopleBfs();

int main(int argc,char*argv[]){
    processInOut();
    int time = 1;
    while(cin>>r>>c&&(r+c)){
        for(int i=1;i<=r;++i)//maps首行末行、首列末列都留作缓冲,这样就不用判断边界
            cin>>(maps[i]+1);
        for(int i=0;i!=(r+2);++i){
            for(int j=0;j!=(c+2);++j){
                if(0==i||0==j||(r+1)==i||(c+1)==j)
                    maps[i][j] = '#';
                if(maps[i][j]=='B'){
                    bx = i;
                    by = j;
                }
                if(maps[i][j]=='S'){
                    px = i;
                    py = j;
                }
                if(maps[i][j]=='T'){
                    tx = i;
                    ty = j;
                }
            }
        }
        boxBfs();
        output(time++);
    }
    return 0;
}

void boxBfs(){
     
}

int peopleBfs(){
    return 0;
}

void processInOut(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/pushing_box_input.txt","r",stdin); 
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/pushing_box_output.txt","w",stdout); 
}
void output(int t){
    cout<<"Maze #"<<t<<endl;
    cout<<ans<<endl<<endl;
}
