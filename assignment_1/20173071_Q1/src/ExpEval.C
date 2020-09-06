

#include "Exp.H"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[])
{
    // reading the infix expression
    string sExpStr = "(4+5.6)/3.2+(4+3.888)";
    //cout << "Enter your expression:" << endl;
    //getline(cin, sExpStr);

    Exp sExp(sExpStr);
    double sResult = sExp.evaluate(); // evaluate the expresion
    cout << "Result: " << sResult << endl;
}


/*
int main(int argc, char* argv[])
{
    cout << "Evaluating Expression Queue" << endl;
    ExpQueue sExpQueue;
    string inputStr("5+6");
    sExpQueue.enqueue("5");
    sExpQueue.enqueue("+");
    sExpQueue.enqueue("6");
    sExpQueue.print();
    cout << sExpQueue.dequeue() << endl;
    cout << sExpQueue.dequeue() << endl;
    sExpQueue.print();
    return 0;
}*/
