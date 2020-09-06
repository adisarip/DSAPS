// A class for evaluating experssions
#ifndef __EXP__
#define __EXP__

#include "ExpQueue.H"
using namespace std;

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

#endif
