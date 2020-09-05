
#include "ExpQueue.H"
#include <iostream>
using namespace std;

ExpQueue::ExpQueue()
:mHead(nullptr)
,mTail(nullptr)
,mCount(0)
{
}

ExpQueue::~ExpQueue()
{
    this->clear();
}

void ExpQueue::enqueue(string expTokenParm)
{
    ExpNode* sNode = new ExpNode();
    sNode->mToken = expTokenParm;
    if (0 == mCount)
    {
        mHead = sNode;
        mTail = sNode;
    }
    else
    {
        sNode->mNext = nullptr;
        mTail->mNext = sNode;
        mTail = sNode;
    }
    mCount++;
}

string ExpQueue::dequeue()
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

void ExpQueue::clear()
{
    // delete all the elements in queue and deallocate their memory.
    while(nullptr != mHead)
    {
        ExpNode* sNode = mHead;
        mHead = sNode->mNext;
        sNode->mNext = nullptr;
        delete(sNode);
        mCount--;
    }
    cout << "Expression Queue Cleared" << endl;
}

void ExpQueue::print()
{
    // Traverse and print the current stack
    ExpNode* sNode = mHead;

    if (nullptr == sNode)
    {
        cout << "Expression queue is empty" << endl;
        return;
    }
    else
    {
        cout << "Queue size: " << mCount << endl;
    }

    while (nullptr != sNode)
    {
        cout << sNode->mToken;
        sNode = sNode->mNext;
    }
    cout << endl;
    return;
}
