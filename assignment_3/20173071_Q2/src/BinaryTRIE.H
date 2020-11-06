
// A Trie Data Structure implementation for XOR computations

#ifndef BINARYTRIE_H
#define BINARYTRIE_H

#include <iostream>
#include <vector>
using namespace std;

class Node
{
  public:
    Node():leafValue(0)
    {
        child[0] = NULL;
        child[1] = NULL;
    }
    ~Node(){};

    // data
    uint64_t leafValue;
    Node* child[2];
};

class BinaryTRIE
{
  public:
    BinaryTRIE();
    ~BinaryTRIE();

    void buildBinaryTrie(vector<uint64_t>& a);
    uint64_t computeMaximumXOR(uint64_t key, uint64_t& element);

  protected:
    void pInsert(uint64_t x); // insert a number in binary format into the TRIE data structure


  protected:
    Node* root;
};

#endif
