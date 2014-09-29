/*************************************************************************
  > File Name: cursor_based_list_test_case.cpp
  > Author:Haoson 
  > Created Time: Thu 25 Sep 2014 02:06:48 PM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
#include<iostream>
#include "cursor_based_list.h"


void testIterator(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test iterator:"<<endl;
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cursor_list.output();
        ++it;
        it++;
        CursorList<int>::iterator it2 = cursor_list.first();
        it2++;
        if(it==it2)
            cout<<"iterator 1 == iterator 2 ,true"<<std::endl;
        it2++;
        if(it!=it2)
            cout<<"iterator 1 != iterator 2 ,true"<<std::endl;
        cout<<(((++(cursor_list.zeroth()))==cursor_list.first())?"zeroth's next == first is true":"zeroth's next == first is false")<<endl;
        cout<<"first's data=";
        cout<<*(cursor_list.first())<<endl;
        cout<<"second element's data=";
        cout<<*(++(cursor_list.first()))<<endl;
        cout<<"last element's data=";
        cout<<*(++++(cursor_list.first()))<<endl;
        cout<<"***********************"<<endl;
    }
}

void testCursorListInsert(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test insert method:"<<endl;
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cursor_list.output();
        it++;
        cursor_list.insert(it,4);
        cursor_list.output();
       ++++it;
        cursor_list.insert(it,5);
        cursor_list.output();
        cout<<"***********************"<<endl;
    }
}

void testCursorListremove1(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cout<<"***********************"<<endl;
        cout<<"Test remove method:"<<endl;
        cout<<"before remove:"<<endl;
        cursor_list.output();
        int data = -1;
        bool is_success = false;
        cout<<"after remove some data not exists,is success:";
        is_success = cursor_list.remove(data);
        cout<<(is_success==false?"false":"true")<<endl;
        cout<<"after remove first element,is success:";
        is_success = cursor_list.remove(3);
        cout<<(is_success==false?"false":"true")<<endl;
        cursor_list.output();
        cout<<"after remove last elementuccess:";
        is_success = cursor_list.remove(1);
        cout<<(is_success==false?"false":"true")<<endl;
        cursor_list.output();
        cursor_list.insert(it,3);
        cursor_list.insert(it,4);
        cursor_list.output();
        cout<<"after remove some data in the middle,is success:";
        is_success = cursor_list.remove(3);
        cout<<(is_success==false?"false":"true")<<endl;
        cursor_list.output();
        cout<<"***********************"<<endl;
    }
}

void testCursorListremove2(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cout<<"***********************"<<endl;
        cout<<"Test remove  method(designated position):"<<endl;
        cout<<"before remove:"<<endl;
        cursor_list.output();
        int data = -1;
        bool is_success = false;
        cout<<"after remove some position out of bounds,is success:";
        CursorList<int>::iterator it_end = cursor_list.last();
        is_success = cursor_list.remove(it_end,data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cout<<"remove position=head's position,is success:";
        is_success = cursor_list.remove(it,data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cout<<"after remove first element,is success:";
        is_success = cursor_list.remove(cursor_list.first(),data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cursor_list.output();
        cout<<"after remove last element,is success:";
        is_success = cursor_list.remove(++(cursor_list.first()),data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cursor_list.output();
        cursor_list.insert(it,3);
        cursor_list.insert(it,4);
        cout<<"insert some data:"<<endl;
        cursor_list.output();
        cout<<"after remove some data in the middle,is success:";
        is_success = cursor_list.remove(++(cursor_list.first()),data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cursor_list.output();
        cout<<"***********************"<<endl;
    }
}

void testCursorListFind(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test find  method:"<<endl;
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cursor_list.output();
        cout<<"find some data not exists,";
        int data = -1;
        CursorList<int>::iterator it_ne = cursor_list.find(data);
        cout<<((it_ne==cursor_list.last())?"return nullptr":"return value is not nullptr")<<endl;
        cout<<"find first element,";
        data = 3;
        it_ne = cursor_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"find last element,";
        data = 1;
        it_ne = cursor_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"find some data in the middle,";
        data = 2;
        it_ne = cursor_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"***********************"<<endl;
    }
}


void testCursorListCopyControl(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test copy constructor:"<<endl;
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cout<<"CursorList output:";
        cursor_list.output();
        CursorList<int> cursor_list2(cursor_list);
        cout<<"CursorList2 output:";
        cursor_list2.output();
        cursor_list2.insert(cursor_list2.zeroth(),4);
        cout<<" after CursorList2 insert,CursorList2 output is:";
        cursor_list2.output();
        cout<<"***********************"<<endl;
        cout<<"Test assignment operator:"<<endl;
        cursor_list = cursor_list2;
        cout<<"after CursorList=CursorList2,CursorList output is:";
        cursor_list.output();
        cout<<"***********************"<<endl;
    }
}


void testCursorListOtherMethod(){
    CursorList<int> cursor_list;
    if(cursor_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test makeEmpty method:"<<endl;
        CursorList<int>::iterator it = cursor_list.zeroth();
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        cursor_list.output();
        cursor_list.makeEmpty();
        cursor_list.output();
        cout<<"***********************"<<endl;
        cout<<"***********************"<<endl;
        cursor_list.insert(it,1);
        cursor_list.insert(it,2);
        cursor_list.insert(it,3);
        bool is_empty = cursor_list.isEmpty();
        cout<<"The CursorList is empty=";
        cout<<((is_empty==true)?"true":"false")<<endl;
        cursor_list.makeEmpty();
        is_empty = cursor_list.isEmpty();
        cout<<"The CursorList is empty=";
        cout<<((is_empty==true)?"true":"false")<<endl;
        cout<<"***********************"<<endl;
    }
}

int main(int argc, char *argv[]){
    testCursorListInsert();
    testIterator();
    testCursorListremove1();
    testCursorListremove2();
    testCursorListFind();
    testCursorListOtherMethod();
    testCursorListCopyControl();
    return 0;
}
