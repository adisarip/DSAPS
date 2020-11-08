

#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include "SuffixTree.H"
#include <map>
using namespace std;

class SuffixArray : public SuffixTree
{
  public:
    SuffixArray(string textInput);
    ~SuffixArray();

    void display();

    // string utilities using suffix array
    string getSmallestRotation();
    string getLongestKSubstring(int k);
    string getLongestPalindomicSubstring();

  protected:
    // Build the suffix array
    void pBuildSuffixArray();
    // perform A DFS traversal
    void pDoComputeArrayUsingDFS(Node* node, int *index);

    // data
    int size;
    int* sArray;
    map<int, string> sArrayStrings;
};



#endif
