
// SuffixArray class derived from SuffixTree

#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include "SuffixTree.H"
#include <map>
#include <vector>
using namespace std;

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
    void getLongestPalindomicSubstring();

  protected:
    string pGetSubstring(int xsize, int& count);
    void pRebuildSuffixArray(string x);
    bool pIsPalindrome(string x);
    string pGetCommonPrefix(int index);
    void pGetPalindromicSubstring();
    // Build the suffix array
    void pBuildSuffixArray();
    // perform A DFS traversal
    void pDoComputeArrayUsingDFS(Node* node, int& index);

    // data
    int size;
    int* sArray;
    map<int, string> mRotations;
    map<int, string> mSuffixes;
    vector<string> mPalindromes;
};



#endif
