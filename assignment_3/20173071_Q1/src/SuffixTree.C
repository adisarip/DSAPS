
// Implementation


#include "SuffixTree.H"
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

void SuffixTree::clear()
{
    pDeleteNode(root);
}

void SuffixTree::buildTree()
{
    // create the root node
    root = new Node(-1, -1); // Root Node (startIndex, endIndex) = (-1, -1)
    activeNode = root;

    for (int i=0; i < getStringLength(); i++)
    {
        pExtendSuffixTree(i);
    }
    pSetSuffixIndex(root);
}

void SuffixTree::displayTree()
{
}

// Protected member definitions

void SuffixTree::pSetSuffixIndex(Node* node, int index)
{
    // perform a DFS to set the suffix indices of all the nodes
    if (NULL == node)
    {
        return;
    }

    int isLeafNode = true;
    for (int i=0; i < ALPHABET; i++)
    {
        if (NULL != node->child[i])
        {
            isLeafNode = false;
            pSetSuffixIndex(node->child[i], index + getEdgeLength(node->child[i]));
        }
    }
    if (isLeafNode)
    {
        node->suffixIndex = getStringLength() - index;
    }
}

void SuffixTree::pExtendSuffixTree(int position)
{
}

int SuffixTree::pTraverse(Node* currentNode)
{
    return 0;
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
