/*************************************************************************
  > File Name: bag_test_case.cpp
  > Author:Haoson 
  > Created Time: Sat 27 Sep 2014 03:58:23 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
#include "bag.h"


int main(int argc, char *argv[]){
    Bag<int> bag;
    cout<<"bag is empty:";
    cout<<(bag.isEmpty()==true?"true!":"false!")<<endl;
    bag.add(1);
    bag.add(3);
    bag.add(2);
    bag.add(5);
    bag.add(4);
    bag.add(6);
    bag.add(7);
    cout<<"bab size=";
    cout<<bag.size()<<endl;
    cout<<"bag is empty:";
    cout<<(bag.isEmpty()==true?"true!":"false!")<<endl;
    for(Bag<int>::iterator it = bag.begin();it!=bag.end();++it)
        cout<<*(it)<<"  ";
    cout<<endl;
    return 0;
}
