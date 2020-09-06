
#include "ExpQueue.H"
#include <iostream>
using namespace std;

ExpQueue::ExpQueue()
:mHead(NULL)
,mTail(NULL)
{
}

ExpQueue::~ExpQueue()
{
    this->clear();
}

void ExpQueue::enqueue(string expTokenParm)
{
    ExpNode* sNode = new ExpNode();
    if (sNode != NULL)
    {
        sNode->mToken = expTokenParm;
        if (mHead == mTail && mHead == NULL)
        {
            mHead = sNode;
            mTail = sNode;
        }
        else
        {
            sNode->mNext = NULL;
            mTail->mNext = sNode;
            mTail = sNode;
        }
    }
}

string ExpQueue::dequeue()
{
    string sToken = "";
    if (mHead != NULL)
    {
        ExpNode* sNode = mHead;
        sToken = sNode->mToken;
        mHead = sNode->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
    return sToken;
}

void ExpQueue::clear()
{
    // delete all the elements in queue and deallocate their memory.
    while(mHead != NULL)
    {
        ExpNode* sNode = mHead;
        mHead = mHead->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
}

void ExpQueue::print()
{
    // Traverse and print the current stack
    ExpNode* sNode = mHead;

    if (sNode == NULL)
    {
        cout << "Expression queue is empty" << endl;
        return;
    }

    while (sNode != NULL)
    {
        cout << sNode->mToken << " ";
        sNode = sNode->mNext;
    }
    cout << endl;
    return;
}
