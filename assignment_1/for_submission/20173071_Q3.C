

// A generic implementation of a deque (doubly ended queue) using templates

#include <iostream>
using namespace std;

const int FORWARD = 1;
const int REVERSE = -1;

template <class T>
class Node
{
  public:
    inline Node():mPrev(NULL),mNext(NULL){};
    inline ~Node(){};
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
    void push_back(const T& dataParm);
    void pop_back();
    void push_front(const T& dataParm);
    void pop_front();
    T front();
    T back();
    bool isEmpty();
    int size();
    void clear();
    T& operator[](int i);

    void resize(int sizeParm,
                T fillParm,
                const int directionParm = REVERSE);

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
    cout << "Deque Created" << endl;
}

template <class T>
Deque<T>::Deque(int sizeParm, T fillParm)
:mSize(sizeParm)
{
    // create the first node
    mHead = new Node<T>();
    mHead->mData = fillParm;
    mTail = mHead;

    // create the remaining nodes
    for (int i=1; i<sizeParm; i++)
    {
        Node<T>* sNode = new Node<T>();
        sNode->mData = fillParm;
        mTail->mNext = sNode;
        sNode->mPrev = mTail;
        mTail = sNode;
    }
    mSize = sizeParm;
    cout << "Deque Created with " << mSize << " elements" << endl;
}

template <class T>
Deque<T>::~Deque()
{
    this->clear();
}

template <class T>
void Deque<T>::resize(int sizeParm,
                      T fillParm,
                      const int directionParm)
{
    if (mSize < sizeParm)
    {
        int sCount = sizeParm - mSize;
        if (directionParm == FORWARD)
        {
            // add nodes at front
            for (int i=0; i<sCount; i++)
            {
                this->push_front(fillParm);
            }
        }
        else
        {
            // add nodes at back - default
            for (int i=0; i<sCount; i++)
            {
                this->push_back(fillParm);
            }
        }
    }
    else if (mSize > sizeParm)
    {
        int sCount = mSize - sizeParm;
        if (directionParm == FORWARD)
        {
            // delete from front
            for (int i=0; i<sCount; i++)
            {
                this->pop_front();
            }
        }
        else
        {
            // delete from back - default
            for (int i=0; i<sCount; i++)
            {
                this->pop_back();
            }
        }
    }
}

template <class T>
void Deque<T>::push_back(const T& dataParm)
{
    Node<T>* sNode = new Node<T>();
    sNode->mData = dataParm;
    if (mSize == 0)
    {
        mHead = sNode;
        mTail = sNode;
    }
    else
    {
        mTail->mNext = sNode;
        sNode->mPrev = mTail;
        mTail = sNode;
    }
    mSize++;
}

template <class T>
void Deque<T>::pop_back()
{
    Node<T>* sNode = mTail;
    mTail = mTail->mPrev;
    mTail->mNext = NULL;
    sNode->mPrev = NULL;
    sNode->mNext = NULL;
    delete(sNode);
    mSize--;
}

template <class T>
void Deque<T>::push_front(const T& dataParm)
{
    Node<T>* sNode = new Node<T>();
    sNode->mData = dataParm;
    if (mSize == 0)
    {
        mHead = sNode;
        mTail = sNode;
    }
    else
    {
        mHead->mPrev = sNode;
        sNode->mNext = mHead;
        mHead = sNode;
    }
    mSize++;
}

template <class T>
void Deque<T>::pop_front()
{
    Node<T>* sNode = mHead;
    mHead = mHead->mNext;
    mHead->mPrev = NULL;
    sNode->mPrev = NULL;
    sNode->mNext = NULL;
    delete(sNode);
    mSize--;
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
    mSize = 0;
    cout << "Deque Cleared" << endl;
}

template <class T>
T Deque<T>::front()
{
    return mHead->mData;
}

template <class T>
T Deque<T>::back()
{
    return mTail->mData;
}

template <class T>
T& Deque<T>::operator[](int indexParm)
{
    T sTmp;
    T& sRetValue = sTmp;
    if (mSize == 0)
    {
        cout << "Deque is Empty. Invalid Operation !" << endl;
    }
    else if (indexParm >= mSize || indexParm < -mSize)
    {
        cout << "Index out of range. Invalid Operation !" << endl;
    }
    else
    {
        if (indexParm >=0)
        {
            Node<T>* sNode = mHead;
            for (int i=0; i<indexParm; i++)
            {
                sNode = sNode->mNext;
            }
            sRetValue = sNode->mData;
        }
        else
        {
            Node<T>* sNode = mTail;
            int sIndex = -1-indexParm;
            for (int i=0; i<sIndex; i++)
            {
                sNode = sNode->mPrev;
            }
            sRetValue = sNode->mData;
        }
    }
    return sRetValue;
}

template <class T>
bool Deque<T>::isEmpty()
{
    bool sIsEmpty = (mSize == 0) ? true : false;
    return sIsEmpty;
}

template <class T>
int Deque<T>::size()
{
    return mSize;
}


//============ Driver Program ==============//

int main (int argc, char* argv[])
{
    Deque<int> deque(10, 5);
    deque.print();
    deque.push_back(10);
    deque.push_back(15);
    deque.push_back(16);
    deque.print();
    deque.resize(20, 0);
    deque.print();
    deque.resize(13, 0);
    deque.print();
    deque.resize(20, 0, FORWARD);
    deque.print();
    deque.resize(13, 0, FORWARD);
    deque.print();
    cout << deque[0] << endl;
    cout << deque[-1] << endl;
    cout << deque[-3] << endl;
    cout << deque[-14] << endl;
    cout << deque[13] << endl;
    deque.pop_back();
    deque.pop_back();
    deque.pop_back();
    deque.print();
    deque.push_front(10);
    deque.push_front(15);
    deque.push_front(16);
    deque.print();
    deque.pop_front();
    deque.pop_front();
    deque.pop_front();
    deque.print();
    cout << deque.front() << endl;
    cout << deque.back() << endl;
    cout << deque.size() << endl;
    return 0;
}
