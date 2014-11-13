/*************************************************************************
  > File Name: stack_test_case.cpp
  > Author:Haoson 
  > Created Time: Sat 27 Sep 2014 06:11:06 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
#include "stack.h"

int main(int argc, char *argv[]){
    Stack<int> stack;
    cout<<"stack is empty:";
    cout<<(stack.isEmpty()==true?"true!":"false!")<<endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);
    cout<<"stack size=";
    cout<<stack.size()<<endl;
    cout<<"stack is empty:";
    cout<<(stack.isEmpty()==true?"true!":"false!")<<endl;
    int temp = stack.top();
    cout<<"stack top data=";
    cout<<temp<<endl;
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    temp = stack.top();
    cout<<" after 4 pop,stack top data=";
    cout<<temp<<endl;
    while(!stack.isEmpty()){
        cout<<(stack.top())<<" ";
        stack.pop();
    }
    cout<<endl;
    return 0;
}
