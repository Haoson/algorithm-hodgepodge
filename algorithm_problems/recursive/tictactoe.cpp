/*************************************************************************
  > File Name: tictactoe.cpp
  > Author:Haoson 
  > Created Time: Thu 13 Nov 2014 07:59:42 AM PST
  > Description:codeforces-tictactoe (http://codeforces.com/problemset/problem/3/C)
 ************************************************************************/
/**
 *思路：dfs递归回溯获取所有合法的棋局
 **/
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;

//#define DEBUG

const int CHESS_BOARD_NUMBER = 9;//棋盘格子数
static string chessboard;//给定的棋盘
static map<string,string> res;//存储所有合法的棋局情况,map的key是某一种棋局状态，value是这种状态下的verdict
static string grid (9,'.');//递归回溯过程中初始的棋盘

void processInput();
void processOutput();
void dfs(int i);//递归回溯找到所有合法的棋盘状态
bool isWin(const string& board,char c);//当在棋盘放入c的时候，判断是否游戏结束，有一方获胜

int main(int argc,char*argv[]){
    processInput();
    dfs(0);
    processOutput();
    return 0;
}

void dfs(int time){
    if(isWin(grid,'X')){
        res.insert(std::pair<string,string>(grid,"the first player won"));
        return;
    }else if(isWin(grid,'O')){
        res.insert(std::pair<string,string>(grid,"the second player won"));
        return;
    }else if(time==CHESS_BOARD_NUMBER){
        res.insert(std::pair<string,string>(grid,"draw"));
        return;
    }
    if(time%2==0){
        res.insert(std::pair<string,string>(grid,"first"));
    }else{
        res.insert(std::pair<string,string>(grid,"second"));
    }
    for(size_t j=0;j!=CHESS_BOARD_NUMBER;++j){
        if(grid[j]=='.'){
            grid[j] = (time%2==0)?'X':'O';
            dfs(time+1);
            grid[j] = '.';
        }
    }
}

bool isWin(const string& board,char c){
    for(size_t i=0;i!=3;++i){
        if(board[3*i]==c&&board[3*i+1]==c&&board[3*i+2]==c)
            return true;
    }
    for(size_t i=0;i!=3;++i){
        if(board[i]==c&&board[i+3]==c&&board[i+6]==c)
            return true;
    }
    if(board[0]==c&&board[4]==c&&board[8]==c)
        return true;
    if(board[2]==c&&board[4]==c&&board[6]==c)
        return true;
    return false;
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/tictactoe_input.txt","r",stdin);    
    string t;
    for(size_t i=0;i!=3;++i){
        cin>>t; 
        chessboard+=t;
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/tictactoe_output.txt","w",stdout);
    if(res.find(chessboard)==res.end()){
        cout<<"illegal"<<endl;
    }else{
        cout<<res[chessboard]<<endl;
    }
#else
    cout<<"给定的棋盘："<<chessboard<<endl;
    cout<<"chessboard size:"<<(chessboard.size())<<" grid size:"<<grid.size()<<endl;
    cout<<((res.find(chessboard)==res.end())?"not found":"found")<<endl;
#endif
}
