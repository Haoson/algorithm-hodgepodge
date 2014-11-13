/*************************************************************************
  > File Name: deque_test_case.cpp
  > Author:Haoson 
  > Created Time: Sat 27 Sep 2014 11:12:13 PM PDT
  > Description: 
 ************************************************************************/

#include<iostream>
using namespace std;
#include "deque.h"

void testIterator(){
    Deque<int> deque;
    cout<<"***********************"<<endl;
    cout<<"Test iterator:"<<endl;
        Deque<int>::iterator it = deque.begin();
        it = deque.insert(it,1);
        it = deque.insert(deque.end(),2);
        it = deque.insert(it,3);
        deque.output();
        cout<<(*(deque.begin()))<<" "<<(*(++(deque.begin())))<<" "<<(*(--(deque.end())))<<" "<<*(it++)<<" "<<*(it--)<<" "<<*(it)<<endl;
        it = deque.begin();
        it += 2;
        cout<<*it<<" ";
        it -= 1;
        cout<<*it<<" "<<endl;
        Deque<int>::iterator it_temp = deque.end();
        cout<<*(1+it)<<" "<<*(it+1)<<" "<<*(it-1)<<endl;
        cout<<(it_temp-it)<<" "<<(it_temp-deque.begin())<<endl;
        cout<<"it_temp > it,"<<(it_temp>it?"true!":"false!")<<endl;
        cout<<"it_temp >= it,"<<(it_temp>=it?"true!":"false!")<<endl;
        cout<<"it < it_temp,"<<(it<it_temp?"true!":"false!")<<endl;
        cout<<"it <= it_temp,"<<(it<=it_temp?"true!":"false!")<<endl;
        cout<<"***********************"<<endl;
}

void testDequeInsert(){
    Deque<int> deque;
    cout<<"***********************"<<endl;
    cout<<"Test push_front method:"<<endl;
    deque.push_front(1);
    deque.push_front(2);
    deque.push_front(4);
    deque.push_front(3);
    deque.output();
    cout<<"Test push_back method:"<<endl;
    deque.clear();
    deque.output();
    deque.push_back(9);
    deque.push_back(8);
    deque.push_back(7);
    deque.output();
    cout<<"Test push_back and push_front method:"<<endl;
    deque.clear();
    deque.output();
    deque.push_front(1);
    deque.push_back(8);
    deque.push_front(2);
    deque.push_front(3);
    deque.push_back(9);
    deque.push_back(10);
    deque.output();
    cout<<"Test insert method:"<<endl;
    deque.clear();
    deque.output();
    deque.insert(deque.end(),1);
    deque.insert(deque.end(),2);
    deque.insert(deque.begin(),3);
    deque.insert(++(deque.begin()),4);
    deque.insert(--(deque.end()),5);
    deque.insert(deque.end(),9);
    deque.push_front(6);
    deque.push_back(10);
    deque.insert(++++(deque.begin()),7);
    deque.insert(++++++++++(deque.begin()),8);
    deque.output();
    cout<<"***********************"<<endl;
}

void testDequeErase(){
    Deque<int> deque;
    deque.push_back(3);
    deque.push_back(2);
    deque.push_back(1);
    cout<<"***********************"<<endl;
    cout<<"Test erase method:"<<endl;
    deque.output();
    cout<<"deque length="<<deque.length()<<endl;
    cout<<"after erase begin element,";
    Deque<int>::iterator it = deque.erase((deque.begin()));
    cout<<"The following data=";
    cout<<*(it)<<endl;
    deque.output();
    cout<<"deque length="<<deque.length()<<endl;
    cout<<"after erase end element,";
    it = deque.erase(--(deque.end()));
    cout<<"The following iterator is tail,";
    cout<<(it==deque.end()?"true!":"false!")<<endl;
    deque.output();
    cout<<"deque length="<<deque.length()<<endl;
    deque.push_front(1);
    deque.push_back(4);
    cout<<"insert some data:"<<endl;
    deque.output();
    cout<<"deque length="<<deque.length()<<endl;
    cout<<"after erase some data in the middle,";
    it = deque.erase(++(deque.begin()));
    cout<<"The following data="<<*(it)<<endl;
    deque.output();
    cout<<"deque length="<<deque.length()<<endl;
    cout<<"***********************"<<endl;
}

void testDequeCopyControl(){
    Deque<int> deque;
    cout<<"***********************"<<endl;
    cout<<"Test copy constructor:"<<endl;
    Deque<int>::iterator it = deque.begin();
    deque.insert(it,1);
    deque.insert(it,2);
    deque.insert(it,3);
    cout<<"Deque output:";
    deque.output();
    cout<<"deque length="<<(deque.length())<<endl;
    Deque<int> deque2(deque);
    cout<<"Deque2 output:";
    deque2.output();
    cout<<"deque2 length="<<(deque2.length())<<endl;
    deque2.insert(deque2.begin(),4);
    cout<<" after Deque2 insert,Deque2 output is:";
    deque2.output();
    cout<<"deque2 length="<<(deque2.length())<<endl;
    cout<<"***********************"<<endl;
    cout<<"Test assignment operator:"<<endl;
    deque = deque2;
    cout<<"after Deque=Deque2,Deque output is:";
    deque.output();
    cout<<"deque length="<<(deque.length())<<endl;
    cout<<"***********************"<<endl;
}


void testDequeOtherMethod(){
    Deque<int> deque;
    cout<<"***********************"<<endl;
    cout<<"Test clear、length、isEmpty method:"<<endl;
    deque.push_front(1);
    deque.push_front(2);
    deque.push_front(3);
    deque.output();
    cout<<"deque length="<<(deque.length())<<endl;
    bool is_empty = deque.isEmpty();
    cout<<"The Deque is empty="<<((is_empty==true)?"true":"false")<<endl;
    deque.clear();
    deque.output();
    cout<<"deque length="<<(deque.length())<<endl;
    is_empty = deque.isEmpty();
    cout<<"The Deque is empty="<<((is_empty==true)?"true":"false")<<endl;
    cout<<"***********************"<<endl;
    cout<<"Test front、back、[] method:"<<endl;
    deque.push_front(1);
    deque.push_front(2);
    deque.push_front(3);
    cout<<"front data="<<deque.front()<<";back data="<<deque.back()<<endl;
    cout<<"data[0]="<<deque[0]<<";data[1]="<<deque[1]<<";data[2]="<<deque[2]<<endl;
    cout<<"***********************"<<endl;
}

int main(int argc, char *argv[]){
    testDequeInsert();
    testIterator();
    testDequeErase();
    testDequeOtherMethod();
    testDequeCopyControl();
    return 0;
}
