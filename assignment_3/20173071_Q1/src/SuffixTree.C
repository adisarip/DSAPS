
// Implementation


#include "SuffixTree.H"
#include <iostream>
#include <string>
using namespace std;

SuffixTree::SuffixTree()
:root(NULL)
,internalNode(NULL)
,activeNode(NULL)
,activeEdge(-1)
,activeLength(0)
,suffixCount(0)
,nodesCount(0)
,inputString("")
{
}

SuffixTree::SuffixTree(string textInput)
:root(NULL)
,internalNode(NULL)
,activeNode(NULL)
,activeEdge(-1)
,activeLength(0)
,suffixCount(0)
,nodesCount(0)
,inputString(textInput)
{
}

SuffixTree::~SuffixTree()
{
    // delete all the nodes from the Suffix Tree
    clear();
}

int SuffixTree::getEdgeLength(Node* node)
{
    return (node->end - node->start + 1);
}

int SuffixTree::getStringLength()
{
    return inputString.length();
}

void SuffixTree::clear()
{
    pDeleteNode(root);
}

void SuffixTree::buildTree()
{
}

void SuffixTree::displayTree()
{
}

// Protected member definitions

Node* SuffixTree::pCreateNode(int startIndex, int endIndex)
{
    return NULL;
}

int SuffixTree::pTraverse(Node* currentNode)
{
    return 0;
}

void SuffixTree::pExtendSuffixTree(int position)
{
}

void SuffixTree::pDeleteNode(Node* node)
{
    // algorithm for deleting the nodes.
    if (node == NULL)
    {
        return;
    }

    for (int i=0; i < ALPHABET; i++)
    {
        if (node->child[i] != NULL)
        {
            pDeleteNode(node);
        }
    }
    delete(node);
}
