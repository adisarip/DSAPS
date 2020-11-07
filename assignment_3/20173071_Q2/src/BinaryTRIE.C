

#include "BinaryTRIE.H"
using namespace std;

const int SIZE = 64; // 8 bytes - 64-bit

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
