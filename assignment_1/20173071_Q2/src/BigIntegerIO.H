#ifndef BigIntegerIO_H
#define BigIntegerIO_H

#include "NumberBlockArray.H"
#include "BigInteger.H"
#include <string>
#include <iostream>
using namespace std;

// string conversion routines. Base 10 only.
string BigIntegerToString(const BigInteger &x);
BigInteger stringToBigInteger(const string &s);
// overloading '<<' operator for printing BinIntger using 'cout'.
ostream &operator <<(ostream &os, const BigInteger &x);

class BigIntegerIO : public NumberBlockArray<unsigned short>
{
  public:
    // The digits of a BigIntegerIO are unsigned shorts.
    typedef unsigned short Digit;
    // That's also the type of a base.
    typedef Digit Base;

  protected:
    // The base in which this BigIntegerIO is expressed
    Base base;
    // For internal use.
    BigIntegerIO(int, Index c) : NumberBlockArray<Digit>(0, c) {}
    // Decreases len to eliminate any leading zero digits
    void trimLeadingZeros()
    {
        while (mLength > 0 && block[mLength - 1] == 0)
        {
            mLength--;
        }
    }

  public:
    // Constructs zero in base 2.
    BigIntegerIO() : NumberBlockArray<Digit>(), base(10) {}

    // Copy constructor
    BigIntegerIO(const BigIntegerIO &x) : NumberBlockArray<Digit>(x), base(x.base) {}

    // Assignment operator
    void operator =(const BigIntegerIO &x)
    {
        NumberBlockArray<Digit>::operator =(x);
        base = x.base;
    }

    // Constructor that copies from a given array of digits.
    BigIntegerIO(const Digit *d, Index l, Base base);

    // Destructor
    ~BigIntegerIO() {}

    BigIntegerIO(const BigInteger &x, Base base=10);
    operator BigInteger() const;

    // These use the symbols "0123456789" to represent digits of 0 through 9.
    operator string() const;
    BigIntegerIO(const string &s, Base base=10);

    // Accessing Member data
    Base getBase() const { return base; }
    // Returns the requested digit, or 0 if it is beyond the length
    Digit getDigit(Index i) const { return i >= mLength ? 0 : block[i]; }

    bool isZero() const { return NumberBlockArray<Digit>::isEmpty(); }

    bool operator ==(const BigIntegerIO &x) const
    {
        return base == x.base && NumberBlockArray<Digit>::operator ==(x);
    }
    bool operator !=(const BigIntegerIO &x) const { return !operator ==(x); }
};

#endif
