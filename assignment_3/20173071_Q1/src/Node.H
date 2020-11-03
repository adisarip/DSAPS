
// A node in the Suffix Tree

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

const int ALPHABET = 26;

class Node
{
  public:
    int start;
    int end;
    int suffixIndex;
    Node* suffixLink;
    Node* child[ALPHABET];

    Node(int startIndex, int endIndex, Node* node = NULL);
    ~Node();
};

Node::Node(int startIndex, int endIndex, Node* node)
:start(startIndex)
,end(endIndex)
,suffixIndex(-1)
,suffixLink(node)
{
    for (int i=0; i < ALPHABET; i++)
    {
        child[i] = NULL;
    }
}

#endif // NODE_H
