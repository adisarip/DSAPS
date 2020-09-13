

#include <cmath>
#include <string>
#include <iostream>
using namespace std;

// A Singly Linked List Node used in expresion evaluation
struct ExpNode
{
    string mToken;
    ExpNode* mNext;
    inline ExpNode():mToken(""),mNext(NULL){};
    inline ~ExpNode(){};
};


//=================== Class Implementation: "ExpStack" ===================//
// A Stack implementation for storing operators for evaluating experssions
// Base data structure: Singly Linked List

// Declarations
class ExpStack
{
  public:
    ExpStack();
    ~ExpStack();

    void push(string expTokenParm);
    string pop();
    void clear();
    void print();
    bool isEmpty();

  private:
    ExpNode* mHead;
};

// Definitions

ExpStack::ExpStack()
:mHead(NULL)
{
}

ExpStack::~ExpStack()
{
    this->clear();
}

void ExpStack::push(string expTokenParm)
{
    ExpNode* sNode = new ExpNode();
    sNode->mToken = expTokenParm;
    if (NULL == mHead)
    {
        mHead = sNode;
    }
    else
    {
        sNode->mNext = mHead;
        mHead = sNode;
    }
}

string ExpStack::pop()
{
    string sToken = "";
    if (NULL != mHead)
    {
        ExpNode* sNode = mHead;
        sToken = sNode->mToken;
        mHead = sNode->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
    return sToken;
}

void ExpStack::clear()
{
    ExpNode* sNode = NULL;
    // delete all the elements in stack and deallocate their memory.
    while(NULL != mHead)
    {
        sNode = mHead;
        mHead = sNode->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
}

bool ExpStack::isEmpty()
{
    bool sIsEmpty = false;
    if (mHead == NULL)
    {
        sIsEmpty = true;
    }
    return sIsEmpty;
}

void ExpStack::print()
{
    // Traverse and print the current stack
    ExpNode* sNode = mHead;

    if (NULL == sNode)
    {
        return;
    }

    while (NULL != sNode)
    {
        cout << sNode->mToken;
        sNode = sNode->mNext;
    }
    cout << endl;
    return;
}


//======================= Class Implementation: "ExpQueue" =======================//
// A Queue implementation for storing operators/operands for evaluating experssions
// Base data structure: Singly Linked List

// Declarations

class ExpQueue
{
  public:
    ExpQueue();
    ~ExpQueue();

    void enqueue(string expTokenParm);
    string dequeue();
    void clear();
    void print();
    bool isEmpty();

  private:
    ExpNode* mHead;
    ExpNode* mTail;
};

// Definitions

ExpQueue::ExpQueue()
:mHead(NULL)
,mTail(NULL)
{
}

ExpQueue::~ExpQueue()
{
    this->clear();
}

void ExpQueue::enqueue(string expTokenParm)
{
    ExpNode* sNode = new ExpNode();
    if (sNode != NULL)
    {
        sNode->mToken = expTokenParm;
        if (mHead == mTail && mHead == NULL)
        {
            mHead = sNode;
            mTail = sNode;
        }
        else
        {
            sNode->mNext = NULL;
            mTail->mNext = sNode;
            mTail = sNode;
        }
    }
}

string ExpQueue::dequeue()
{
    string sToken = "";
    if (mHead != NULL)
    {
        ExpNode* sNode = mHead;
        sToken = sNode->mToken;
        mHead = sNode->mNext;
        sNode->mNext = NULL;
        mTail = (mHead == NULL) ? mHead : mTail;
        delete(sNode);
    }
    return sToken;
}

bool ExpQueue::isEmpty()
{
    bool sIsEmpty = false;
    if (mHead == mTail && mHead == NULL)
    {
        sIsEmpty = true;
    }
    return sIsEmpty;
}

void ExpQueue::clear()
{
    // delete all the elements in queue and deallocate their memory.
    while(mHead != NULL)
    {
        ExpNode* sNode = mHead;
        mHead = mHead->mNext;
        sNode->mNext = NULL;
        delete(sNode);
    }
}

void ExpQueue::print()
{
    // Traverse and print the current stack
    ExpNode* sNode = mHead;

    if (sNode == NULL)
    {
        return;
    }

    while (sNode != NULL)
    {
        cout << sNode->mToken << " ";
        sNode = sNode->mNext;
    }
    cout << endl;
    return;
}


//======= Class Implementation: "Expression" =======//
// A class for evaluating experssions

class Expression
{
  public:
    Expression(string expStrParm);
    ~Expression();

    double evaluate();
    // Setter/getter methods
    void setExpString(string expStrParm);
    string getExpString();

  protected:
    // helper functions for evaluating expressions
    int precedence(string tokenParm);
    void pTokenizeExpression(); // creating tokenized infix expression
    void pConvertToPostfix();   // converting infix expression to postfix expresion
    double pEvaluatePostfix();  // evaluate postfix expresion

  private:
    string    mExpStr;
    ExpQueue* mInfixExp;
    ExpQueue* mPostfixExp;
};

// Definitions

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
        else if (c == ' ')
        {
            // skip spaces
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


//=============== Driver Program ===============//

int main (int argc, char* argv[])
{
    // reading the infix expression
    string sExpStr;
    getline(cin, sExpStr);

    Expression sExpression(sExpStr);
    double sResult = sExpression.evaluate(); // evaluate the expresion
    cout << sResult << endl;
}
