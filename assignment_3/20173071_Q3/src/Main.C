
#include "ExtSort.H"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "[Error] Input File Missing !!!" << endl;
        return 0;
    }

    string input_file = argv[1];
    string output_file = "./data/sorted_output.txt";
    ExtSort data(input_file, output_file, 10000);
    data.sort();
    return 0;
}
