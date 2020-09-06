
// A Queue implementation for storing operators/operands for evaluating experssions
// Base data structure: Singly Linked List

#ifndef __EXPQUEUE__
#define __EXPQUEUE__

#include "Node.H"
#include <string>
using namespace std;

class ExpQueue
{
  public:
    ExpQueue();
    ~ExpQueue();

    void enqueue(string expTokenParm);
    string dequeue();
    void clear();
    void print();
    bool isEmpty();

  private:
    ExpNode* mHead;
    ExpNode* mTail;
};

#endif
