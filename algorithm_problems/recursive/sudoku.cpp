/*************************************************************************
  > File Name: sudoku.cpp
  > Author:Haoson 
  > Created Time: Wed 12 Nov 2014 01:54:53 AM PST
  > Description:Sudoku-leetcode(https://oj.leetcode.com/problems/sudoku-solver/) 
 ************************************************************************/
/**
 *思路：典型的递归回溯算法解决。改进点：可以找限制最多的单元格填入
 **/
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
#define DEBUG

const int BOARD_NUM = 81;//9*9个格子
static int board[BOARD_NUM];//数独
static int space_num;//空格数目
static int spaces[BOARD_NUM];//内容为空格下标
static int arities[BOARD_NUM];//格子的“自由度”，arities[x]表示x这个格子目前的候选数字的个数，选待填格子时应选arity最小的格子
static bool available[BOARD_NUM][10];//格子有哪些数字可用，例如available[3][2]==true说明第3号格子能填入数字2

void processInput();
void preProcess();
void processOutput();

int main(int argc,char *argv[]){
    space_num = 0;
    processInput();
    preProcess();
    processOutput();
}

void preProcess(){
    
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/sudoku_input.txt","r",stdin);    
    string str;
    int index = 0;
    while(cin>>str){
        for(string::iterator it = str.begin();it!=str.end();++it){
            board[index++] = *it-'0';
            if(*it=='0')
                spaces[space_num++] = index-1;
        }
        str.clear();
    }
}

void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/sudoku_output.txt","w",stdout);   
#else
    for(int i=0;i!=BOARD_NUM;++i)
        cout<<board[i]<<" ";
    cout<<endl;
    cout<<"space num:"<<space_num<<endl;
#endif

}
