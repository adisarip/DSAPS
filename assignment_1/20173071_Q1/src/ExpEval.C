

#include "Exp.H"
#include <iostream>
#include <string>
using namespace std;

/*
int main (int argc, char* argv[])
{
    // reading the infix expression
    string sExpStr;
    cout << "Enter your expression:" << endl;
    getline(cin, sExpStr);

    Exp sExp(sExpStr);
    double sResult = sExp.evaluate(); // evaluate the expresion
    cout << "Result: " << sResult << endl;
}
*/



int main(int argc, char* argv[])
{
    cout << "Evaluating Expression Queue" << endl;
    ExpQueue sExpQueue;
    sExpQueue.print();
    sExpQueue.enqueue("(");
    sExpQueue.enqueue("a");
    sExpQueue.enqueue("+");
    sExpQueue.enqueue("b");
    sExpQueue.enqueue(")");
    sExpQueue.print();
    cout << sExpQueue.dequeue() << endl;
    cout << sExpQueue.dequeue() << endl;
    cout << sExpQueue.dequeue() << endl;
    cout << sExpQueue.dequeue() << endl;
    sExpQueue.print();
    return 0;
}
