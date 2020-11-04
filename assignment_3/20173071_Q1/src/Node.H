
// A node in the Suffix Tree

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

const int MAX_CHAR_SET = 100; // ASCII character set range is -> 0x00 to 0x5F

class Node
{
  public:
    int start;
    int end;
    int suffixIndex;
    Node* suffixLink;
    Node* child[MAX_CHAR_SET];

    Node(int startIndex, int endIndex, Node* node = NULL);
    ~Node(){};
};

Node::Node(int startIndex, int endIndex, Node* node)
:start(startIndex)
,end(endIndex)
,suffixIndex(-1)
,suffixLink(node)
{
    for (int i=0; i < MAX_CHAR_SET; i++)
    {
        child[i] = NULL;
    }
}

#endif // NODE_H
