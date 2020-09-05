

#include "Exp.H"
#include "ExpStack.H"
using namespace std;

Exp::Exp(string expStrParm)
:mExpStr(expStrParm)
,mInfixExp(nullptr)
,mPostfixExp(nullptr)
{
    pCreateInfixExp();
}

Exp::~Exp()
{
    mInfixExp->clear();
    mPostfixExp->clear();
    mInfixExp = nullptr;
    mPostfixExp = nullptr;
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
    return 0;
}

// helper functions for evaluating expressions
void Exp::pCreateInfixExp()
{
}

void Exp::pConvertToPostfix()
{
}
