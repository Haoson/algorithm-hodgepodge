/*************************************************************************
  > File Name: printer.cpp
  > Author:Haoson 
  > Created Time: Tue 30 Sep 2014 06:42:29 AM PDT
  > Description:codeforces 253E -Printer (http://codeforces.com/contest/253/problem/E) 
 ************************************************************************/
/**
 *思路：对优先级进行二分  每次给一个优先级就模拟一下看是否合格 不合格就二分调整，用堆搞
 */

#include<iostream>
using namespace std;
#include<set>
#include<queue>
#include <algorithm>
#define LL long long

struct Task{
    int task_id; 
    LL cur_time;
    LL volume;
    LL priority;
    bool operator < (const Task & t)const{
        return priority < t.priority;
    }
};
//处理输入
void processInput();
//处理输出
void processOutput();
//初始化
void init();
//预处理
void preProcess();
//二分处理
void binarySearch();
//对二分查找过程中的每个优先级都进行处理,返回当前处理的优先级下的结束时间
LL processPriority(LL priority);
//谓词函数,双关键字排序使用
bool cmp(const Task&x,const Task& y){
    if(x.cur_time!=y.cur_time)
        return x.cur_time<y.cur_time;
    return x.priority<y.priority;
}


static int num_tasks;//要打印的任务的个数
static int index_of_negative_task;//priority为-1的task在task_array_ptr数组中的下标
static LL end_time_of_negative_task;//priority为-1的task结束任务的时间
static LL max_priority;//输入数据中最大优先级
static shared_ptr<Task> task_array_ptr;//存储所有task的数组指针
static shared_ptr<LL> ans_ptr; //存储每个task结束任务的时间的数组指针
static set<LL> st; //存放优先级，去重
static priority_queue<Task> qt;//获得某一个时刻内的优先级最大的task采用的数据结构-优先队列

int main(int argc,char*argv[]){
    processInput();
    preProcess();
    binarySearch();
    processOutput();
    return 0;
}
//计算该该优先级下所有task的结束时间
LL processPriority(LL p){
    task_array_ptr.get()[index_of_negative_task].priority = p;
    int task_id = task_array_ptr.get()[index_of_negative_task].task_id;
    int processed_task = 0;
    LL current_time = 0;
    //(处理task是按照某一时刻所有到来的task的优先级从大到小处理)
    while(!qt.empty()||processed_task!=num_tasks){
        //当前面task全部结束（或者开始打印第一份task），打印机空闲而且还有任务未处理的，将任务放入优先队列中，准备处理
        if(processed_task!=num_tasks&&qt.empty()){
            current_time = task_array_ptr.get()[processed_task].cur_time;
            qt.push(task_array_ptr.get()[processed_task++]);
        }
        //将进入时间相同，但是优先级不同的任务放入优先队列中进行处理
        while(processed_task!=num_tasks){
            if(current_time==(task_array_ptr.get()[processed_task].cur_time))
                qt.push(task_array_ptr.get()[processed_task++]);
            else
                break;
        }
        //处理这一时刻优先级最大的task
        Task temp = qt.top();
        qt.pop();
        //将优先级大的task尽可能多的处理掉，如果某一时刻遇到一个优先级比正要处理的task的优先级大的task，那么应该停下来处理优先级大的
        while(processed_task!=num_tasks){
            if((temp.volume>task_array_ptr.get()[processed_task].cur_time-current_time)&&(task_array_ptr.get()[processed_task].priority<temp.priority))
                qt.push(task_array_ptr.get()[processed_task++]);
            else 
                break;
        }
        //当此时处理的task是最后一个task时或者优先级最大的task能在小于或者等于自己优先级的所有task处理时间之和之内处理掉的情况
        if(processed_task==num_tasks||temp.volume<=task_array_ptr.get()[processed_task].cur_time-current_time){
            current_time+=temp.volume;
            temp.volume = 0;
        }else{
            //遇到了比自己优先级大的task，得先处理优先级大的task
            temp.volume -= (task_array_ptr.get()[processed_task].cur_time-current_time);
            current_time = task_array_ptr.get()[processed_task].cur_time;
        }

        if(temp.volume==0)
            ans_ptr.get()[temp.task_id] = current_time;//task完全处理掉时的时间
        else
            qt.push(temp);//遇到优先级更大的task之后自身还没完全处理掉时还得压入优先队列

    }
    return ans_ptr.get()[task_id];
}
void binarySearch(){
    //先找到缺失优先级的那个task的优先级的范围，然后二分查找
    LL l=1,r=max_priority+1,mid;
    while(st.find(l)!=st.end())
        ++l;
    while(st.find(r)!=st.end())
        --r;
    while(l<=r){
        mid = (l+r)>>1;
        while(st.find(mid)!=st.end())
            --mid;
        LL t = processPriority(mid); 
        if(t==end_time_of_negative_task)
            break;
        if(t<end_time_of_negative_task)//该优先级下处理结束时间提前，说明优先级假设大了
            r = mid-1;
        else
            l = mid+1;
        while(st.find(l)!=st.end())
            ++l;
        while(st.find(r)!=st.end())
            --r;
    }
}
void processInput(){
     freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/half_interval/input/printer_input.txt","r",stdin);
    if(scanf("%d",&num_tasks)!=EOF){
        init();
        for(int i=0;i!=num_tasks;++i){
            scanf("%lld %lld %lld",&(task_array_ptr.get()[i].cur_time),&(task_array_ptr.get()[i].volume),&(task_array_ptr.get()[i].priority));
            task_array_ptr.get()[i].task_id = i;
            st.insert(task_array_ptr.get()[i].priority);
            max_priority = (max_priority>(task_array_ptr.get()[i].priority))?max_priority:(task_array_ptr.get()[i].priority);
        }
        scanf("%lld",&end_time_of_negative_task);
      }
}
void processOutput(){
     freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/half_interval/output/printer_output.txt","w",stdout);
    printf("%lld \n",task_array_ptr.get()[index_of_negative_task].priority);
     for(int i=0;i!=num_tasks;++i){
        printf("%lld ",ans_ptr.get()[i]);
     }
     printf("\n");
}
void init(){
    task_array_ptr = shared_ptr<Task>(new Task[num_tasks],[](Task *p){delete []p;});
    ans_ptr = shared_ptr<LL>(new LL[num_tasks],[](LL* p){delete[] p;});
    max_priority=0;
    st.clear();
}
void preProcess(){
    //对所有task做双关键字排序，首先按照时间排序，然后按照优先级排序
    sort(task_array_ptr.get(),task_array_ptr.get()+num_tasks,cmp);
    for(int i=0;i!=num_tasks;++i){
        if(task_array_ptr.get()[i].priority==-1){
            index_of_negative_task = i;
            break;
        }
    }
}
