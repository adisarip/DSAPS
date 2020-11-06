

#include "BinaryTRIE.H"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    vector<uint64_t> nList;
    int N = 0;
    int Q = 0;

    cin >> N >> Q;
    for (int i=0; i<N; i++)
    {
        int t;
        cin >> t;
        nList.push_back(t);
    }

    BinaryTRIE sBinTrie;
    sBinTrie.buildBinaryTrie(nList);


    vector<uint64_t> iQueries;
    for (int j=0; j<Q; j++)
    {
        uint64_t k;
        cin >> k;
        iQueries.push_back(k);
    }

    for (auto q : iQueries)
    {
        uint64_t element = 0;
        uint64_t result = sBinTrie.computeMaximumXOR(q, element);
        cout << "Maximum XOR value is " << q << " XOR " << element << " : " << result << endl;
    }
}
