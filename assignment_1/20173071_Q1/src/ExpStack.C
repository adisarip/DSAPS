
#include "ExpStack.H"
#include <iostream>
using namespace std;

ExpStack::ExpStack()
:mHead(NULL)
{
}

ExpStack::~ExpStack()
{
    this->clear();
}

void ExpStack::push(string expTokenParm)
{
    ExpNode* sNode = new ExpNode();
    sNode->mToken = expTokenParm;
    if (NULL == mHead)
    {
        mHead = sNode;
    }
    else
    {
        sNode->mNext = mHead;
        mHead = sNode;
    }
}

string ExpStack::pop()
{
    string sToken = "";
    if (NULL != mHead)
    {
        ExpNode* sNode = mHead;
        sToken = sNode->mToken;
        mHead = sNode->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
    return sToken;
}

void ExpStack::clear()
{
    ExpNode* sNode = NULL;
    // delete all the elements in stack and deallocate their memory.
    while(NULL != mHead)
    {
        sNode = mHead;
        mHead = sNode->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
}

bool ExpStack::isEmpty()
{
    bool sIsEmpty = false;
    if (mHead == NULL)
    {
        sIsEmpty = true;
    }
    return sIsEmpty;
}

void ExpStack::print()
{
    // Traverse and print the current stack
    ExpNode* sNode = mHead;

    if (NULL == sNode)
    {
        cout << "Expression stack is empty" << endl;
        return;
    }

    while (NULL != sNode)
    {
        cout << sNode->mToken;
        sNode = sNode->mNext;
    }
    cout << endl;
    return;
}
