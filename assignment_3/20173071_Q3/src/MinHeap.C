
#include "MinHeap.H"
#include <string>
using namespace std;

MinHeap::MinHeap(Node a[], int n)
:size(n)
,heap(a)
{
    int index = (size - 1) / 2;
    while (index >= 0)
    {
        pHeapify(index);
        index--;
    }
}

MinHeap::~MinHeap()
{
    delete[] heap;
    size = 0;
}

int  MinHeap::getLeftIndex(int level)
{
    return (2*level + 1);
}

int  MinHeap::getRightIndex(int level)
{
    return (2*level + 2);
}

Node MinHeap::getMinNode()
{
    return heap[0];
}

void MinHeap::replaceMinNode(Node node)
{
    heap[0] = node;
    pHeapify(0);
}

// Protected members definitions

void MinHeap::pHeapify(int index)
{
    int left = getLeftIndex(index);
    int right = getRightIndex(index);
    int smallest = index;

    if (left < size && heap[left].value < heap[index].value)
    {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        // swap the smallest node with the current index
        Node x = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = x;

        // heapify the min heap
        pHeapify(smallest);
    }
}
