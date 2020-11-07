
// A Trie Data Structure implementation for XOR computations

#ifndef BINARYTRIE_H
#define BINARYTRIE_H

#include <iostream>
#include <vector>
using namespace std;

#define ll long long

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

#endif
