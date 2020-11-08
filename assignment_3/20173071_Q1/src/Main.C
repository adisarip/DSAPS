

#include "SuffixArray.H"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    string s("banana$");
    SuffixArray s_array(s);
    s_array.display();
    s_array.displayRotations();
    cout << "Q1a: Smallest Lexicographical Rotation of 'banana' : " << s_array.getSmallestRotation() << endl;
    cout << "Q1b: Longest Substring appearing atleast '3' times : " << s_array.getLongestKSubstring(3) << endl;
    cout  << endl;
    return 0;
}
