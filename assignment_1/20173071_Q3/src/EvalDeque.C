
#include "Deque.H"
#include <iostream>
using namespace std;

int main (int argc, char* argv[])
{
    Deque<int> deque(10, 5);
    deque.print();
    deque.push_back(10);
    deque.push_back(15);
    deque.push_back(16);
    deque.print();
    deque.resize(20, 0);
    deque.print();
    deque.resize(13, 0);
    deque.print();
    deque.resize(20, 0, FORWARD);
    deque.print();
    deque.resize(13, 0, FORWARD);
    deque.print();
    cout << deque[0] << endl;
    cout << deque[-1] << endl;
    cout << deque[-3] << endl;
    cout << deque[-14] << endl;
    cout << deque[13] << endl;
    deque.pop_back();
    deque.pop_back();
    deque.pop_back();
    deque.print();
    deque.push_front(10);
    deque.push_front(15);
    deque.push_front(16);
    deque.print();
    deque.pop_front();
    deque.pop_front();
    deque.pop_front();
    deque.print();
    cout << deque.front() << endl;
    cout << deque.back() << endl;
    cout << deque.size() << endl;
    return 0;
}
