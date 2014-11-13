/*************************************************************************
  > File Name: priority_queue_test_case.cpp
  > Author:Haoson 
  > Created Time: Mon 29 Sep 2014 10:35:40 AM PDT
  > Description: 
 ************************************************************************/

#include<iostream>
using namespace std;
#include "priority_queue.h"
#include "deque.h"

void testPriorityQueueMakeHeap(){
    cout<<"************************"<<endl; 
    Deque<int> deque;
    deque.push_back(90);
    deque.push_back(120);
    deque.push_back(10);
    deque.push_back(15);
    deque.push_back(25);
    deque.push_back(1);
    deque.push_back(75);
    deque.push_back(92);
    deque.push_back(200);
    deque.push_back(23);
    deque.push_back(9);
    cout<<"********原始数据********"<<endl; 
    deque.output();
    PriorityQueue<int> pq(deque.begin(),deque.end());
    cout<<"*****构建够的最小堆*****"<<endl; 
    pq.output();
    cout<<"************************"<<endl; 
}

void testPriorityQueuePush(){
    cout<<"************************"<<endl; 
    PriorityQueue<int> pq;
    pq.push(90);
    pq.push(120);
    pq.push(10);
    pq.push(15);
    pq.push(25);
    pq.push(1);
    pq.push(75);
    pq.push(92);
    pq.push(200);
    pq.push(23);
    pq.push(9);
    pq.output();
    cout<<"首元素="<<pq.top()<<endl;
    pq.pop();
    pq.output();
    cout<<"首元素="<<pq.top()<<endl;
    pq.pop();
    pq.output();
    cout<<"************************"<<endl; 
}

int main(int argc,char*argv[]){
    testPriorityQueueMakeHeap();
    testPriorityQueuePush();
    return 0;
}
