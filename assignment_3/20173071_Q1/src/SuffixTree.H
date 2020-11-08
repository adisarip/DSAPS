
// Implementation of Suffix Tree using Ukkonen Algorithm
// References: http://web.stanford.edu/~mjkay/gusfield.pdf
//             https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf

#ifndef SUFFIXTREE_H
#define SUFFIXTREE_H

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
    //void buildSuffixArray(int arr[]);

  protected:
    int pGetID(int position);
    void pSetSuffixIndex(Node* node, int index=0);
    void pExtendSuffixTree(int position);
    SuffixTree::ActivePointStatus pUpdateActivePoint(Node* currentNode);
    //void pDoTraversalDFS(Node* node, int arr[], int *index);
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

#endif //SUFFIXTREE_H
