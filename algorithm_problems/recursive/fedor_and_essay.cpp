/*************************************************************************
  > File Name: fedor_and_essay.cpp
  > Author:Haoson 
  > Created Time: Mon 10 Nov 2014 12:54:57 AM PST
  > Description:codeforces 467D -Fedor and Essay (http://codeforces.com/problemset/problem/467/D) 
 ************************************************************************/
/**
 *思路：把每个单词视为一个点，把所有点都根据R(优先)和长度进行双关键字排序，然后每一对同义词就是一条有向边。
 *把单词排序后，遍历单词dfs一遍，对某个单词u，把u的所有后代的r和sz都更新为u的r和sz，最后再更新一遍文章的就ok了。
 **/
#include<iostream>
#include<cstdio>
#include<cctype>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
#define LL long long

//将每一个单词看做图中的一个点
struct Node{
    int id,r_num,sz,head;//每个点的id,字母R的数量，单词长度以及head
   
    friend bool operator <(const Node& a,const Node& b){//每个点双关键字(r_num,sz)排序要使用的谓词函数
        if(a.r_num!=b.r_num)
            return a.r_num<b.r_num;
        return a.sz<b.sz;
    }
};
//每一对近义词都看做图中的一条边
struct Edge{
    int to;//指向的顶点
    int next;
};

static vector<int> essayid_v;//记录文章中各个单词的id
static vector<int> id;//维持一个所有节点原始索引的vector（之后排序已打乱）,维持这个vector主要是为了方便从边或者单词map对应找到节点（因为边中存放的是id）
static vector<bool> is_visited;//标记每个节点是否已经经过dfs处理过
static map<string,int> essay_r_map;//将文章以及近义词中出现的每一个单词都当做一个点，构建点与id(出现顺序)的map 
static vector<Node> nodes_v; //所有单词节点
static vector<Edge> edges_v;//将近义词当做一条边，被替换的单词是边指向的一端
static int essay_words_num;//文章中的单词数
static int  node_num,edge_num;

int getId(string str);//将单词节点存放如节点vector中和单词map中
void addEdge(int from_id,int to_id);//将近义词作为一条边，加入edge vector
void process();//处理树上的每一个节点
void dfs(size_t index,int r_num,int word_sz);//dfs处理每一个替换链上的节点，将每一个替换链上的节点的R数目和size替换为替换链上的最优的节点上R和size
void processInput();
void processOutput();

int  main(int charc,char*argv[]){
    node_num = edge_num = 0;
    processInput();
    process();
    processOutput();
    return 0;
}

void process(){
    //对所有Node进行排序
    std::sort(nodes_v.begin(),nodes_v.end());
    id.assign(static_cast<size_t>(node_num),0);
    is_visited.assign(static_cast<size_t>(node_num),false);
    for(int i=0;i!=node_num;++i){
        id[static_cast<size_t>(nodes_v[static_cast<size_t>(i)].id)] = i; 
    } 

    for(size_t  i=0;i!=static_cast<size_t>(node_num);++i){
        if(!is_visited[i])
            dfs(i,nodes_v[i].r_num,nodes_v[i].sz);
    }
}

void dfs(size_t index,int r_num,int word_sz){
    if(is_visited[index])
        return;
    is_visited[index] = true;
    nodes_v[index].r_num = r_num;
    nodes_v[index].sz = word_sz;
    //将替换链上的所有节点的r_num和sz替换为r_num最小（优先）、sz最小的节点的r_num和sz
    for(int i=nodes_v[index].head;i!=-1;i=edges_v[static_cast<size_t>(i)].next)
        dfs(static_cast<size_t>(id[static_cast<size_t>(edges_v[static_cast<size_t>(i)].to)]),r_num,word_sz);
}

int getId(string str){
    Node node;
    std::transform(str.begin(),str.end(),str.begin(),::tolower);    
    if(essay_r_map.find(str)==essay_r_map.end()){
        node.id = node_num;
        node.sz = 0;
        node.head = -1;
        node.r_num = 0;
        for(size_t i=0;i!=str.size();++i){
            if(str[i]=='r')++(node.r_num);   
            ++(node.sz);
        }
        nodes_v.push_back(node);
        essay_r_map[str] = node_num++;
    }
    return essay_r_map[str]; 
}

void addEdge(int from_id,int to_id){
    Edge edge_temp;
    edge_temp.to = to_id;
    edge_temp.next = nodes_v[static_cast<size_t>(from_id)].head;
    nodes_v[static_cast<size_t>(from_id)].head = edge_num++;
    edges_v.push_back(edge_temp);
}

void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/input/fedor_and_essay_input.txt","r",stdin);
    int num;
    string str,str_second;
    if(cin>>essay_words_num){
        for(int i=0;i!=essay_words_num;++i){
            cin>>str;
            essayid_v.push_back(getId(str));
        }
        cin>>num;
        for(int i=0;i!=num;++i){
            cin>>str>>str_second;
            addEdge(getId(str_second),getId(str));
        }
    }
}

void processOutput(){
    #ifdef DEBUG
    for(vector<int>::iterator it = essayid_v.begin();it!=essayid_v.end();++it)
        cout<<*it<<" ";
    cout<<endl;
    for(vector<Node>::iterator it = nodes_v.begin();it!=nodes_v.end();++it)
        cout<<"id:"<<(*it).id<<"  sz:"<<(*it).sz<<"  r_num:"<<(*it).r_num<<"  head:"<<(*it).head<<endl;
    cout<<endl;
    for(vector<Edge>::iterator it = edges_v.begin();it!=edges_v.end();++it)
        cout<<"to:"<<(*it).to<<"  next:"<<(*it).next<<" "<<endl;
    cout<<endl;
    for(map<string,int>::iterator it = essay_r_map.begin();it!=essay_r_map.end();++it)
        cout<<"word:"<<(*it).first<<"  id:"<<(*it).second<<" "<<endl;
    cout<<endl;
    #else
    freopen("/home/haoson/workspace/github-project/algorithm/algorithm_problems/output/fedor_and_essay_output.txt","w",stdout);
    LL ansr=0,ansz=0;
    for(size_t i=0;i!=static_cast<size_t>(essay_words_num);++i){
        ansr += nodes_v[static_cast<size_t>(id[static_cast<size_t>(essayid_v[i])])].r_num; 
        ansz += nodes_v[static_cast<size_t>(id[static_cast<size_t>(essayid_v[i])])].sz; 
    }    
    cout<<ansr<<" "<<ansz<<endl;
    #endif
}
