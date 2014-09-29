/*************************************************************************
  > File Name: linked_list_test_case.cpp
  > Author:Haoson 
  > Created Time: Thu 25 Sep 2014 01:22:02 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
#include<iostream>
#include "linked_list.h"


void testIterator(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test iterator:"<<endl;
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        linked_list.output();
        ++it;
        it++;
        LinkedList<int>::iterator it2 = linked_list.begin();
        it2++;
        if(it==it2)
            cout<<"iterator 1 == iterator 2 ,true"<<std::endl;
        it2++;
        if(it!=it2)
            cout<<"iterator 1 != iterator 2 ,true"<<std::endl;
        cout<<(((++(linked_list.zeroth()))==linked_list.begin())?"zeroth's next == begin is true":"zeroth's next == begin is false")<<endl;
        cout<<"begin's data=";
        cout<<*(linked_list.begin())<<endl;
        cout<<"second element's data=";
        cout<<*(++(linked_list.begin()))<<endl;
        cout<<"last element's data=";
        cout<<*(++++(linked_list.begin()))<<endl;
        cout<<"***********************"<<endl;
    }
}

void testLinkedListInsert(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test insert method:"<<endl;
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        linked_list.output();
        it++;
        linked_list.insert(it,4);
        linked_list.output();
        ++++++it;
        linked_list.insert(it,5);
        linked_list.output();
        cout<<"***********************"<<endl;
    }
}

void testLinkedListErase1(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        cout<<"***********************"<<endl;
        cout<<"Test remove method:"<<endl;
        cout<<"before remove:"<<endl;
        linked_list.output();
        int data = -1;
        bool is_success = false;
        cout<<"after remove some data not exists,is success:";
        is_success = linked_list.erase(data);
        cout<<(is_success==false?"false":"true")<<endl;
        cout<<"after remove first element,is success:";
        is_success = linked_list.erase(3);
        cout<<(is_success==false?"false":"true")<<endl;
        linked_list.output();
        cout<<"after remove last elementuccess:";
        is_success = linked_list.erase(1);
        cout<<(is_success==false?"false":"true")<<endl;
        linked_list.output();
        linked_list.insert(it,3);
        linked_list.insert(it,4);
        linked_list.output();
        cout<<"after remove some data in the middle,is success:";
        is_success = linked_list.erase(3);
        cout<<(is_success==false?"false":"true")<<endl;
        linked_list.output();
        cout<<"***********************"<<endl;
    }
}

void testLinkedListErase2(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        cout<<"***********************"<<endl;
        cout<<"Test remove  method(designated position):"<<endl;
        cout<<"before remove:"<<endl;
        linked_list.output();
        int data = -1;
        bool is_success = false;
        cout<<"after remove some position out of bounds,is success:";
        LinkedList<int>::iterator it_end = linked_list.end();
        is_success = linked_list.erase(it_end,data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cout<<"remove position=head's position',is success:";
        is_success = linked_list.erase(it,data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        cout<<"after remove first element,is success:";
        is_success = linked_list.erase(linked_list.begin(),data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        linked_list.output();
        cout<<"after remove last element,is success:";
        is_success = linked_list.erase(++(linked_list.begin()),data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        linked_list.output();
        linked_list.insert(it,3);
        linked_list.insert(it,4);
        cout<<"insert some data:"<<endl;
        linked_list.output();
        cout<<"after remove some data in the middle,is success:";
        is_success = linked_list.erase(++(linked_list.begin()),data);
        cout<<(is_success==false?"false":"true")<<",and the data=";
        cout<<data<<endl;
        linked_list.output();
        cout<<"***********************"<<endl;
    }
}

void testLinkedListFind(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test find  method:"<<endl;
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        linked_list.output();
        cout<<"find some data not exists,";
        int data = -1;
        LinkedList<int>::iterator it_ne = linked_list.find(data);
        cout<<((it_ne==linked_list.end())?"return nullptr":"return value is not nullptr")<<endl;
        cout<<"find first element,";
        data = 3;
        it_ne = linked_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"find last element,";
        data = 1;
        it_ne = linked_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"find some data in the middle,";
        data = 2;
        it_ne = linked_list.find(data);
        cout<<"the data=";
        cout<<*(it_ne)<<endl;
        cout<<"***********************"<<endl;
    }
}

void testLinkedListSearch(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test search method:"<<endl;
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        linked_list.output();
        cout<<"search some data not exists,is success:";
        bool is_success = linked_list.search(-1);
        cout<<(is_success==false?"false":"true")<<endl;
        cout<<"search first element,is success:";
        is_success = linked_list.search(3);
        cout<<(is_success==false?"false":"true")<<endl;
        cout<<"find last element,is success:";
        is_success = linked_list.search(1);
        cout<<(is_success==false?"false":"true")<<endl;
        cout<<"find some data in the middle,is success:";
        is_success = linked_list.search(2);
        cout<<(is_success==false?"false":"true")<<endl;
        cout<<"***********************"<<endl;
    }
}


void testLinkedListCopyControl(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test copy constructor:"<<endl;
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        cout<<"LinkedList output:";
        linked_list.output();
        LinkedList<int> linked_list2(linked_list);
        cout<<"LinkedList2 output:";
        linked_list2.output();
        cout<<"LinkedList2 length=";
        cout<<linked_list2.length()<<endl;
        linked_list2.insert(linked_list2.zeroth(),4);
        cout<<" after LinkedList2 insert,LinkedList2 output is:";
        linked_list2.output();
        cout<<"***********************"<<endl;
        cout<<"Test assignment operator:"<<endl;
        linked_list = linked_list2;
        cout<<"after LinkedList=LinkedList2,LinkedList output is:";
        linked_list.output();
        cout<<"LinkedList length=";
        cout<<linked_list.length()<<endl;
        cout<<"***********************"<<endl;
    }
}


void testLinkedListOtherMethod(){
    LinkedList<int> linked_list;
    if(linked_list.create()){
        cout<<"***********************"<<endl;
        cout<<"Test makeEmpty method:"<<endl;
        LinkedList<int>::iterator it = linked_list.zeroth();
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        linked_list.output();
        linked_list.makeEmpty();
        linked_list.output();
        cout<<"***********************"<<endl;
        cout<<"***********************"<<endl;
        linked_list.insert(it,1);
        linked_list.insert(it,2);
        linked_list.insert(it,3);
        bool is_empty = linked_list.isEmpty();
        cout<<"The LinkedList is empty=";
        cout<<((is_empty==true)?"true":"false")<<endl;
        int LinkedList_length = linked_list.length();
        cout<<"The LinkedList length=";
        cout<<LinkedList_length<<endl;
        linked_list.makeEmpty();
        is_empty = linked_list.isEmpty();
        LinkedList_length = linked_list.length();
        cout<<"After make empty,the LinkedList length=";
        cout<<LinkedList_length<<endl;
        cout<<"The LinkedList is empty=";
        cout<<((is_empty==true)?"true":"false")<<endl;
        cout<<"***********************"<<endl;
    }
}

int main(int argc, char *argv[]){
    testLinkedListInsert();
    testIterator();
    testLinkedListErase1();
    testLinkedListErase2();
    testLinkedListFind();
    testLinkedListSearch();
    testLinkedListOtherMethod();
    testLinkedListCopyControl();
    return 0;
}
