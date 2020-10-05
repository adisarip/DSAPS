// Test the functionality of the Ordered Map

#include "Map.H"
#include <iostream>
using namespace std;


int main (int argc, char* argv[])
{
    cout << ">>>> Testing Ordered Map <<<<" << endl;
    Map<int> sMap;
    sMap.insert(0, 40);
    sMap.insert(1, 20);
    sMap.insert(2, 60);
    sMap.insert(3, 10);
    sMap.insert(4, 5);
    sMap.insert(5, 15);
    sMap.insert(6, 55);
    sMap.insert(7, 65);
    sMap.insert(8, 75);
    sMap.insert(9, 32);
    sMap.insert(10, 12);
    sMap.display();
}
