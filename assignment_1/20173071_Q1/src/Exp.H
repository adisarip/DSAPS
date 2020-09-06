// A class for evaluating experssions
#ifndef __EXP__
#define __EXP__

#include "ExpQueue.H"
using namespace std;

class Exp
{
  public:
    Exp(string expStrParm);
    ~Exp();

    double evaluate();
    // Setter/getter methods
    void setExpString(string expStrParm);
    string getExpString();

  protected:
    // helper functions for evaluating expressions
    void pTokenizeExp(); // creating tokenized infix expression
    void pConvertToPostfix();

  private:
    string    mExpStr;
    ExpQueue* mInfixExp;
    ExpQueue* mPostfixExp;
};

#endif
