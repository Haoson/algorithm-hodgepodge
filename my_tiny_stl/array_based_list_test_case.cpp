/*************************************************************************
  > File Name: array_based_list_test_case.cpp
  > Author:Haoson 
  > Created Time: Wed 24 Sep 2014 12:55:47 PM PDT
 ************************************************************************/

#include<iostream>
#include "array_based_list.h"
using namespace std;

void testABLInsert(){
    ArrayBasedList<int> abl;
    if(abl.create()){
        for(int index=0;index < 5;++index){
            abl.insert(index*2); 
        }
        cout<<"***********************"<<endl;
        cout<<"Test insert method:"<<endl;
        abl.output();
        abl.insert(-1,-1);
        abl.insert(0,10);
        abl.insert(1,11);
        abl.insert(4,14);
        abl.insert(8,17);
        abl.output();
        cout<<"***********************"<<endl;
    }
}

void testABLRemove(){
    ArrayBasedList<int> abl;
    if(abl.create()){
        for(int index=0;index < 6;++index){
            abl.insert(index*2); 
        }

        cout<<"***********************"<<endl;
        cout<<"Test remove method:"<<endl;
        cout<<"before remove:"<<endl;
        abl.output();
        int data = -1;
        abl.remove(-1,data);
        cout<<"after remove some data not exists,the data=";
        cout<<data<<endl;
        abl.remove(6,data);
        cout<<"after remove data index out of bounds,the data=";
        cout<<data<<endl;
        abl.remove(0,data);
        cout<<"after remove abl[0],the abl[0]=";
        cout<<data<<endl;
        abl.remove(abl.length()-1,data);
        cout<<"after remove abl[abl.length()-1],the abl[abl.length()-1]=";
        cout<<data<<endl;
        abl.remove(1,data);
        cout<<"after remove abl[1],the abl[1]=";
        cout<<data<<endl;
        abl.output();
        cout<<"***********************"<<endl;
    }
}

void testABLSearch(){
    ArrayBasedList<int> abl;
    if(abl.create()){
        for(int index=0;index < 5;++index){
            abl.insert(index*2); 
        }
        cout<<"***********************"<<endl;
        cout<<"Test search method:"<<endl;
        abl.output();
        int index;
        index  = abl.search(100);
        cout<<"search data not exist,the return value=";
        cout<<index<<endl;
        index  = abl.search(0);
        cout<<"search data=0,the return value=";
        cout<<index<<endl;
        index  = abl.search(8);
        cout<<"search data=8,the return value=";
        cout<<index<<endl;
        index  = abl.search(4);
        cout<<"search data=4,the return value=";
        cout<<index<<endl;
        cout<<"***********************"<<endl;
    }
}

void testABLFind(){
    ArrayBasedList<int> abl;
    if(abl.create()){
        for(int index=0;index < 5;++index){
            abl.insert(index*2); 
        }
        cout<<"***********************"<<endl;
        cout<<"Test find method:"<<endl;
        abl.output();
        int data = -1;
        abl.find(100,data);
        cout<<"find data not exist,the data=";
        cout<<data<<endl;
        abl.find(0,data);
        cout<<"find data which index=0,the data=";
        cout<<data<<endl;
        abl.find(2,data);
        cout<<"search data which index=2,the data=";
        cout<<data<<endl;
        abl.find(4,data);
        cout<<"search data which  index=4,the data=";
        cout<<data<<endl;
        cout<<"***********************"<<endl;
    }
}


void testABLCopyControl(){
    ArrayBasedList<int> abl;
    if(abl.create()){
        for(int index=0;index < 5;++index){
            abl.insert(index*2); 
        }
        cout<<"***********************"<<endl;
        cout<<"Test copy constructor:"<<endl;
        cout<<"abl output:";
        abl.output();
        ArrayBasedList<int> abl2(abl);
        cout<<"abl2 output:";
        abl2.output();
        cout<<"abl2 length=";
        cout<<abl2.length()<<endl;
        abl2.insert(123);
        cout<<" after abl2 insert,abl2 output is:";
        abl2.output();
        cout<<"***********************"<<endl;
        cout<<"Test assignment operator:"<<endl;
        abl = abl2;
        cout<<"after abl=abl2,abl output is:";
        abl.output();
        cout<<"abl length=";
        cout<<abl.length()<<endl;
        cout<<"***********************"<<endl;
    }
}


void testABLOtherMethod(){
    ArrayBasedList<int> abl;
    if(abl.create()){
        for(int index=0;index < 5;++index){
            abl.insert(index*2); 
        }
        cout<<"***********************"<<endl;
        cout<<"Test [] method:"<<endl;
        abl.output();
        cout<<abl[0]<<" "<<abl[1]<<" "<<abl[2]<<" "<<abl[3]<<" "<<abl[4]<<endl;
        cout<<"***********************"<<endl;
        cout<<"Test makeEmpty method:"<<endl;
        abl.output();
        abl.makeEmpty();
        abl.output();
        cout<<"***********************"<<endl;
        cout<<"***********************"<<endl;
        cout<<"Test isEmpty and length method:"<<endl;
        for(int index=0;index < 5;++index){
            abl.insert(index*2); 
        }
        abl.output();
        bool is_empty = abl.isEmpty();
        cout<<"The abl is empty=";
        cout<<is_empty<<endl;
        int abl_length = abl.length();
        cout<<"The abl length=";
        cout<<abl_length<<endl;
        abl.makeEmpty();
        is_empty = abl.isEmpty();
        cout<<"After make empty,The abl is empty=";
        cout<<is_empty<<endl;
        abl_length = abl.length();
        cout<<"iAfter make empty,the abl length=";
        cout<<abl_length<<endl;
        cout<<"***********************"<<endl;
    }
}

int main(int argc, char *argv[]){
    testABLInsert();
    testABLRemove();
    testABLSearch();
    testABLFind();
    testABLOtherMethod();
    testABLCopyControl();
    return 0;
}
