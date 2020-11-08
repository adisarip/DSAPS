// Implementation


#include "SuffixTree.H"
#include <iostream>
using namespace std;

Node::Node(int startIndex, int* endIndex, Node* node)
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

SuffixTree::SuffixTree()
:root(NULL)
,internalNode(NULL)
,activeNode(NULL)
,activeEdge(-1)
,activeLength(0)
,suffixCount(0)
,nodesCount(0)
,inputString("")
,leafEnd(-1)
,rootEnd(NULL)
,splitEnd(NULL)
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
,leafEnd(-1)
,rootEnd(NULL)
,splitEnd(NULL)
{
}

SuffixTree::~SuffixTree()
{
    // delete all the nodes from the Suffix Tree
    //clear();
}

void SuffixTree::setInputString(string str)
{
    inputString = str;
}

string SuffixTree::getInputString()
{
    return inputString;
}

int SuffixTree::getStringLength()
{
    return inputString.length();
}

int SuffixTree::getEdgeLength(Node* node)
{
    int length = 0;
    if (node != root)
    {
        length = *(node->end) - (node->start) + 1;
    }
    return length;
}

int SuffixTree::getNodesCount()
{
    return nodesCount;
}

void SuffixTree::clear()
{
    pDeleteNode(root);
}

void SuffixTree::buildTree()
{
    // create the root node
    rootEnd = new int(-1);
    root = new Node(-1, rootEnd); // Root Node (startIndex, endIndex) = (-1, -1)
    activeNode = root;

    for (int i=0; i < getStringLength(); i++)
    {
        pExtendSuffixTree(i);
    }
    pSetSuffixIndex(root, 0);
}

// Protected member definitions

int SuffixTree::pGetID(int position)
{
    return (int)inputString[position] - (int)' '; // returning ASCII value of the character
}

void SuffixTree::pExtendSuffixTree(int position)
{
    leafEnd = position;
    internalNode = NULL;
    suffixCount++;

    while (suffixCount > 0)
    {
        if (activeLength == 0)
        {
            activeEdge = position;
        }

        if (activeNode->child[pGetID(activeEdge)] == NULL)
        {
            activeNode->child[pGetID(activeEdge)] = new Node(position, &leafEnd);
            if (internalNode != NULL)
            {
                internalNode->suffixLink = activeNode;
                internalNode = NULL;
            }
        }
        else
        {
            Node* next = activeNode->child[pGetID(activeEdge)];
            if (SuffixTree::ActivePointChanged == pUpdateActivePoint(next))
            {
                continue; // start from the next internal node
            }

            if (inputString[next->start + activeLength] == inputString[position])
            {
                if (internalNode != NULL && activeNode != root)
                {
                    internalNode->suffixLink = activeNode;
                    internalNode = NULL;
                }
                activeLength++;
                break; // stop processing after Rule-3
            }

            // Split the edge for creating new nodes
            splitEnd = new int;
            *splitEnd = next->start + activeLength - 1;
            Node* splitNode = new Node(next->start, splitEnd);
            activeNode->child[pGetID(activeEdge)] = splitNode;

            // new leaf node coming out of internal node
            splitNode->child[pGetID(position)] = new Node(position, &leafEnd);
            next->start += activeLength;
            splitNode->child[pGetID(next->start)] = next;

            if (internalNode != NULL)
            {
                internalNode->suffixLink = splitNode;
            }
            internalNode = splitNode;
        }
        suffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = position - suffixCount + 1;
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

void SuffixTree::pSetSuffixIndex(Node* node, int index)
{
    // perform a DFS to set the suffix indices of all the nodes
    if (NULL == node)
    {
        return;
    }

    int isLeafNode = true;
    for (int i=0; i < MAX_CHAR_SET; i++)
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

SuffixTree::ActivePointStatus SuffixTree::pUpdateActivePoint(Node* currentNode)
{
    SuffixTree::ActivePointStatus sStatus = SuffixTree::ActivePointUnchanged;
    int sEdgeLength = getEdgeLength(currentNode);
    if (activeLength >= sEdgeLength)
    {
        activeEdge += sEdgeLength;
        activeLength -= sEdgeLength;
        activeNode = currentNode;
        sStatus = SuffixTree::ActivePointChanged;
    }
    return sStatus;
}

/*
void SuffixTree::buildSuffixArray(int arr[])
{
    int size = getStringLength() - 1;
    for (int i=0; i < size; i++)
    {
        arr[i] = -1;
    }
    int index = 0;
    pDoTraversalDFS(root, arr, &index);
    cout << inputString << ":";
    for (int i=0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void SuffixTree::pDoTraversalDFS(Node* node, int arr[], int *index)
{
    int size = getStringLength() - 1;
    if (node == NULL)
    {
        return;
    }
    if (node->suffixIndex == -1)
    {
        for (int i=0; i < MAX_CHAR_SET; i++)
        {
            if (node->child[i] != NULL)
            {
                pDoTraversalDFS(node->child[i], arr, index);
            }
        }
    }
    else if (node->suffixIndex > -1 && node->suffixIndex < size)
    {
        arr[(*index)++] = node->suffixIndex;
    }
}
*/

void SuffixTree::pDeleteNode(Node* node)
{
    // algorithm for deleting the nodes.
    if (node == NULL)
    {
        return;
    }

    for (int i=0; i < MAX_CHAR_SET; i++)
    {
        if (node->child[i] != NULL)
        {
            pDeleteNode(node);
        }
    }
    delete(node);
}
