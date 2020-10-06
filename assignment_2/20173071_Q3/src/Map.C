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
    sMap.print();
    sMap.insert(3, 100);
    sMap.insert(5, 200);
    sMap.display();
    sMap.erase(5);
    sMap.erase(7);
    sMap.display();
    cout << "SIZE() = " << sMap.size() << endl;
    sMap.insert(5, 15);
    sMap.insert(7, 65);
    sMap.display();
    sMap.print();
    cout << "FIND(4) = " << sMap.find(4) << endl;
    cout << "FIND(9) = " << sMap.find(9) << endl;
    cout << "FIND(20) = " << sMap.find(20) << endl;
    cout << "SIZE() = " << sMap.size() << endl;
    cout << "SIZE() = " << sMap.size() << endl;
    cout << "MAP[4] = " << sMap[4] << endl;
    cout << "MAP[9] = " << sMap[9] << endl;
    cout << "MAP[20] = " << sMap[20] << endl;
    sMap.print();
    cout << "Modifying values at '4' and '9'. Adding '20'" << endl;
    sMap[4] = 100;
    sMap[9] = 200;
    sMap[20] = 500;
    cout << "MAP[4] = " << sMap[4] << endl;
    cout << "MAP[9] = " << sMap[9] << endl;
    cout << "MAP[20] = " << sMap[20] << endl;
    sMap.display();
    sMap.print();
    sMap.clear();
}
