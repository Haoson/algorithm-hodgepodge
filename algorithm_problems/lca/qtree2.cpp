/*************************************************************************
  > File Name: qtree2.cpp
  > Author:Haoson 
  > Created Time: Sun 16 Nov 2014 03:43:10 AM PST
  > Description:Spoj913 QTree2(http://www.spoj.com/problems/QTREE2/) 
 ************************************************************************/
/**
 *思路：倍增算法求LCA
 **/
#include<iostream>
#include <vector>
#include <string>
#include<cstdio>
using namespace std;
//#define DEBUG

typedef pair<int,int> pp;
const int MAX_LOG  =14;//2^14>10000
static shared_ptr<vector<int> > parent_ptr; //每个节点倍增到根节点的数组的数组的指针
static shared_ptr<vector<pp > > adj_table_ptr; //树的邻接表表示
static vector<int> depth;                         //节点到根节点的深度
static vector<int> weight;                        //节点到根节点的权重
static int root;                                  //根节点
static int dist_node[2];                          //问题一的数据：求距离的两个节点
static int kth[3];                                //问题二的数据：求第K个节点的三个数据
static size_t node_num;                           //便于计数作用的变量，比实际的节点数大一

void processInput();
void processOutput(int dists,int kth_node);
void dfs(int child_node,int father_node,int depth_to_root,int w_t_f);//使用深度优先的方法求出所有节点到根节点的深度和权重
void preprocessParent();//预处理倍增数组
int lca(int node1,int node2);//求出两个节点之间的最小公共父节点
int distBetweenNodes(int node1,int node2);//求出两个节点之间的权重和
int findKthParent(int node1,int k);//找出node1的第k个祖先节点
int kthNode(int node1,int node2,int k);//找到两个节点之间的第k个节点

int main(int argc,char* argv[]){ 
    processInput();
    dfs(root,-1,0,0);
    preprocessParent();
    int res_dists = distBetweenNodes(dist_node[0],dist_node[1]);
    int res_kth_node =kthNode(kth[0],kth[1],kth[2]);
    processOutput(res_dists,res_kth_node);
    return 0;
}

void dfs(int child_node,int father_node,int depth_to_root,int w_t_f){
    depth[static_cast<size_t>(child_node)] = depth_to_root;
    weight[static_cast<size_t>(child_node)] = w_t_f;
    parent_ptr.get()[static_cast<size_t>(child_node)][0] = father_node;
    for(size_t i=0;i!=adj_table_ptr.get()[child_node].size();++i){
        if(adj_table_ptr.get()[child_node][i].first!=father_node){
            dfs(adj_table_ptr.get()[child_node][i].first,child_node,depth_to_root+1,adj_table_ptr.get()[child_node][i].second+w_t_f);
        } 
    }
}

void preprocessParent(){
    for(size_t j=1;j!=node_num;++j){ //节点从1开始
        for(size_t i = 0;i!=MAX_LOG-1;++i){
            if(parent_ptr.get()[j][i]<0)
                parent_ptr.get()[j][i+1]  = -1;
            else
                parent_ptr.get()[j][i+1] = parent_ptr.get()[static_cast<size_t>(parent_ptr.get()[j][i]) ][i];
        }
    } 
}
void processOutput(int dists,int kth_node){
#ifndef DEBUG
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/output/qtree2_output.txt","w",stdout);
    cout<<dists<<endl;
    cout<<kth_node<<endl;
#else
    cout<<"DIST 4 6="<<dists<<";   KTH 4 6 4 node="<<kth_node<<endl;
#endif
}
void processInput(){
    freopen("/home/haoson/workspace/github-project/algorithm-hodgepodge/algorithm_problems/input/qtree2_input.txt","r",stdin);
    size_t n;
    int child_node,father_node,dist;
    string temp;
    if(cin>>n){
        node_num = n+1;
        adj_table_ptr = shared_ptr<vector<pp > >(new vector<pp >[node_num],[](vector<pp >* p ){delete[]p;});
        for(size_t i=0;i!=n-1;++i){
            cin>>father_node>>child_node>>dist;
            adj_table_ptr.get()[father_node].push_back(pp(child_node,dist)); 
            adj_table_ptr.get()[child_node].push_back(pp(father_node,dist)); 
            if(0==i)root = father_node; //选取第一行的第一个数字作为根节点（可以随机选择）
        }
        cin>>temp>>(dist_node[0])>>(dist_node[1]);
        cin>>temp>>(kth[0])>>(kth[1])>>(kth[2]);

        parent_ptr = shared_ptr<vector<int> >(new vector<int>[node_num],[](vector<int> *p){delete[]p;});
        for(size_t i=0;i!=node_num;++i)
            parent_ptr.get()[i].assign(MAX_LOG,-1);
        depth.assign(static_cast<size_t>(node_num),-1);
        weight.assign(static_cast<size_t>(node_num),0);
    }
}

int lca(int node1,int node2){
    int d1 = depth[static_cast<size_t>(node1)];
    int d2 = depth[static_cast<size_t>(node2)];
    if(d1<d2){
        int temp = node1;
        node1 = node2;
        node2 = temp;
    }
    int dis = depth[static_cast<size_t>(node1)]-depth[static_cast<size_t>(node2)];
    for(size_t k=0;k !=MAX_LOG;++k){
        if((dis>>k)&1){
            node1 = parent_ptr.get()[node1][k]; 
        }
    }
    if(node1==node2)
        return node1;
    for(int k = MAX_LOG-1;k>=0;--k){
        if(parent_ptr.get()[node1][static_cast<size_t>(k)]!=parent_ptr.get()[node2][static_cast<size_t>(k)]){
            node1 = parent_ptr.get()[node1][static_cast<size_t>(k)];
            node2 = parent_ptr.get()[node2][static_cast<size_t>(k)];
        }
    }
    return parent_ptr.get()[node1][0];
}
int distBetweenNodes(int node1,int node2){
    int dis;
    int p = lca(node1,node2);
    int w1 =  weight[static_cast<size_t>(node1)];
    int w2 = weight[static_cast<size_t>(node2)];
    if(node1==p||node2==p){
        dis = (w1>w2)?(w1-w2):(w2-w1); 
    }else{
        dis = w1+w2-2*weight[static_cast<size_t>(p)]; 
    }
    return dis;
}
int findKthParent(int node1,int k){
    for(size_t i =0;i!=MAX_LOG;++i){
        if((k>>i)&1){
            node1 = parent_ptr.get()[node1][i];
        }
    } 
    return node1;
}
int kthNode(int node1,int node2,int k){
    int node;
    int p = lca(node1,node2);
    int d = depth[static_cast<size_t>(node1)]-depth[static_cast<size_t>(p)];
    int d2 = depth[static_cast<size_t>(node2)]-depth[static_cast<size_t>(p)];
    if((d+1)>=k){
        node = findKthParent(node1,k-1); 
    }else{
        node = findKthParent(node2,d2-(k-d-1));
    }
    return node;
}
