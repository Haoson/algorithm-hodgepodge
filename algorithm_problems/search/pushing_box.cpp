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
#include<queue>
#include<set>
using namespace std;
#define LL long long
//#define DEBUG 

struct State{
    int person_x,person_y,box_x,box_y,push_num;
    string path;
    State(){}
    State(int p1x,int p1y,int b1x,int b1y,int pn){
        person_x = p1x;
        person_y = p1y;
        box_x  =b1x;
        box_y = b1y;
        push_num = pn;
    }
    friend bool operator <(const State& a,const State& b){
        if(a.push_num!=b.push_num)
            return a.push_num<b.push_num;
        return a.path.size()<b.path.size(); 
    }
};
struct PersonState{
    int x,y;
    string path;
};
//这里使用Hash去重方法替代下面的两个数组记录状态去重方法
//static bool box_pos_visited[MAX_N][MAX_N][4];//箱子整个过程中状态记录数组，第三个参数是表示方向
//static bool p_vivisted[MAX_N][MAX_N];//人每次bfs状态记录数组

const int MAX_N = 22;//迷宫最大的行和列数
const int pos[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};//辅助四个方向
const char push[4] = {'S','N','E','W'};
const char walk[4]  ={'s','n','e','w'};
static int r,c,bx,by,px,py,tx,ty;//迷宫行列r,c;盒子初始位置bx,by;人初始位置px,py;目标初始位置tx,ty
static char maps[MAX_N][MAX_N];//迷宫
static State box_s;//箱子每一步的状态
static PersonState person_s;//人每一步的状态

void processInOut();
void output(int time);
void boxBfs();
bool peopleBfs(int des_x,int des_y,int source_x,int source_y);
LL getHashNum(int x1,int y1,int x2,int y2);

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
    set<LL> hash_set;//去重 
    State box_s_temp;//每次BFS一次四个方向，都要相对于原来的位置作出判断，所谓这里引入一个temp state
    box_s.box_x = bx;
    box_s.box_y  =by;
    box_s.person_x = px;
    box_s.person_y = py;
    box_s.push_num  =0;
    box_s.path = "";
    priority_queue<State> pq; 
    pq.push(box_s);
    hash_set.insert(getHashNum(px,py,bx,by));
    while(!pq.empty()){
        box_s = pq.top();
        pq.pop();
#ifdef DEBUG
        cout<<"盒子："<<(box_s.box_x)<<","<<(box_s.box_y)<<" 人： "<<(box_s.person_x)<<","<<(box_s.person_y)<<" path:"<<(box_s.path)<<endl;
#endif
        if(box_s.box_x==tx&&box_s.box_y==ty)
            return;
        for(int i=0;i!=4;++i){
            int nbx = box_s.box_x+pos[i][0];
            int nby = box_s.box_y+pos[i][1];
            int npx = box_s.box_x-pos[i][0];
            int npy = box_s.box_y-pos[i][1];
            //剪枝
            if(maps[nbx][nby]!='#'&&maps[npx][npy]!='#'&&(hash_set.insert(getHashNum(box_s.box_x,box_s.box_y,nbx,nby))).second){
                if(peopleBfs(npx,npy,box_s.person_x,box_s.person_y)){
                    box_s_temp.person_x = box_s.box_x;
                    box_s_temp.person_y = box_s.box_y;
                    box_s_temp.box_x = nbx;
                    box_s_temp.box_y  =nby;
                    box_s_temp.push_num  += 1;
                    box_s_temp.path = box_s.path+person_s.path+push[i];
                    pq.push(box_s_temp);
                }  
            } 
        }        
    }
    box_s.path = "Impossible.";
}

//人BFS，先到的一定是最短步长的，所以使用一个queue即可
bool peopleBfs(int des_x,int des_y,int source_x,int source_y){
    PersonState person_s_temp;
    set<LL> p_check;
    person_s.x = source_x;
    person_s.y = source_y;
    person_s.path = "";
    queue<PersonState> psq;
    psq.push(person_s);
    p_check.insert(getHashNum(des_x,des_y,source_x,source_y));
    p_check.insert(getHashNum(des_x,des_y,box_s.box_x,box_s.box_y));
    while(!psq.empty()){
        person_s = psq.front();        
        psq.pop();
        if(person_s.x==des_x&&person_s.y==des_y)
            return true;
        for(int i=0;i!=4;++i){
            int nx = person_s.x+pos[i][0];
            int ny = person_s.y+pos[i][1];
            if(maps[nx][ny]!='#'&&p_check.insert(getHashNum(des_x,des_y,nx,ny)).second){
                person_s_temp.x = nx;
                person_s_temp.y = ny;
                person_s_temp.path  = person_s.path + walk[i];
                psq.push(person_s_temp);
            } 
        }
    }
    return false;
}
/**
 *(x1,y1)是人的坐标，(x2,y2)是箱子的坐标
 **/
LL getHashNum(int x1,int y1,int x2,int y2){
    return (x1+23*y1+23*23*x2+23*23*23*y2);
}

void processInOut(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/pushing_box_input.txt","r",stdin); 
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/pushing_box_output.txt","w",stdout); 
#endif
}
void output(int t){
    cout<<"Maze #"<<t<<endl;
    cout<<box_s.path<<endl<<endl;
}
