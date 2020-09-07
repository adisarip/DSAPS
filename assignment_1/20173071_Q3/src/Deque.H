
// A generic implementation of a deque (doubly ended queue) using templates

#ifndef __DEQUE__
#define __DEQUE__

#include <iostream>
using namespace std;

template <class T>
class Node
{
  public:
    T mData;
    Node<T>* mPrev;
    Node<T>* mNext;
};

template <class T>
class Deque
{
  public:
    Deque();
    Deque(int sizeParm, T fillParm);
    ~Deque();
    void print();
    int push_back(const T&);
    int pop_back();
    int push_front(const T&);
    int pop_front();
    T front();
    T back();
    bool isEmpty();
    int size();
    int resize(int sizeParm, T fillParm);
    void clear();
  private:
    int      mSize;
    T        mFront;
    T        mBack;
    Node<T>* mHead;
    Node<T>* mTail;
};

template <class T>
Deque<T>::Deque()
:mSize(0)
,mHead(NULL)
,mTail(NULL)
{
}

template <class T>
Deque<T>::Deque(int sizeParm, T fillParm)
:mSize(sizeParm)
{
    // create the first node
    Node<T>* sNode = new Node<T>();
    sNode->mData = fillParm;
    mHead = sNode;
    mTail = sNode;

    // create the remaining nodes
    for (int i=1; i<sizeParm; i++)
    {
        Node<T>* sNode = new Node<T>();
        sNode->mData = fillParm;
        sNode->mNext = NULL;
        mTail->mNext = sNode;
        mTail = sNode;
    }
}

template <class T>
Deque<T>::~Deque()
{
}

template <class T>
void Deque<T>::print()
{
    Node<T>* sNode = mHead;
    while(sNode != NULL)
    {
        cout << sNode->mData << " ";
        sNode = sNode->mNext;
    }
    cout << endl;
}

template <class T>
void Deque<T>::clear()
{
    Node<T>* sNode = NULL;
    while(mHead != NULL)
    {
        sNode = mHead;
        mHead = mHead->mNext;
        sNode->mPrev = NULL;
        sNode->mNext = NULL;
        delete(sNode);
    }
}

template <class T>
int Deque<T>::resize(int sizeParm, T fillParm)
{
    return 0;
}

template <class T>
int Deque<T>::push_back(const T&)
{
    return 0;
}

template <class T>
int Deque<T>::pop_back()
{
    return 0;
}

template <class T>
int Deque<T>::push_front(const T&)
{
    return 0;
}

template <class T>
int Deque<T>::pop_front()
{
    return 0;
}

template <class T>
T Deque<T>::front()
{
    T sRetVal;
    return sRetVal;
}

template <class T>
T Deque<T>::back()
{
    T sRetVal;
    return sRetVal;
}

template <class T>
bool isEmpty()
{
    return true;
}

template <class T>
int Deque<T>::size()
{
    return mSize;
}


#endif
