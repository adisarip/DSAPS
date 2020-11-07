

#include "BinaryTRIE.H"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    vector<ll> nList;
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


    vector<ll> iQueries;
    for (int j=0; j<Q; j++)
    {
        ll k;
        cin >> k;
        iQueries.push_back(k);
    }

    for (auto q : iQueries)
    {
        ll element = 0;
        ll result = sBinTrie.computeMaximumXOR(q, element);
        cout << "Maximum XOR value is " << q << " XOR " << element << " : " << result << endl;
    }
}
