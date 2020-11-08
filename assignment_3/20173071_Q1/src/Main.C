

#include "SuffixArray.H"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    string s("banana$");
    SuffixArray s_array(s);
    s_array.display();
    cout << "Smallest Lexicographical Rotation of 'banana' : " << s_array.getSmallestRotation() << endl;
    return 0;
}
