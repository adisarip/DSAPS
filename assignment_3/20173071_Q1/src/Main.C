

#include "SuffixTree.H"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    string s("banana$");
    SuffixTree suffix_tree(s);
    cout << "Building Suffix Tree for: " << s << endl;
    suffix_tree.buildTree();
    cout << "Building Suffix Tree Completed." << endl;

    int size = s.length() - 1;
    int* array = new int[size];
    suffix_tree.buildSuffixArray(array);
    return 0;
}
