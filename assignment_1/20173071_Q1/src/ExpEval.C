

#include "Expression.H"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[])
{
    // reading the infix expression
    string sExpStr;
    cout << "Enter your expression:" << endl;
    getline(cin, sExpStr);

    Expression sExpression(sExpStr);
    double sResult = sExpression.evaluate(); // evaluate the expresion
    cout << "Result: " << sResult << endl;
}
