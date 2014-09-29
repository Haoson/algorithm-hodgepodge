/*************************************************************************
  > File Name: doubly_linked_list_test_case.cpp
  > Author:Haoson 
  > Created Time: Fri 26 Sep 2014 04:46:37 PM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
#include <iostream>
#include "doubly_linked_list.h"
#include "function_object.h"

void testDListSort(){
    DList<int> d_list;
    if(d_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test sort:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        d_list.output();
        d_list.sort();
        d_list.output();
        d_list.sort(hds::Greater<int>());
        d_list.output();
        cout<<"***********************"<<endl;
    }
}

void testDListResize(){
    DList<int> d_list,d_list2;
    if(d_list.create()&&d_list2.create()){
        cout<<"***********************"<<endl;
        cout<<"Test resize:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        d_list.output();
        d_list.resize(2);
        d_list.output();
        d_list.resize(5,4);
        d_list.output();
        cout<<"***********************"<<endl;
    }
}


void testDListMerge(){
    DList<int> d_list,d_list2;
    if(d_list.create()&&d_list2.create()){
        cout<<"***********************"<<endl;
        cout<<"Test merge:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,4);
        d_list.insert(it,7);
        d_list.insert(it,9);
        DList<int>::iterator it2 = d_list2.begin();
        d_list2.insert(it2,1);
        d_list2.insert(it2,5);
        d_list2.insert(it2,8);
        d_list2.insert(it2,10);
        d_list.output();
        d_list2.output();
        /*d_list.sort();*/
        /*d_list2.sort();*/
        d_list.sort(hds::Greater<int>());
        d_list2.sort(hds::Greater<int>());
        d_list.output();
        d_list2.output();
        d_list.merge(d_list2,hds::Greater<int>());
        d_list.output();
        d_list2.output();

        cout<<"***********************"<<endl;
    }
}

void testIterator(){
    DList<int> d_list;
    if(d_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test iterator:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        d_list.output();
        (----(++++it))++;
        DList<int>::iterator it2 = d_list.end();
        if(it==it2)
            cout<<"iterator 1 == iterator 2 ,true"<<std::endl;
        it2--;
        if(it!=it2)
            cout<<"iterator 1 != iterator 2 ,true"<<std::endl;
        cout<<"begin's data=";
        cout<<*(d_list.begin())<<endl;
        cout<<"second element's data=";
        cout<<*(++(d_list.begin()))<<endl;
        cout<<"end element's data=";
        cout<<*(++++(d_list.begin()))<<endl;
        cout<<"***********************"<<endl;
    }
}

void testDListInsert(){
    DList<int> d_list;
    if(d_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test insert method:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(d_list.begin(),2);
        d_list.insert(it,5);
        d_list.insert(d_list.begin(),3);
        d_list.insert(d_list.end(),4);
        d_list.output();
        it++;
        d_list.insert(it,6);
        d_list.output();
        ++(--------it);
        it = d_list.insert(it,7);
        it = d_list.insert(it,8);
        it = d_list.insert(it,9);
        d_list.output();
        cout<<"***********************"<<endl;
    }
}

void testDListremove1(){
    DList<int> d_list;
    if(d_list.create()){
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        cout<<"***********************"<<endl;
        cout<<"Test remove method:"<<endl;
        cout<<"before remove:"<<endl;
        d_list.output();
        int data = -1;
        cout<<"after remove some data not exists,";
        d_list.remove(data);
        d_list.output();
        cout<<"after remove begin element,";
        it = d_list.remove(2);
        d_list.output();
        cout<<"The element following the begin element is,";
        cout<<*(it)<<endl;
        cout<<"after remove end element,";
        it = d_list.remove(1);
        d_list.output();
        cout<<"Following the end element is tail:";
        cout<<(d_list.end()==it?"true!":"false!")<<endl;
        cout<<"insert some elements,";
        d_list.insert(d_list.begin(),5);
        d_list.insert(d_list.end(),4);
        d_list.output();
        cout<<"after remove some data in the middle,";
        it = d_list.remove(3);
        d_list.output();
        cout<<"The element following the element is,";
        cout<<*(it)<<endl;
        cout<<"***********************"<<endl;
    }
}

void testDListremove2(){
    DList<int> d_list;
    if(d_list.create()){
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        cout<<"***********************"<<endl;
        cout<<"Test remove  method(designated position):"<<endl;
        cout<<"before remove:"<<endl;
        d_list.output();
        int data = -1;
        cout<<"after remove begin element,data=";
        it = d_list.remove((d_list.begin()) ,data);
        cout<<data<<endl;
        cout<<"The following data=";
        cout<<*(it)<<endl;
        d_list.output();
        cout<<"after remove end element,data=";
        it = d_list.remove(++(d_list.begin()),data);
        cout<<"The following iterator is tail,";
        cout<<(it==d_list.end()?"true!":"false!")<<endl;
        d_list.output();
        d_list.insert(it,5);
        d_list.insert(it,4);
        cout<<"insert some data:"<<endl;
        d_list.output();
        cout<<"after remove some data in the middle,the data=";
        it = d_list.remove(++(d_list.begin()),data);
        cout<<data<<endl;
        cout<<"The following data=";
        cout<<*(it)<<endl;
        d_list.output();
        cout<<"***********************"<<endl;
    }
}

void testDListFind(){
    DList<int> d_list;
    if(d_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test find  method:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        d_list.output();
        cout<<"find some data not exists,";
        int data = -1;
        DList<int>::iterator it_ne = d_list.find(data);
        cout<<((it_ne==d_list.end())?"Not found,at the end!":"Not at the end!")<<"The data=";
        cout<<data<<endl;
        cout<<"find begin element,";
        data = 2;
        it_ne = d_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"find end element,";
        data = 1;
        it_ne = d_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"find some data in the middle,";
        data = 3;
        it_ne = d_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"***********************"<<endl;
    }
}


void testDListCopyControl(){
    DList<int> d_list;
    if(d_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test copy constructor:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        cout<<"DList output:";
        d_list.output();
        DList<int> d_list2(d_list);
        cout<<"DList2 output:";
        d_list2.output();
        d_list2.insert(d_list2.begin(),4);
        cout<<" after DList2 insert,DList2 output is:";
        d_list2.output();
        cout<<"***********************"<<endl;
        cout<<"Test assignment operator:"<<endl;
        d_list = d_list2;
        cout<<"after DList=DList2,DList output is:";
        d_list.output();
        cout<<"***********************"<<endl;
    }
}


void testDListOtherMethod(){
    DList<int> d_list;
    if(d_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test makeEmpty method:"<<endl;
        DList<int>::iterator it = d_list.begin();
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        d_list.output();
        d_list.clear();
        d_list.output();
        cout<<"***********************"<<endl;
        cout<<"***********************"<<endl;
        d_list.insert(it,1);
        d_list.insert(it,2);
        d_list.insert(it,3);
        bool is_empty = d_list.isEmpty();
        cout<<"The DList is empty=";
        cout<<((is_empty==true)?"true":"false")<<endl;
        d_list.clear();
        is_empty = d_list.isEmpty();
        cout<<"The DList is empty=";
        cout<<((is_empty==true)?"true":"false")<<endl;
        cout<<"***********************"<<endl;
    }
}

int main(int argc, char *argv[]){
    testDListInsert();
    testIterator();
    testDListremove1();
    testDListremove2();
    testDListFind();
    testDListSort();
    testDListMerge();
    testDListResize();
    testDListOtherMethod();
    testDListCopyControl();
    return 0;
}
