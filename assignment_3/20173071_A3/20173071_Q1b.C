

// Implementation of Suffix Array using Suffix Tree construction based on Ukkonen Algorithm
// References: http://web.stanford.edu/~mjkay/gusfield.pdf
//             https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf

#include <iostream>
#include <map>
#include <string>
using namespace std;

const int MAX_CHAR_SET = 100; // ASCII character set range is -> 0x00 to 0x5F

class Node
{
  public:
    int start;
    int *end;
    int suffixIndex;
    Node* suffixLink;
    Node* child[MAX_CHAR_SET];

    Node(int startIndex, int* endIndex, Node* node = NULL);
    ~Node(){};
};


class SuffixTree
{
  public:

    SuffixTree();
    SuffixTree(string textInput);
    ~SuffixTree();

    enum ActivePointStatus
    {
        ActivePointUnchanged = 0,
        ActivePointChanged   = 1,
    };

    // getter setter members
    void setInputString(string str);
    string getInputString();
    int getStringLength();
    int getEdgeLength(Node* node);
    int getNodesCount();

    // public interface
    void clear();
    void buildTree();

  protected:
    int pGetID(int position);
    void pSetSuffixIndex(Node* node, int index=0);
    void pExtendSuffixTree(int position);
    SuffixTree::ActivePointStatus pUpdateActivePoint(Node* currentNode);
    void pDeleteNode(Node* node);

    // Root Node of the Suffix Tree
    Node*  root;
     // Points to newly created internal node, waiting for its suffixLink to be set
    Node*  internalNode;
    // Active Point can be described using the following 3 variables.
    // This is the point where traversal starts in any extension.
    Node*  activeNode;   // Root Node or any internal Node.
    int    activeEdge;   // Will store information about which edge to choose while traversal (via internal nodes)
    int    activeLength; // How many characters we need to walk down (traverse)
    int    suffixCount;  // A count about how many suffixes yet to be added in the Tree
    int    nodesCount;   // Total number of nodes in the Suffix Tree
    string inputString;  // Input string for which we are creating the Suffix Tree
    // additonal data members for use
    int leafEnd;
    int* rootEnd;
    int* splitEnd;
};

// Class Implementation

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
    clear();
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
            pDeleteNode(node->child[i]);
        }
    }
    if (node->suffixIndex == -1)
    {
        delete(node->end);
    }
    delete(node);
}

// SuffixArray class derived from SuffixTree

class SuffixArray : public SuffixTree
{
  public:
    SuffixArray(string textInput);
    ~SuffixArray();
    void display();
    void displaySuffixes();
    void displayRotations();

    // string utilities using suffix array
    string getSmallestRotation();
    string getLongestKSubstring(int k);
    string getLongestPalindomicSubstring();

  protected:
    string pGetSubstring(int xsize, int& count);
    // Build the suffix array
    void pBuildSuffixArray();
    // perform A DFS traversal
    void pDoComputeArrayUsingDFS(Node* node, int& index);

    // data
    int size;
    int* sArray;
    map<int, string> mRotations;
    map<int, string> mSuffixes;
};


SuffixArray::SuffixArray(string textInput)
:SuffixTree(textInput)
{
    size = getStringLength() - 1;
    sArray = new int[size];
    pBuildSuffixArray();
}

SuffixArray::~SuffixArray()
{
    delete[] sArray;
}

void SuffixArray::display()
{
    string str = inputString.substr(0, size);
    cout << "Suffix Array for '" << str << "': ";
    for (int i=0; i < size; i++)
    {
        cout << sArray[i] << " ";
    }
    cout << endl;
}

void SuffixArray::displaySuffixes()
{
    string str = inputString.substr(0, size);
    cout << "\nAll Suffixes of the string '" << str << "':" << endl;
    for (int x=0; x<size; x++)
    {
        cout << x << " : " << mSuffixes[x] << endl;
    }
    cout << endl;
}

void SuffixArray::displayRotations()
{
    string str = inputString.substr(0, size);
    cout << "All Rotations of the string '" << str << "':" << endl;
    for (int x=0; x<size; x++)
    {
        cout << x << " : " << mRotations[x] << endl;
    }
    cout << endl;
}

string SuffixArray::getSmallestRotation()
{
    return mRotations[sArray[0]];
}

string SuffixArray::getLongestKSubstring(int k)
{
    if (k==1)
    {
        return inputString.substr(0, size);
    }

    int count = 0;
    string ms;
    for (int i=1; i<size-1; i++)
    {
        string s = pGetSubstring(i,count);
        if (count >= k)
        {
            ms = s;
            count = 0;
        }
        else
        {
            break;
        }
    }
    return ms;
}

string SuffixArray::pGetSubstring(int xsize, int& count)
{
    // xsize = size of the substring
    map<string, int> sRepeatedStrings;
    for (int i=0; i<size; i++)
    {
        string str = mRotations[i].substr(0,xsize);
        sRepeatedStrings[str]++;
    }

    string max_sub_string = "";
    map<string, int>::iterator it;
    for (it = sRepeatedStrings.begin(); it != sRepeatedStrings.end(); it++)
    {
        if (count < it->second)
        {
            count = it->second;
            max_sub_string = it->first;
        }
    }
    return max_sub_string;
}

string SuffixArray::getLongestPalindomicSubstring()
{
    string result = "";
    return result;
}

// Protected member definitions

void SuffixArray::pBuildSuffixArray()
{
    // Base class call
    buildTree();

    for (int i=0; i < size; i++)
    {
        sArray[i] = -1;
    }
    int index = 0;
    pDoComputeArrayUsingDFS(root, index);

    string str = inputString.substr(0, size);
    for (int i=0; i<size; i++)
    {
        int index = sArray[i];
        string x = str.substr(index, size - index);
        string y = str.substr(0, index);
        mRotations[index] = x+y;
        mSuffixes[index] = x;
    }
}

void SuffixArray::pDoComputeArrayUsingDFS(Node* node, int& index)
{
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
                pDoComputeArrayUsingDFS(node->child[i], index);
            }
        }
    }
    else if (node->suffixIndex > -1 && node->suffixIndex < size)
    {
        //sArray[(*index)++] = node->suffixIndex;
        sArray[index++] = node->suffixIndex;
    }
}

// ================================= Driver Program =================================

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Input String Missing !!!" << endl;
        cout << "Usage: ./bin/scomp <input_string>" << endl;
        return 1;
    }

    string s = string(argv[1]) + string("$");
    SuffixArray s_array(s);
    s_array.display();
    int k=2;
    string x = s_array.getLongestKSubstring(k);
    int xsize = (x.length() > 0) ? x.length() : -1;
    cout << "Q1b: Longest Substring appearing atleast '" << k << "' times : " << x << " | size=" << xsize << endl;
    k=3;
    x = s_array.getLongestKSubstring(k);
    xsize = (x.length() > 0) ? x.length() : -1;
    cout << "Q1b: Longest Substring appearing atleast '" << k << "' times : " << x << " | size=" << xsize << endl;
    k=4;
    x = s_array.getLongestKSubstring(k);
    xsize = (x.length() > 0) ? x.length() : -1;
    cout << "Q1b: Longest Substring appearing atleast '" << k << "' times : " << x << " | size=" << xsize << endl;
    return 0;
}
