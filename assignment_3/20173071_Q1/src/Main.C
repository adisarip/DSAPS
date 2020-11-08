

#include "SuffixArray.H"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Input String Missing !!!" << endl;
        cout << "Usage: ./bin/scomp <input_string>" << endl;
        return 1;
    }

    string s = string(argv[1]) + string("$");
    SuffixArray s_array(s);
    s_array.display();
    //s_array.displaySuffixes();
    //s_array.displayRotations();
    cout << "Q1a: Smallest Lexicographical Rotation of '" << argv[1] << "' : " << s_array.getSmallestRotation() << endl;
    int k=2;
    string x = s_array.getLongestKSubstring(k);
    int xsize = (x.length() > 0) ? x.length() : -1;
    cout << "Q1b: Longest Substring appearing atleast '" << k << "' times : " << x << " | size=" << xsize << endl;
    k=3;
    x = s_array.getLongestKSubstring(k);
    xsize = (x.length() > 0) ? x.length() : -1;
    cout << "Q1b: Longest Substring appearing atleast '" << k << "' times : " << x << " | size=" << xsize << endl;
    k=4;
    x = s_array.getLongestKSubstring(k);
    xsize = (x.length() > 0) ? x.length() : -1;
    cout << "Q1b: Longest Substring appearing atleast '" << k << "' times : " << x << " | size=" << xsize << endl;
    return 0;
}
