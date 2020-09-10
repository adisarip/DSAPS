#ifndef BIGUNSIGNEDINABASE_H
#define BIGUNSIGNEDINABASE_H

#include "NumberBlockArray.H"
#include "BigUnsigned.H"
#include <string>

class BigUnsignedInABase : public NumberBlockArray<unsigned short>
{
  public:
    // The digits of a BigUnsignedInABase are unsigned shorts.
    typedef unsigned short Digit;
    // That's also the type of a base.
    typedef Digit Base;

  protected:
    // The base in which this BigUnsignedInABase is expressed
    Base base;
    // Creates a BigUnsignedInABase with a capacity; for internal use.
    BigUnsignedInABase(int, Index c) : NumberBlockArray<Digit>(0, c) {}
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
    BigUnsignedInABase() : NumberBlockArray<Digit>(), base(10) {}

    // Copy constructor
    BigUnsignedInABase(const BigUnsignedInABase &x) : NumberBlockArray<Digit>(x), base(x.base) {}

    // Assignment operator
    void operator =(const BigUnsignedInABase &x)
    {
        NumberBlockArray<Digit>::operator =(x);
        base = x.base;
    }

    // Constructor that copies from a given array of digits.
    BigUnsignedInABase(const Digit *d, Index l, Base base);

    // Destructor.  NumberBlockArray does the delete for us.
    ~BigUnsignedInABase() {}

    // LINKS TO BIGUNSIGNED
    BigUnsignedInABase(const BigUnsigned &x, Base base);
    BigUnsignedInABase(const BigUnsigned &x);
    operator BigUnsigned() const;

    // LINKS TO STRINGS
    //
    // These use the symbols ``0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'' to
    // represent digits of 0 through 35.  When parsing strings, lowercase is
    // also accepted.
    //
    // All string representations are big-endian (big-place-value digits
    // first).
    operator std::string() const;
    BigUnsignedInABase(const std::string &s, Base base);
    BigUnsignedInABase(const std::string &s);

    // ACCESSORS
    Base getBase() const { return base; }

    /* Returns the requested digit, or 0 if it is beyond the length (as if
     * the number had 0s infinitely to the left). */
    Digit getDigit(Index i) const { return i >= len ? 0 : block[i]; }

    // The number is zero if and only if the canonical length is zero.
    bool isZero() const { return NumberBlockArray<Digit>::isEmpty(); }

    /* Equality test.  For the purposes of this test, two BigUnsignedInABase
     * values must have the same base to be equal. */
    bool operator ==(const BigUnsignedInABase &x) const
    {
        return base == x.base && NumberBlockArray<Digit>::operator ==(x);
    }
    bool operator !=(const BigUnsignedInABase &x) const { return !operator ==(x); }
};

#endif
