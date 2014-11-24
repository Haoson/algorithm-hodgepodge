/*************************************************************************
  > File Name: snake.cpp
  > Author:Haoson 
  > Created Time: Sat 22 Nov MAX_NUM14 03:52:51 AM PST
  > Description:Codeforces 225D Snake(http://codeforces.com/problemset/problem/225/D) 
 ************************************************************************/
//还有bug没解决
/*
 *思路：BFS+状态压缩(利用位运算，蛇身最大8，共16bit即可记录这一节相对于上一节的方向,0123分别表示上下右左。) 
 **/

#include<iostream>
#include<cstdio>
#include<queue>
#include<string>
#include<vector>
#include<set>
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
struct SnakeState{
    pp s_head;
    int body;
    SnakeState(pp h,int b):s_head(h),body(b){}
    SnakeState(){}
    friend bool operator<(const SnakeState& a,const SnakeState& b){
        return (a.s_head<b.s_head&&a.body<b.body);
    }
};
struct Snake{
    pp s_head;//蛇头位置
    int body;
    int step;//到这个位置的时候走过的步数
    Snake():s_head(0,0),body(0),step(0){}
    bool canGo(int new_x,int new_y){
        char c = field[static_cast<size_t>(new_x)][static_cast<size_t>(new_y)];
        if(new_x<0||new_x>=static_cast<int>(row)||new_y<0||new_y>=static_cast<int>(col))return false;
        if(c=='#')return false;
        if(c=='@'||c=='.')return true;
        if(c>'0'&&c<='9'&&static_cast<size_t>(c-'0')==snake_length&&snake_length!=2)return true;
        return false;     
    }
    void go(int new_x,int new_y,int position){
        ++step;
        s_head.first = static_cast<size_t>(new_x);
        s_head.second = static_cast<size_t>(new_y);
        body=((body<<2)&((1<<(2*(snake_length-1)))-1))|(position);//去除最后一节蛇身体，再添加新位置下的的第一节身体的bit
    }
    bool getApple(){
        return s_head==apple_pos;    
    }
};
static set<SnakeState> snake_states;//保存蛇走过的状态，判断是否在绕圈
static Snake snake;

void processInput();
void processOutput();
bool bfs();
SnakeState getNewState(int new_x,int new_y,int new_pos,int old_body);

int main(int argc,char*argv[]){
    processInput();
    bfs();
    processOutput();
    return 0;
}
bool bfs(){
    queue<Snake> sq;
    sq.push(snake);
    Snake snake_temp=snake;
    snake_states.insert(SnakeState(snake.s_head,snake.body));
    int new_x,new_y;
    while(!sq.empty()){
        snake = sq.front();
        sq.pop();
        if(snake.getApple()){
            return true; 
        }
        for(size_t j=0;j!=4;++j){
            new_x = dx[j]+static_cast<int>(snake.s_head.first);
            new_y = dy[j]+static_cast<int>(snake.s_head.second);
            if(snake.canGo(new_x,new_y)&&snake_states.insert(getNewState(new_x,new_y,static_cast<int>(j),snake.body)).second){
                Snake s = snake;
                s.go(new_x,new_y,static_cast<int>(j));
                sq.push(s);
                snake_temp = s;
            }
        }
    }
    return false;
}
SnakeState getNewState(int new_x,int new_y,int new_pos,int old_body){
    SnakeState s;
    s.s_head.first = static_cast<size_t>(new_x);
    s.s_head.second = static_cast<size_t>(new_y);
    s.body=((old_body<<2)&((1<<(2*(snake_length-1)))-1))|(new_pos);
    return s;
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
    cout<<snake.s_head.first<<" "<<snake.s_head.second<<" "<<snake.body<<";step="<<snake.step<<endl;
#endif
}
