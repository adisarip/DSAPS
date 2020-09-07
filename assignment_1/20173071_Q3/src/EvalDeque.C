
#include "Deque.H"
#include <iostream>
using namespace std;

int main (int argc, char* argv[])
{
    Deque<int> deque(10, 5);
    deque.print();
    return 0;
}
