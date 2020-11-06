

#include "SuffixTree.H"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    string s("abbc");
    SuffixTree st(s);
    cout << "Building Suffix Tree for: " << s << endl;
    st.buildTree();
    cout << "Building Suffix Tree Completed." << endl;
    st.displayTree();
    cout << "Number of nodes in suffix tree are " << st.getNodesCount() << endl;
    return 0;
}
