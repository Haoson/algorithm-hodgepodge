/*************************************************************************
  > File Name: snake.cpp
  > Author:Haoson 
  > Created Time: Sat 22 Nov MAX_NUM14 03:52:51 AM PST
  > Description:Codeforces 225D Snake(http://codeforces.com/problemset/problem/225/D) 
 ************************************************************************/
/*
 *思路：BFS+状态压缩(利用位运算，蛇身最大8，共16bit即可记录这一节相对于上一节的方向,0123分别表示上下右左。) 
 **/

#include<iostream>
#include<cstdio>
#include<queue>
#include<string>
#include<vector>
using namespace std;
#define DEBUG

typedef pair<size_t,size_t> pp;
const int MAX_NUM = 20;
static int dx[4]={1,-1,0,0};//方向辅助数组
static int dy[4]={0,0,-1,1};//方向辅助数组
static vector<string> field;//记录棋盘
static size_t row,col;//行、列
static pp apple_pos;//目标（苹果）所在坐标
static size_t snake_length = 0;
struct Snake{
    pp s_head;//蛇头位置
    int body;
    int step;//到这个位置的时候走过的步数
    Snake():s_head(0,0),body(0),step(0){}
    bool canGo(pair<int,int> d_pos){
        int x = d_pos.first+static_cast<int>(s_head.first);
        int y = d_pos.second+static_cast<int>(s_head.second);
        char c = field[static_cast<size_t>(x)][static_cast<size_t>(y)];
        if(x<0||x>=static_cast<int>(row)||y<0||y>=static_cast<int>(col))return false;
        if(c=='#')return false;
        if(c=='@')return true;
        if(c>'0'&&c<='9'&&static_cast<size_t>(c-'0')==snake_length&&snake_length!=2)return true;
        return false;     
    }
    void go(pair<int,int> d_pos,int position){
        size_t x = static_cast<size_t>(d_pos.first+static_cast<int>(s_head.first));
        size_t y = static_cast<size_t>(d_pos.second+static_cast<int>(s_head.second));
        ++step;
        s_head.first = x;
        s_head.second = y;
        body=(body>>2)|(position);
    }
    bool getApple(){
        return s_head==apple_pos;    
    }
};
static Snake snake;

void processInput();
void processOutput();
void bfs();

int main(int argc,char*argv[]){
    processInput();
    bfs();
    processOutput();
    return 0;
}
void bfs(){
    queue<Snake> sq;
    sq.push(snake);
    Snake snake_temp;
    while(!sq.empty()){
        snake = sq.front();
        sq.pop();
        if(snake.getApple()){
            return; 
        }
        for(size_t j=0;j!=4;++j){
            if(snake.canGo(pair<int,int>(dx[j],dy[j]))){
                Snake s = snake;
                s.go(pair<int,int>(dx[j],dy[j]),j);
                sq.push(s);
            }
        }
    }
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/snake_input.txt","r",stdin);
    vector<pair<int,int> > snake_temp(9,pp(0,0));
    size_t int_temp;
    if(cin>>row>>col){
        string temp;
        for(size_t i=0;i!=row;++i){
            cin>>temp;
            field.push_back(temp);    
        }    
        for(size_t i=0;i!=row;i++){
            for(size_t j=0;j!=col;j++){
                if(field[i][j]=='@'){
                    apple_pos.first = i;
                    apple_pos.second = j;
                }else if(field[i][j]>='1'&&field[i][j]<='9'){
                    int_temp = static_cast<size_t>(field[i][j]-'0');
                    if(int_temp>snake_length)
                        snake_length = int_temp;
                    snake_temp[int_temp].first = static_cast<int>(i);
                    snake_temp[int_temp].second = static_cast<int>(j);
                    if(field[i][j]=='1'){
                        snake.s_head.first = i;
                        snake.s_head.second = j;
                    }
                }
            }
        }
        for(size_t i=2;i!=snake_length+1;++i){//将蛇身体处理成bit
            for(size_t j=0;j!=4;++j){
                if((snake_temp[i].first+dx[j]==snake_temp[i-1].first)&&(snake_temp[i].second+dy[j]==snake_temp[i-1].second)){
                    snake.body|=(j<<(2*(i-2)));////第i位标号左移(i-2)*2位跟body做与操作,表示第i位相对第i-1位置的相对位置，0123分别表示上下右左
                    break;
                }    
            } 
        }
    }
}
void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/snake_output.txt","w",stdout);
#else
    cout<<snake.s_head.first<<" "<<snake.s_head.second<<" "<<snake.body<<endl;
#endif
}
