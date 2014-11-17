# algorithm-hodgepodge

## Introduction

    Algorithm-hodgepodge project is mainly to do some algorithm implementation.It contains four parts:
    1. A tiny STL implementation
    2. Implementation of some typical algorithm problems'solutions
    3. Implementation of basic sort algorithm 
    4. Implementation of some C++11 features 

## Contents

### my_tiny_stl
####Implementation of some data structures,inluding:
    1. deque(implemented by using a sequence of individually allocated fixed-size arrays);
    2. doubly_linked_list(similar to list in cpp,implemented as double-linked list);
    3. array_based_list(similar to vector in cpp,implemented by using dynamic array);
    4. priority_queue(implemented by using heap)
    5. some container adapters:stack,queue,bag
    6. others:cursor_based_list(a sequence container implemented by using cursor);linked_list(a sequence container implemented as singly linked-list)
    7. to do:binary tree,AVL tree,red black tree,hash tree，hash_map

####Implementation of iterator
    1. iterator_base
    2. Each container introduced above all provide their own iterator
####Implementation of Algorithm
    The implementation is in the algorithm_implementation folder,but just implemented the sorting algorithm
####Implementation of function object
    1. function_object

### algorithm_problems
####half_interval 
    1. printer problem
####recursive 
    1. rectangular-cut problem
    2. sudoku problem
    3. pair problem
    4. tictactoe problem
####search 
    1. pushing box problem
    2. graph coloring problem
    3. qtree2 problem(LCA)
    4. p-cousin problem(RMQ)
####graphs
    1. fedor and essay problem
    2. popular cows roblem(kosataju algorithm)
####dp 
    1. missile silos problem
    2. fibonacci problem
    3. 0/1 knapsack problem
    4. infinite knapsack problem
    5. minimize the difference problem
    6. flower arrangement problem
    7. barcode problem
    8. matrix multiplication problem
    9. edit distance problem
    

###algorithm_implementation
Some basic sort algorithm
### cpp_feature
//to do


## Compiling

Any C++11 compiler should work. 
