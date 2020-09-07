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
- resize(x, d) - changes the size dynamically. If the new size is greater than
  the current size of the deque, then fill the empty space with the default value d.
  If the size is less then the current deque size delete elements from back.
- clear() - remove all elements of deque.
- D[n] - returns the nth element of the deque.


Solution Outline:
=================


Source Code Tree:
=================


Compilation Run:
================

Sample Execution Runs:
======================
