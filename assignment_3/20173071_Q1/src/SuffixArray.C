

#include "SuffixArray.H"
#include <iostream>
using namespace std;

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
    for (int x=0; x<size; x++)
    {
        cout << x << " : " << sArrayStrings[x] << endl;
    }
}

string SuffixArray::getSmallestRotation()
{
    return sArrayStrings[sArray[0]];
}

string SuffixArray::getLongestKSubstring(int k)
{
    string result = "";
    return result;
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
    pDoComputeArrayUsingDFS(root, &index);

    string str = inputString.substr(0, size);
    for (int i=0; i<size; i++)
    {
        int index = sArray[i];
        string aStr = str.substr(index, size - index) + str.substr(0, index);
        sArrayStrings[index] = aStr;
    }
}

void SuffixArray::pDoComputeArrayUsingDFS(Node* node, int* index)
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
        sArray[(*index)++] = node->suffixIndex;
    }
}
