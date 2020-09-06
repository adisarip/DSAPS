
// A Stack implementation for storing operators for evaluating experssions
// Base data structure: Singly Linked List

#ifndef __EXPSTACK__
#define __EXPSTACK__

#include "Node.H"
using namespace std;

class ExpStack
{
  public:
    ExpStack();
    ~ExpStack();

    void push(string expTokenParm);
    string pop();
    void clear();
    void print();

  private:
    ExpNode* mHead;
};

#endif
