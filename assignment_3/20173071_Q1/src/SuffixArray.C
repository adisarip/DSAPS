

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
    map<string, int> sRepeatedStrings;
    for (int i=0; i<size; i++)
    {
        string str = mRotations[i].substr(0,k);
        sRepeatedStrings[str]++;
    }

    int max_count = 0;
    string max_string = "";
    map<string, int>::iterator it;
    for (it = sRepeatedStrings.begin(); it != sRepeatedStrings.end(); it++)
    {
        if (max_count < it->second)
        {
            max_count = it->second;
            max_string = it->first;
        }
    }
    return max_string;
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
