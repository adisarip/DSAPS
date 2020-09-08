Q1: Problem Statement:
======================
- Implementatgion of "deque" : "Doubly Ended Queue"
- Deque is the same as dynamic arrays with the ability to resize itself
  automatically when an element is inserted or deleted, with their storage
  being handled automatically by the container.
- They support insertion and Deletion from both ends in amortized constant time.
- Inserting and erasing in the middle is linear in time.

Implementation of deque must satisfy the following performance requirements:
----------------------------------------------------------------------------
- deque() - initialize a blank deque.
- deque(n,x) - initialize a deque of length n with all values as x.
- push_back(x) - append data x at the end.
- pop_back() - erase data at the end.
- push_front(x) - append data x at the beginning.
- pop_front() - erase data at the beginning.
- front() - returns the first element(value) in the deque.
- back() - returns the last element(value) in the deque.
- empty() - returns true if deque is empty else returns false.
- size() - returns the current size of deque.
- resize(x, d, direction) - changes the size dynamically. If the new size is greater than
  the current size of the deque, then fill the empty space with the default value d.
  By default -> "direction" will be from "REVERSE". If "direction" set to "FORWARD" elements will
  be deleted or added at the front.
- clear() - remove all elements of deque.
- D[n] - returns the nth element of the deque.
         If n<0 then traverse the deque in reverse. Eg: D[-1] = last element;


Solution Outline:
=================
- Implemented a C++ Templates based generic Doubly ended queue.


Source Code Tree:
=================
20173071_Q3
├── Makefile
├── Readme.txt
├── bin
│   └── deque
├── obj
│   └── EvalDeque.o
└── src
    ├── Deque.H
    └── EvalDeque.C

3 directories, 6 files


Compilation Run:
================
20173071_Q3$ make clean;make
Cleaning all the object files and binaries.
rm -f core ./obj/EvalDeque.o ./bin/deque
g++ -Wall -std=c++1z -c src/EvalDeque.C -o obj/EvalDeque.o
Compiled src/EvalDeque.C successfully.
g++ ./obj/EvalDeque.o -o bin/deque
Linking Complete.
To start the file explorer run --> ./bin/deque
20173071_Q3$


Sample Execution Runs:
======================
-> verify the sequence of operations from main() in EvalDeque.C file.

20173071_Q3$ ./bin/deque
Deque Created with 10 elements
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5 10 15 16
5 5 5 5 5 5 5 5 5 5 10 15 16 0 0 0 0 0 0 0
5 5 5 5 5 5 5 5 5 5 10 15 16
0 0 0 0 0 0 0 5 5 5 5 5 5 5 5 5 5 10 15 16
5 5 5 5 5 5 5 5 5 5 10 15 16
5
16
10
Index out of range. Invalid Operation !
-407410640
Index out of range. Invalid Operation !
-407410640
5 5 5 5 5 5 5 5 5 5
16 15 10 5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5
5
10
Deque Cleared
20173071_Q3$
