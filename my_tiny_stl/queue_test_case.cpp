/*************************************************************************
  > File Name: queue_test_case.cpp
  > Author:Haoson 
  > Created Time: Sun 28 Sep 2014 10:39:45 AM PDT
  > Description: 
 ************************************************************************/

#include<iostream>
using namespace std;
#include "queue.h"

int main(int argc, char *argv[]){
    Queue<int> queue;
    cout<<"queue is empty:";
    cout<<(queue.isEmpty()==true?"true!":"false!")<<endl;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.push(6);
    queue.push(7);
    cout<<"queue size=";
    cout<<queue.length()<<endl;
    cout<<"queue is empty:";
    cout<<(queue.isEmpty()==true?"true!":"false!")<<endl;
    int temp = queue.front();
    cout<<"queue front data="<<temp<<"; queue back data="<<queue.back()<<endl;
    queue.pop();
    queue.pop();
    queue.pop();
    queue.pop();
    cout<<" after 4 pop,queue front data="<<queue.front()<<endl;
    queue.front() += queue.back();
    while(!queue.isEmpty()){
        cout<<(queue.front())<<" ";
        queue.pop();
    }
    cout<<endl;
    return 0;
}
