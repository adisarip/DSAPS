

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
// The following represent the corresponding query number for each function:
// 1. push_front(x)
// 2. pop_front()
// 3. push_back(x)
// 4. pop_back()
// 5. deque()
// 6. deque(n,x)
// 7. front()
// 8. back()
// 9. empty()
// 10. size()
// 11. resize(x, d)
// 12. clear()
// 13. D[n]
// 14. display() - display contents of deque
// Your task is to take Q queries as input and perform the corresponding
// function and display the output.

// Input format:
// =============
// First Line contains the query count Q
// Next Q lines contain the query no and input( if any)

// Output format:
// ==============
// Q-1 lines displaying queue after each query
// NOTE: for correct execution, the first query will be always deque() or deque(n,x)
// Output for first query is not required as deque() will be empty

// Sample Input:
// =============
// 6
// 5
// 1 2
// 1 3
// 3 4
// 7
// 10

// Sample Output:
// ==============
// 2
// 3 2
// 3 2 4
// 3
// 3

int main (int argc, char* argv[])
{
    int Q = 0;
    int cmd = 0;
    int x = 0; int n = 0;
    Deque<int> deque;

    cin >> Q; // read number of queries
    cin >> cmd; // first query to create the Deque
    if (cmd == 5)
    {
        // created already
    }
    else if (cmd == 6)
    {
        cin >> n >> x;
        deque.resize(n,x);
    }
    else
    {
        // Invalid Command - create the deque first.
        return 0;
    }

    for (int i=0; i<Q-1; i++)
    {
        cin >> cmd;
        switch (cmd)
        {
            case 1:
                // push_front(x)
                cin >> x;
                deque.push_front(x);
                deque.print();
                break;
            case 2:
                // pop_front(x)
                deque.pop_front();
                deque.print();
                break;
            case 3:
                // push_back(x)
                cin >> x;
                deque.push_back(x);
                deque.print();
                break;
            case 4:
                // pop_back(x)
                deque.pop_back();
                deque.print();
                break;
            case 7:
                // front()
                cout << deque.front() << endl;
                break;
            case 8:
                // back()
                cout << deque.back() << endl;
                break;
            case 9:
                // empty()
                cout << deque.isEmpty() << endl;
                break;
            case 10:
                // size()
                cout << deque.size() << endl;
                break;
            case 11:
                // resize(size,d)
                cin >> n >> x;
                deque.resize(n,x);
                deque.print();
                break;
            case 12:
                // clear()
                deque.clear();
                deque.print();
                break;
            case 13:
                // D[n]
                cin >> n;
                cout << deque[n] << endl;
                break;
            case 14:
                // display()
                deque.print();
                break;
            default:
                break;
        };
    }

    return 0;
}
