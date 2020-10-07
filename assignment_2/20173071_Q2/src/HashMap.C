

// Test the functionality of the Unordered Map

#include "HashMap.H"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[])
{
    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Testing Unordered Map (HashMap) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    string aditya = "Aditya";
    string laasya = "Laasya";
    string lahari = "Lahari";
    string anusha = "Anusha";
    string chandu = "Chandu";
    string vishwa = "Vishwanath";

    HashMap<string, int> sHashMap(aditya, 1984);
    sHashMap[laasya] = 1990;
    cout << "HASHMAP[Lahari] = " << sHashMap[lahari] << endl;
    cout << "SIZE() = " << sHashMap.size() << endl;
    sHashMap.insert(lahari, 1994);
    sHashMap.insert(anusha, 1990);
    sHashMap[chandu] = 1984;
    sHashMap[vishwa] = 1981;
    cout << "HASHMAP[Lahari] = " << sHashMap.fetch(lahari) << endl;
    cout << "HASHMAP[Anusha] = " << sHashMap.fetch(anusha) << endl;
    cout << "SIZE() = " << sHashMap.size() << endl;
    sHashMap.print();
    cout << "\nErasing Chandu ...\n" << endl;
    sHashMap.erase(chandu);
    sHashMap.print();
    cout << endl;
    cout << "FIND(Lahari) = " << sHashMap.find(lahari) << endl;
    cout << "FIND(Aditya) = " << sHashMap.find(aditya) << endl;
    cout << "FIND(Chandu) = " << sHashMap.find(chandu) << endl;
    cout << "SIZE() = " << sHashMap.size() << endl;
    cout << endl;
    cout << "Updating data in HasMap ...\n" << endl;
    sHashMap.insert(aditya, 1994);
    sHashMap.insert(laasya, 2004);
    sHashMap.insert(lahari, 2002);
    sHashMap.insert(string("ashuna"), 1987);
    sHashMap.insert(aditya, 2006);
    sHashMap.print();
    return 0;
}
