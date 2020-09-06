

#include "Expression.H"
#include "ExpStack.H"
#include <iostream>
#include <cmath>
using namespace std;

Expression::Expression(string expStrParm)
:mExpStr(expStrParm)
{
    mInfixExp = new ExpQueue();
    mPostfixExp = new ExpQueue();
}

Expression::~Expression()
{
    mInfixExp->clear();
    mPostfixExp->clear();
    mInfixExp = NULL;
    mPostfixExp = NULL;
}

// Setter/getter methods
void Expression::setExpString(string expStrParm)
{
    mExpStr = expStrParm;
}

string Expression::getExpString()
{
    return mExpStr;
}

double Expression::evaluate()
{
    // creating tokenized infix expression
    pTokenizeExpression();

    // Convert infix to postfix
    pConvertToPostfix();

    // Evaluate postfix expression
    double result = pEvaluatePostfix();

    return result;
}

// helper functions for evaluating expressions
void Expression::pTokenizeExpression()
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
    cout << "Infix Expression:" << endl;
    mInfixExp->print();
    cout << endl;
}

int Expression::precedence(string tokenParm)
{
    int sPrecedence = 0;
    if (tokenParm == "*" || tokenParm == "/" || tokenParm == "%")
    {
        sPrecedence = 3;
    }
    else if (tokenParm == "+" || tokenParm == "-")
    {
        sPrecedence = 2;
    }
    else if (tokenParm == "(")
    {
        sPrecedence = 1;
    }
    return sPrecedence;
}

void Expression::pConvertToPostfix()
{
    ExpStack* sExpStack = new ExpStack();
    ExpQueue* sInfixExp = mInfixExp;
    ExpQueue* sPostfixExp = mPostfixExp;

    // Push “(” onto a stack and append “)” to the tokenized infix expression queue
    sExpStack->push("(");
    sInfixExp->enqueue(")");

    while (!sInfixExp->isEmpty())
    {
        string sToken = sInfixExp->dequeue();

        if (sToken == "(")
        {
            sExpStack->push(sToken);
        }
        else if (sToken == ")")
        {
            // Pop out all the operators and append them to postfix expression
            // till an opening bracket is found
            string sTop = sExpStack->pop();
            while (sTop != "(")
            {
                sPostfixExp->enqueue(sTop);
                sTop = sExpStack->pop();
            }
        }
        else if (sToken == "+" || sToken == "-" || sToken == "*" || sToken == "/" || sToken == "%")
        {
            // Pop out operators with higher precedence at the top of the stack
            // and append them to the postfix expression, before pushing the
            // current operator to the stack.
            while (!sExpStack->isEmpty())
            {
                string sTop = sExpStack->pop();
                if (precedence(sTop) >= precedence(sToken))
                {
                    sPostfixExp->enqueue(sTop);
                }
                else
                {
                    sExpStack->push(sTop);
                    break;
                }
            }
            sExpStack->push(sToken);
        }
        else
        {
            // Positions of the operands do not change in the postfix expression
            // so append the operand as it is.
            sPostfixExp->enqueue(sToken);
        }
    }
    delete(sExpStack);

    cout << "Postfix Expression:" << endl;
    sPostfixExp->print();
    cout << endl;

}

double Expression::pEvaluatePostfix()
{
    ExpStack* sExpStack = new ExpStack();
    ExpQueue* sPostfixExp = mPostfixExp;

    while (!sPostfixExp->isEmpty())
    {
        string sToken = sPostfixExp->dequeue();
        if (sToken == "+" || sToken == "-" || sToken == "*" || sToken == "/" || sToken == "%")
        {
            // pop top two operands, compute result and push back
            double sOp1 = stod(sExpStack->pop());
            double sOp2 = stod(sExpStack->pop());
            if (sToken == "+")
            {
                sExpStack->push(to_string(sOp2 + sOp1));
            }
            else if (sToken == "-")
            {
                sExpStack->push(to_string(sOp2 - sOp1));
            }
            else if (sToken == "*")
            {
                sExpStack->push(to_string(sOp2 * sOp1));
            }
            else if (sToken == "/")
            {
                sExpStack->push(to_string(sOp2 / sOp1));
            }
            else if (sToken == "%")
            {
                sExpStack->push(to_string(fmod(sOp2,sOp1)));
            }
        }
        else
        {
            // push operands onto stack
            sExpStack->push(sToken);
        }
    }

    double sResult = stod(sExpStack->pop());

    return sResult;
}
