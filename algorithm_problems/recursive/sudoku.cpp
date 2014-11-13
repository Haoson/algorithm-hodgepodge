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
#include<set>
#include<algorithm>
using namespace std;
//#define DEBUG

const int BOARD_NUM = 81;//9*9个格子
const int NEIGHBORS = 24;//每个格子的邻居，同行、同列、同一个block的其他数
static int board[BOARD_NUM];//数独
static int neighbors[BOARD_NUM][NEIGHBORS];//每一个格子的邻居,做缓存
static int space_num;//初始空格数目
static int dynamic_space_num;//动态变化的空格数目
static int spaces[BOARD_NUM];//内容为空格下标
static int arities[BOARD_NUM];//格子的“自由度”，arities[x]表示x这个格子目前的候选数字的个数，选待填格子时应选arity最小的格子
static bool available[BOARD_NUM][10];//格子有哪些数字可用，例如available[3][2]==true说明第3号格子能填入数字2
static set<int> spaces_index_set;//存储初始空格的坐标

void processInput();
void preProcess();//预处理，处理邻居数组，自由度数组，available数组
void processOutput();
bool verify(int index,int number);//验证在index坐标下的空格能否放入数字number
bool backtrackingSudoku(int index);//递归回溯处理数独主函数
int selectMinArities();//选择自由度最小的空格放入数字
void changeAux(int index,int number,bool is_forward);//每次放入一个空格数字的时候重新计算辅助数组，包含available和arities数组

int main(int argc,char *argv[]){
    space_num = 0;
    std::fill(spaces,spaces+BOARD_NUM,-1);
    processInput();
    preProcess();
    backtrackingSudoku(0);
    processOutput();
}

bool backtrackingSudoku(int index){
    if(index==space_num)
        return true;
    int min_arities_index = selectMinArities();
    for(int i=1;i!=10;++i){
        if(available[min_arities_index][i]){
            board[min_arities_index] = i;
#ifdef DEBUG
            cout<<"index="<<min_arities_index<<";value="<<i<<";";
#endif
            changeAux(min_arities_index,i,true);
            if(backtrackingSudoku(++index))
                return true;
            else{
                board[min_arities_index] = 0;
                ++dynamic_space_num;
                changeAux(min_arities_index,i,false); 
            }
        }
    }

    return false;
}


//填充一个空格后，需要动态改变辅助数组arities和avaliable
void changeAux(int i,int number,bool is_forward){
    set<int> processed_index_set;
    //处理同一行的邻居
    for(int j=(i/9 * 9);j!=(i/9 * 9 + 9);++j){
        if(spaces_index_set.find(j)!=spaces_index_set.end()){
            processed_index_set.insert(j);
            if(is_forward&&available[j][number]){
                --arities[j];
                available[j][number] = false;
            }
            if(!is_forward&&verify(j,number)){
                ++arities[j];
                available[j][number] = true;
            }
        }
    }
    //处理同一列的邻居
    for(int j=i%9;j!=(BOARD_NUM+i%9);j+=9){
        if(j!=i&&spaces_index_set.find(j)!=spaces_index_set.end()){
            processed_index_set.insert(j);
            if(is_forward&&available[j][number]){
                --arities[j];
                available[j][number] = false;
            }
            if(!is_forward&&verify(j,number)){
                ++arities[j];
                available[j][number] = true;
            }
        }
    }
    //处理同一个block里面的邻居
    int temp;
    for(int j=0;j!=3;++j){
        for(int k=0;k!=3;++k){
            temp = j*9+k+(i/27*27+(i%9)/3*3);
            if((processed_index_set.insert(temp).second)&&spaces_index_set.find(temp)!=spaces_index_set.end()){
                if(is_forward&&available[j][number]){
                    --arities[j];
                    available[j][number] = false;
                }
                if(!is_forward&&verify(j,number)){
                    ++arities[j];
                    available[j][number] = true;
                }
            }
        }
    }    
}
//返回自由度最小的那个格子的坐标
int selectMinArities(){
    int res  = BOARD_NUM,arities_temp = BOARD_NUM,index = -1;
    for(int i=0;i!=dynamic_space_num;++i){
        if(arities[spaces[i]]<arities_temp){
            arities_temp = arities[spaces[i]];
            res = spaces[i];
            index = i;
        }
    }
    for(int i=index;i!=(dynamic_space_num-1);++i){
        spaces[i] = spaces[i+1];
    } 
    spaces[dynamic_space_num-1] = res;
    --dynamic_space_num;
    return res;
}

//判断number能否放在board[index]位置处
bool verify(int index,int number){
    int i = 0;
    for(;i!=NEIGHBORS/3;++i){
        if(neighbors[index][i]==number||neighbors[index][i+8]==number||neighbors[index][i+16]==number)
            return false;
    }
    return true;
}

void preProcess(){
    int index =0,temp = 0 ;
    for(int i=0;i!=BOARD_NUM;++i){
        std::fill(available[i],available[i]+10,false);
        arities[i] = 0;
        index = 0;
        //处理同一行的邻居
        for(int j=(i/9 * 9);j!=(i/9 * 9 + 9);++j){
            if(j!=i)
                neighbors[i][index++] = board[j];
        }
        //处理同一列的邻居
        for(int j=i%9;j!=(BOARD_NUM+i%9);j+=9){
            if(j!=i)
                neighbors[i][index++] = board[j];
        }
        //处理同一个block里面的邻居
        for(int j=0;j!=3;++j){
            for(int k=0;k!=3;++k){
                temp = j*9+k+(i/27*27+(i%9)/3*3);
                neighbors[i][index++] = board[temp];
            }
        }    
    }
    for(int i=0;i!=space_num;++i){
        for(int j=1;j!=10;++j){
            if(verify(spaces[i],j)){
                available[spaces[i]][j] = true;
                ++arities[spaces[i]];
            }
       }
    }    
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/sudoku_input.txt","r",stdin);    
    string str;
    int index = 0;
    while(cin>>str){
        for(string::iterator it = str.begin();it!=str.end();++it){
            board[index++] = *it-'0';
            if(*it=='0'){
                spaces[space_num++] = index-1;
                spaces_index_set.insert(index-1);
            }
        }
        str.clear();
    }
    dynamic_space_num = space_num;
}

void processOutput(){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/sudoku_output.txt","w",stdout);   
    for(int i=0;i!=BOARD_NUM;++i){
        if(i!=0&&i%9==0)
            cout<<endl;
        cout<<board[i];
    }
    cout<<endl;
#else
/*    cout<<"board data:"<<endl;*/
    //for(int i=0;i!=BOARD_NUM;++i)
        //cout<<board[i]<<" ";
    //cout<<endl;
    //cout<<"space num:"<<space_num<<endl;
    //cout<<"neighbors data:"<<endl;
    //for(int i=0;i!=BOARD_NUM;++i){
        //cout<<"index "<<i<<":";
        //for(int j=0;j!=NEIGHBORS;++j){
            //cout<<neighbors[i][j]<<" "; 
        //}
        //cout<<endl;
    //}
    //cout<<"arities:一共"<<space_num<<"个。"<<endl;
    //for(int i=0;i!=space_num;++i){
        //cout<<spaces[i]<<"自由度："<<arities[spaces[i]]<<endl;
    /*}*/
#endif

}
