
#include "ExpStack.H"
#include <iostream>
using namespace std;

ExpStack::ExpStack()
:mHead(nullptr)
,mCount(0)
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
    if (0 == mCount)
    {
        mHead = sNode;
    }
    else
    {
        sNode->mNext = mHead;
        mHead = sNode;
    }
    mCount++;
}

string ExpStack::pop()
{
    string sToken = "";
    if (nullptr != mHead)
    {
        ExpNode* sNode = mHead;
        sToken = sNode->mToken;
        mHead = sNode->mNext;
        sNode->mNext = nullptr;
        delete(sNode);
        mCount--;
    }
    return sToken;
}

void ExpStack::clear()
{
    // delete all the elements in stack and deallocate their memory.
    while(nullptr != mHead)
    {
        ExpNode* sNode = mHead;
        mHead = sNode->mNext;
        sNode->mNext = nullptr;
        delete(sNode);
        mCount--;
    }
    cout << "Expression Stack Cleared" << endl;
}

void ExpStack::print()
{
    // Traverse and print the current stack
    ExpNode* sNode = mHead;

    if (nullptr == sNode)
    {
        cout << "Expression stack is empty" << endl;
        return;
    }
    else
    {
        cout << "Stack size: " << mCount << endl;
    }

    while (nullptr != sNode)
    {
        cout << sNode->mToken;
        sNode = sNode->mNext;
    }
    cout << endl;
    return;
}
