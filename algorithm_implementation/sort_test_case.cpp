/*************************************************************************
  > File Name: sort_test_case.cpp
  > Author:Haoson 
  > Created Time: Sun 28 Sep 2014 02:29:42 PM PDT
  > Description: 
 ************************************************************************/

#include<iostream>
using namespace std;
#include "sort.h"
#include "../data_structure/deque.h"
void testSelectionSort(){
    cout<<"***********************"<<endl;
    cout<<"******select sort******"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::selectionSort(deque.begin(),deque.end());
    deque.output();
    hds::selectionSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}

void testInsertionSort(){
    cout<<"***********************"<<endl;
    cout<<"*****insertion sort****"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::insertionSort(deque.begin(),deque.end());
    deque.output();
    hds::insertionSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}


void testShellSort(){
    cout<<"***********************"<<endl;
    cout<<"******shell sort*******"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::shellSort(deque.begin(),deque.end());
    deque.output();
    hds::shellSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}


void testMergeSort(){
    cout<<"***********************"<<endl;
    cout<<"******merge sort*******"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::mergeSort(deque.begin(),deque.end());
    deque.output();
    hds::mergeSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}


void testMergeSortBU(){
    cout<<"***********************"<<endl;
    cout<<"****merge sort BU******"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::mergeSortBU(deque.begin(),deque.end());
    deque.output();
    hds::mergeSortBU(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}

void testQuickSort(){
    cout<<"***********************"<<endl;
    cout<<"******quick sort*******"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::quickSort(deque.begin(),deque.end());
    deque.output();
    hds::quickSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();

    deque.clear();
    for(int i=0;i < 20;++i){
        deque.push_back(i+10);
    }
    deque.insert(deque.begin()+10,2);
    deque.insert(deque.begin()+2,34);
    deque.insert(deque.begin()+16,6);
    deque.insert(deque.begin()+13,78);
    deque.output();
    hds::quickSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}

void testQuick3WaySort(){
    cout<<"***********************"<<endl;
    cout<<"****quick3way sort*****"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::quick3WaySort(deque.begin(),deque.end());
    deque.output();
    hds::quick3WaySort(deque.begin(),deque.end(),hds::GreaterEqual<int>());
    deque.output();

    deque.clear();
    for(int i=0;i < 20;++i){
        deque.push_back(i+10);
    }
    deque.insert(deque.begin()+10,2);
    deque.insert(deque.begin()+2,34);
    deque.insert(deque.begin()+16,6);
    deque.insert(deque.begin()+13,78);
    deque.output();
    hds::quick3WaySort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}

void testHeapSort(){
    cout<<"***********************"<<endl;
    cout<<"******heap sort********"<<endl;
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(3);
    deque.push_back(2);
    deque.push_front(4);
    deque.output();
    hds::heapSort(deque.begin(),deque.end());
    deque.output();
    hds::heapSort(deque.begin(),deque.end(),hds::Greater<int>());
    deque.output();
    cout<<"***********************"<<endl;
}
int main(int argc,char*argv[]){
    testSelectionSort();
    testInsertionSort();
    testShellSort();
    testMergeSortBU();
    testQuickSort();
    testQuick3WaySort();
    testHeapSort();
}
