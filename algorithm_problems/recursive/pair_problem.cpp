/*************************************************************************
  > File Name: pair_problem.cpp
  > Author:Haoson 
  > Created Time: Tue 30 Sep 2014 04:27:14 PM PDT
  > Description:给定一列pair,int列(如pair pair int int int),pair能包含int或pair(如pair<int,int>，pair<pair<int,int>,int>),
  >输出完整的pair包含(如pair<pair<int,int >,int>)，否则报错(例如输入是：pair int,不能组成完整的pair包含) 
 ************************************************************************/
/**
 *思路：递归解决，当处理掉一个完整的最大的pair后，处理结束，若int多了则报错
 **/
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;

static vector<string> v; 

void processInput();
bool processPair(size_t start,string& res);
void processOutput(string res,bool is_success);

int  main(int arc,char *argv[]){
    processInput();
    string pair_res;
    bool is_success = processPair(0,pair_res);
    processOutput(pair_res,is_success);
    return 0;
}

bool processPair(size_t start,string& res){
    bool is_success = true;
    if(start!=v.size()){
        res += v[start];     
        if(v[start]=="pair"){
            res += "<";
            is_success = processPair(++start,res);
            res += ",";
            is_success = processPair(++start,res);
            res += " >";
        }
    }else{
        is_success = false;
    }
    return is_success;
}

void processOutput(string res,bool is_success){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/pair_problem_output.txt","w",stdout);     
    if(is_success)
        cout<<res<<endl;
    else
        cout<<"wrong input!"<<endl;
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/pair_problem_input.txt","r",stdin);    
    string temp;
    while(cin>>temp){
        v.push_back(temp);
    }
}

