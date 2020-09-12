

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

// The vector and sstream are only used for the driver program
#include <sstream>
#include <vector>

vector<int> split(const string& s, char delimiter)
{
   vector<int> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(stoi(token));
   }
   return tokens;
}

int main (int argc, char* argv[])
{
    int Q = 0;
    int cmd = 0;
    Deque<int> deque;

    string s;
    getline(cin, s);
    Q = stoi(s);
    vector<string> iQueries;
    for (int i=1; i<=Q; i++)
    {
        getline(cin, s);
        iQueries.push_back(s);
    }

    cout << "========== Deque states after every operation ==========" << endl;

    for (string s : iQueries)
    {
        vector<int> tokens = split(s, ' ');
        cmd = tokens.at(0);
        switch (cmd)
        {
            case 1:
                // push_front(x)
                deque.push_front(tokens.at(1));
                deque.print();
                break;
            case 2:
                // pop_front(x)
                deque.pop_front();
                deque.print();
                break;
            case 3:
                // push_back(x)
                deque.push_back(tokens.at(1));
                deque.print();
                break;
            case 4:
                // pop_back(x)
                deque.pop_back();
                deque.print();
                break;
            case 5:
                break; // already created
            case 6:
                // As the default deque is already created - resize if cmd == 6
                deque.resize(tokens.at(1), tokens.at(2));
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
                deque.resize(tokens.at(1), tokens.at(2));
                deque.print();
                break;
            case 12:
                // clear()
                deque.clear();
                deque.print();
                break;
            case 13:
                // D[n]
                cout << deque[tokens.at(1)] << endl;
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
