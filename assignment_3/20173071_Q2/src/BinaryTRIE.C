

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

void BinaryTRIE::buildBinaryTrie(vector<uint64_t>& a)
{
    // insert the input array into the TRIE in binary format
    for (auto x : a)
    {
        pInsert(x);
    }
}

uint64_t BinaryTRIE::computeMaximumXOR(uint64_t key, uint64_t& element)
{
    Node* sNode = root;
    for (uint64_t i = SIZE-1; i > 0; i--)
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

void BinaryTRIE::pInsert(uint64_t value)
{
    Node* sNode = root;
    // insert the numbers in bitwise format into the TRIE
    // starting with the Most-Significant-Bit
    for (uint64_t i = SIZE-1; i > 0; i--)
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
