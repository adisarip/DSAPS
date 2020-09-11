#ifndef BigIntegerIO_H
#define BigIntegerIO_H

#include "NumberBlockArray.H"
#include "BigInteger.H"
#include <string>
#include <iostream>
using namespace std;

// std::string conversion routines. Base 10 only.
std::string BigIntegerToString(const BigInteger &x);
BigInteger stringToBigInteger(const std::string &s);
// overloading '<<' operator for printing BinIntger using 'cout'.
std::ostream &operator <<(std::ostream &os, const BigInteger &x);

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
    // Creates a BigIntegerIO with a capacity; for internal use.
    BigIntegerIO(int, Index c) : NumberBlockArray<Digit>(0, c) {}
    // Decreases len to eliminate any leading zero digits
    void trimLeadingZeros()
    {
        while (len > 0 && block[len - 1] == 0)
        {
            len--;
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

    // Destructor.  NumberBlockArray does the delete for us.
    ~BigIntegerIO() {}

    // LINKS TO BigInteger
    BigIntegerIO(const BigInteger &x, Base base=10);
    operator BigInteger() const;

    // LINKS TO STRINGS
    // These use the symbols "0123456789" to represent digits of 0 through 9.
    operator string() const;
    BigIntegerIO(const string &s, Base base=10);

    // ACCESSORS
    Base getBase() const { return base; }

    /* Returns the requested digit, or 0 if it is beyond the length (as if
     * the number had 0s infinitely to the left). */
    Digit getDigit(Index i) const { return i >= len ? 0 : block[i]; }

    // The number is zero if and only if the canonical length is zero.
    bool isZero() const { return NumberBlockArray<Digit>::isEmpty(); }

    /* Equality test.  For the purposes of this test, two BigIntegerIO
     * values must have the same base to be equal. */
    bool operator ==(const BigIntegerIO &x) const
    {
        return base == x.base && NumberBlockArray<Digit>::operator ==(x);
    }
    bool operator !=(const BigIntegerIO &x) const { return !operator ==(x); }
};

#endif
