
#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
using namespace std;

#define ll long long

// A min heap node for k-way merging
struct Node
{
    int index; // array index
    ll  value; // value
};

class MinHeap
{
  public:
    MinHeap(Node a[], int n);
    ~MinHeap();
    int getLeftIndex(int level);  // get the index of left child
    int getRightIndex(int level); // get the index of right child
    Node getMinNode();            // get the next minimum node
    void replaceMinNode(Node node);        // replace the current minimum node with the next minimum from the file

  protected:
    void pHeapify(int index); // heapify the array of elements

  private:
    int size;
    Node* heap;
};

#endif // MINHEAP_H
