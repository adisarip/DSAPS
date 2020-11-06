// Implementation


#include "Node.H"
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
    return (node->end - node->start + 1);
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
    root = new Node(-1, -1); // Root Node (startIndex, endIndex) = (-1, -1)
    activeNode = root;

    cout << "buildTree(): 1" << endl;
    for (int i=0; i < getStringLength(); i++)
    {
        cout << "buildTree(): 2." << i << endl;
        pExtendSuffixTree(i);
    }
    cout << "buildTree(): 3" << endl;
    pSetSuffixIndex(root);
    cout << "buildTree(): 4" << endl;
}

void SuffixTree::displayTree()
{
    pDisplay(root);
}

void SuffixTree::pDisplay(Node* node, int index)
{
    if (NULL == node)
    {
        return;
    }
    if (node->start != -1)
    {
        for (int i = node->start; i <= node->end; i++)
        {
            cout << inputString[i];
        }
    }
    int isLeafNode = true;
    for (int i=0; i < MAX_CHAR_SET; i++)
    {
        if (NULL != node->child[i])
        {
            if (isLeafNode && node->start != -1)
            {
                cout << " [" << node->suffixIndex  << "]" << endl;
            }
            isLeafNode = false;
            pDisplay(node->child[i], index + getEdgeLength(node->child[i]));
        }
    }
    if (isLeafNode)
    {
        cout << " [" << node->suffixIndex  << "]" << endl;
    }
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
        activeEdge = (int) inputString[activeEdge + sEdgeLength] - (int)' ';
        activeLength = activeLength - sEdgeLength;
        activeNode = currentNode;
        sStatus = SuffixTree::ActivePointChanged;
    }
    return sStatus;
}

int SuffixTree::pGetCharacterID(int position)
{
    return (int)inputString[position] - (int)' '; // returning ASCII value of the character
}

void SuffixTree::pExtendSuffixTree(int position)
{
    suffixCount++;
    int leafEnd = position;
    cout << "pExtendSuffixTree():1: " << position << endl;
    while (suffixCount > 0)
    {
        if (activeLength == 0)
        {
            activeEdge = pGetCharacterID(position);
        }
        cout << "pExtendSuffixTree():2.0: " << suffixCount << ": " << inputString[position] << endl;

        if (activeNode == NULL)
        {
            cout << "activeNode is NULL" << endl;
            break;
        }

        if (activeNode->child[activeEdge] == NULL)
        {
            // Extension Rule-2
            cout << "pExtendSuffixTree():2.1: " << suffixCount << endl;
            activeNode->child[activeEdge] = new Node(position, leafEnd);
            if (internalNode != NULL)
            {
                cout << "pExtendSuffixTree():2.2: " << suffixCount << endl;
                internalNode->suffixLink = activeNode;
                internalNode = NULL;
            }
            cout << "pExtendSuffixTree():2.3: " << suffixCount << endl;
        }
        else
        {
            cout << "pExtendSuffixTree():2.4.1: " << suffixCount << endl;
            Node* next = activeNode->child[activeEdge];
            cout << "pExtendSuffixTree():2.4.2: " << suffixCount << endl;
            if (pUpdateActivePoint(next))
            {
                continue; // start from the next internal node
            }
            cout << "pExtendSuffixTree():2.5: " << suffixCount << endl;

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
            cout << "pExtendSuffixTree():2.6: " << suffixCount << endl;

            // Split the edge for creating new nodes
            int splitEndIndex = next->start + activeLength - 1;
            Node* splitNode = new Node(next->start, splitEndIndex);
            activeNode->child[activeEdge] = splitNode;

            // new leaf node coming out of internal node
            splitNode->child[pGetCharacterID(position)] = new Node(position, leafEnd);

            next->start = next->start + activeLength;
            splitNode->child[activeEdge] = next;
            if (internalNode != NULL)
            {
                internalNode->suffixLink = splitNode;
            }
            internalNode = splitNode;
        }
        cout << "pExtendSuffixTree():3: " << suffixCount << endl;
        suffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pGetCharacterID(position - suffixCount + 1);
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
        cout << "pExtendSuffixTree():4: " << suffixCount << endl;
    }
}


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
