

// Test the functionality of the Unordered Map

#include "HashMap.H"
#include <iostream>
using namespace std;

int main (int argc, char* argv[])
{
    cout << ">>>> Testing Unordered Map (HashMap) <<<<" << endl;
    HashMap<int, int> sHashMap(3, 100);
    cout << sHashMap[3] << endl;
    sHashMap[4] = 200;
    cout << sHashMap[4] << endl;
    cout << sHashMap[5] << endl;
    return 0;
}
