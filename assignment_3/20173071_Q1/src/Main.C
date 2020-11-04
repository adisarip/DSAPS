

#include "SuffixTree.H"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    SuffixTree st(string("abbc"));
    st.buildTree();
    st.displayTree();
    cout << "Number of nodes in suffix tree are " << st.getNodesCount() << endl;
    return 0;
}
