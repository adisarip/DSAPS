

#ifndef __NODE__
#define __NODE__

#include <string>
using namespace std;

// A Singly Linked List Node used in expresion evaluation
struct ExpNode
{
    string mToken;
    ExpNode* mNext;
    inline ExpNode():mToken(""),mNext(NULL){};
    inline ~ExpNode(){};
};

#endif
