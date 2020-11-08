
// A Trie Data Structure implementation for XOR computations

#include <iostream>
#include <vector>
using namespace std;

#define ll long long
const int SIZE = 64; // 8 bytes - 64-bit

class Node
{
  public:
    Node():leafValue(-1)
    {
        child[0] = NULL;
        child[1] = NULL;
    }
    ~Node(){};

    // data
    ll leafValue;
    Node* child[2];
};

class BinaryTRIE
{
  public:
    BinaryTRIE();
    ~BinaryTRIE();
    void buildBinaryTrie(vector<ll>& a);
    ll computeMaximumXOR(ll key, ll& element);

  protected:
    void pInsert(ll x); // insert a number in binary format into the TRIE data structure

  protected:
    Node* root;
};

BinaryTRIE::BinaryTRIE()
{
    root = new Node();
}

BinaryTRIE::~BinaryTRIE()
{
}

void BinaryTRIE::buildBinaryTrie(vector<ll>& a)
{
    // insert the input array into the TRIE in binary format
    for (auto x : a)
    {
        pInsert(x);
    }
}

ll BinaryTRIE::computeMaximumXOR(ll key, ll& element)
{
    Node* sNode = root;
    for (ll i = SIZE-1; i > 0; i--)
    {
        bool current_bit = (key & (1 << i));
        if (sNode->child[1 - current_bit] != NULL)
        {
            sNode = sNode->child[1 - current_bit];
        }
        else if (sNode->child[current_bit] != NULL)
        {
            sNode = sNode->child[current_bit];
        }
    }
    element = sNode->leafValue;
    return key ^ element;
}

// protected member definitions

void BinaryTRIE::pInsert(ll value)
{
    Node* sNode = root;
    // insert the numbers in bitwise format into the TRIE
    // starting with the Most-Significant-Bit
    for (ll i = SIZE-1; i > 0; i--)
    {
        bool current_bit = (value & (1 << i));
        if (sNode->child[current_bit] == NULL)
        {
            // create a node for the corresponding bit value 0/1
            sNode->child[current_bit] = new Node();
        }
        sNode = sNode->child[current_bit];
    }
    // store the value in the leaf node
    sNode->leafValue = value;
}


// ================================= Driver Program =================================

int main(int argc, char* argv[])
{
    vector<ll> nList;
    int N = 0;
    int Q = 0;

    cin >> N >> Q;
    for (int i=0; i<N; i++)
    {
        int t;
        cin >> t;
        nList.push_back(t);
    }

    BinaryTRIE sBinTrie;
    sBinTrie.buildBinaryTrie(nList);

    vector<ll> iQueries;
    for (int j=0; j<Q; j++)
    {
        ll k;
        cin >> k;
        iQueries.push_back(k);
    }

    for (auto q : iQueries)
    {
        ll element = 0;
        ll result = sBinTrie.computeMaximumXOR(q, element);
        cout << "Maximum XOR value is " << q << " XOR " << element << " : " << result << endl;
    }
}
