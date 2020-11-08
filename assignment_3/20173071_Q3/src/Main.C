
#include "ExtSort.H"
#include <iostream>
#include <fstream>
using namespace std;

void printHelp()
{
    cout << "USAGE:" << endl;
    cout << "      ./bin/esort <input_file> <output_file> [partion_size]" << endl;
    cout << "Ex:   ./bin/esort ./data/input.txt ./data/sorted_input.txt" << endl;
    cout << "Ex:   ./bin/esort ./data/input.txt ./data/sorted_input.txt 20" << endl;
    cout << "NOTE: partion_size is the maximum number of elements that each partition will have." << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "[Error] Invalid Command !!!" << endl;
        printHelp();
        return 1;
    }

    string input_file  = argv[1];
    string output_file = argv[2];
    int partion_size = (argc == 4) ? stoi(argv[3]) : 1000;
    ExtSort data(input_file, output_file, partion_size);
    data.sort();
    data.cleanup();
    return 0;
}
