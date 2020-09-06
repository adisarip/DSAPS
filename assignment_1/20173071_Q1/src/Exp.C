

#include "Exp.H"
#include "ExpStack.H"
#include <iostream>
using namespace std;

Exp::Exp(string expStrParm)
:mExpStr(expStrParm)
{
    mInfixExp = new ExpQueue();
    mPostfixExp = new ExpQueue();
}

Exp::~Exp()
{
    mInfixExp->clear();
    mPostfixExp->clear();
    mInfixExp = NULL;
    mPostfixExp = NULL;
}

// Setter/getter methods
void Exp::setExpString(string expStrParm)
{
    mExpStr = expStrParm;
}

string Exp::getExpString()
{
    return mExpStr;
}

double Exp::evaluate()
{
    // creating tokenized infix expression
    pTokenizeExp();
    return 0;
}

// helper functions for evaluating expressions
void Exp::pTokenizeExp()
{
    string sInfixToken("");
    int sExpSize = mExpStr.length();
    int i = 0;
    for (; i<sExpSize-1; i++)
    {
        char c = mExpStr.at(i);
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
            c == '(' || c == ')')
        {
            sInfixToken = string(1,c);
            mInfixExp->enqueue(sInfixToken);
            sInfixToken = "";
        }
        else
        {
            sInfixToken += string(1,c);
            if (!((mExpStr.at(i+1) >= '0' && mExpStr.at(i+1) <= '9') || mExpStr.at(i+1) == '.'))
            {
                mInfixExp->enqueue(sInfixToken);
                sInfixToken = "";
            }
        }
    }

    if ((mExpStr.at(i) >= '0' && mExpStr.at(i) <= '9') || mExpStr.at(i) == '.')
    {
        sInfixToken += mExpStr[sExpSize-1];
    }
    else
    {
        sInfixToken = mExpStr[sExpSize-1];
    }
    mInfixExp->enqueue(sInfixToken);
    mInfixExp->print();
}

void Exp::pConvertToPostfix()
{
}
