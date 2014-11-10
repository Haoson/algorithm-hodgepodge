/*************************************************************************
  > File Name: rectangular_cut.cpp
  > Author:Haoson 
  > Created Time: Sun 09 Nov 2014 08:30:39 PM PST
  > Description:给定矩形和切分数，并给出每一个切分方案的坐标(x1,y1,x2,y2),输出切分后的所有的矩形的面积（一次切分只会分割一个最小矩形） 
 ************************************************************************/
/**
 *思路：递归求解，深度优先搜索切分，找出切分后的每一个最小的矩形
 **/
#include<iostream>
#include<vector>
#include<stack>
#include<cstdio>
using namespace std;

struct Cut{
    //两个点确定一个矩形
    int x1,y1,x2,y2;
    //判断给定的切分是否在这个矩形内
    bool in(int xa,int ya,int xb,int yb){
        bool is_success = true;
        int d1 = (xa-x1)*(xb-x2);
        int d2 = (ya-y1)*(yb-y2);
        if(d1>0||d2>0||(d1==0&&d2==0)){//点落上顶点上或者点在矩形外
            is_success = false; 
        }
        return is_success;
    }
};
static vector<int> cut_flag;//标记一个切分是否已经被处理过
static vector<Cut> cut_v;//记录所有的切分
static stack<int> area;//输出结果栈，结果要求先分割的矩形面积先输出
static Cut rectangular;//初始的矩形，属于一种特殊的Cut,也是由四个点决定
static int cut_num;//输入的切分数

void processInput();
//深度优先处理切分
void dfsCut(int x1,int y1,int x2,int y2,size_t num);
void processOutput();

int main(int argc,char*argv[]){
    processInput();
    dfsCut(rectangular.x1,rectangular.y1,rectangular.x2,rectangular.y2,static_cast<size_t>(cut_num));
    processOutput();
    return 0;
}

void dfsCut(int x1,int y1,int x2,int y2,size_t num){
    bool is_min_rec = true;
    //对于每一个矩形，把全部的切分都验证一遍
    for(size_t i=0;i != num;++i){
        if(cut_flag[i])
            continue;
        if(cut_v[i].in(x1,y1,x2,y2)){
            cut_flag[i] = 1;
            if(cut_v[i].x1==cut_v[i].x2){ //处理竖切分
                dfsCut(cut_v[i].x1,y1,x2,y2,num);
                dfsCut(x1,y1,cut_v[i].x1,y2,num);
            }
            if(cut_v[i].y1==cut_v[i].y2){//处理横切分
                dfsCut(x1,cut_v[i].y1,x2,y2,num);
                dfsCut(x1,y1,x2,cut_v[i].y2,num);
            }
            is_min_rec = false;
        }
    }    
    //只记录未被继续切分矩形的面积
    if(is_min_rec)
        area.push((x2-x1)*(y2-y1)); 
}

void processOutput(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/rectangle_cut_output.txt","w",stdout);    
    while(!area.empty()){
        printf("%d ",area.top());
        area.pop();
    }
    printf("\n");
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/rectangle_cut_input.txt","r",stdin);    
    Cut cut_temp;
    rectangular.x1 = rectangular.y1 = 0;
    if(scanf("%d %d %d",&(rectangular.x2),&(rectangular.y2),&cut_num)){
        for(int i=0;i!=cut_num;++i){
            scanf("%d %d %d %d",&(cut_temp.x1),&(cut_temp.y1),&(cut_temp.x2),&(cut_temp.y2));     
            cut_v.push_back(cut_temp);
            cut_flag.push_back(0);
        }
    }
}

