#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include "NumberBlockArray.H"
#include <iostream>
using namespace std;

// BigUnsigned class represents a nonnegative integer of size limited only by
// available memory. BigUnsigneds support most mathematical operators and can
// be converted to and from most primitive integer types.
// The number is stored as a NumberBlockArray of unsigned longs as if it were
// written in base 256^sizeof(unsigned long). The least significant block is
// first, and the length is such that the most significant block is nonzero.
class BigUnsigned : public NumberBlockArray<unsigned long>
{
  public:
    // Enumeration for the result of a comparison.
    enum CmpRes
    {
        less = -1,
        equal = 0,
        greater = 1
    };

    // BigUnsigneds are built with a Block type of unsigned long.
    typedef unsigned long Block;
    typedef NumberBlockArray<Block>::Index Index;

  protected:
      // Creates a BigUnsigned with a capacity; for internal use.
      BigUnsigned(int, Index c) : NumberBlockArray<Block>(0, c) {}
      // Decreases len to eliminate any leading zero blocks.
      void trimLeadingZeros();

  public:

    // Constructs zero.
    BigUnsigned() : NumberBlockArray<Block>() {}
    // Copy constructor
    BigUnsigned(const BigUnsigned &x) : NumberBlockArray<Block>(x) {}
    // Assignment operator
    void operator=(const BigUnsigned &x) { NumberBlockArray<Block>::operator =(x); }

    // Copy Constructor - that copies from a given array of blocks.
    BigUnsigned(const Block *b, Index blen) : NumberBlockArray<Block>(b, blen)
    {
        // Eliminate any leading zeros we may have been passed.
        trimLeadingZeros();
    }

  protected:
    // Helpers
    template <class X> void initFromPrimitive (X x);
    template <class X> X convertToPrimitive () const;

  public:
    // Constructors from primitive integer types
    BigUnsigned(unsigned long  x) { initFromPrimitive (x); }
    BigUnsigned(unsigned short x) { initFromPrimitive (x); }

    // Destructor.
    ~BigUnsigned() {}

    // Converters to primitive integer types
    unsigned short toUnsignedShort() const { return convertToPrimitive <unsigned short>(); }

    // The number is zero if and only if the canonical length is zero.
    bool isZero() const;

    // Overloaded operators
    // Helper function -> Compares *this to x
    CmpRes compareTo(const BigUnsigned &x) const;
    // Ordinary comparison operators
    bool operator ==(const BigUnsigned &x) const { return NumberBlockArray<Block>::operator ==(x); }
    bool operator !=(const BigUnsigned &x) const { return NumberBlockArray<Block>::operator !=(x); }
    bool operator < (const BigUnsigned &x) const { return compareTo(x) == less; }
    bool operator <=(const BigUnsigned &x) const { return compareTo(x) != greater; }
    bool operator >=(const BigUnsigned &x) const { return compareTo(x) != less; }
    bool operator > (const BigUnsigned &x) const { return compareTo(x) == greater; }

    // Arguments are read-only operands, result is saved in *this.
    void add(const BigUnsigned &a, const BigUnsigned &b);
    void subtract(const BigUnsigned &a, const BigUnsigned &b);
    void multiply(const BigUnsigned &a, const BigUnsigned &b);
    void bitShiftLeft(const BigUnsigned &a, int b);
    void bitShiftRight(const BigUnsigned &a, int b);
    void divide(const BigUnsigned &b, BigUnsigned &q);

    // Overloaded Arithmetic Operators
    BigUnsigned operator +(const BigUnsigned &x) const;
    BigUnsigned operator -(const BigUnsigned &x) const;
    BigUnsigned operator *(const BigUnsigned &x) const;
    BigUnsigned operator /(const BigUnsigned &x) const;
    BigUnsigned operator %(const BigUnsigned &x) const;

    // Overloaded Biwise Shift Operators
    BigUnsigned operator <<(int b) const;
    BigUnsigned operator >>(int b) const;

    // Helper function that needs access to BigUnsigned internals
    friend Block getShiftedBlock(const BigUnsigned &num,
                                 Index x,
                                 unsigned int y);

};

inline BigUnsigned BigUnsigned::operator +(const BigUnsigned &x) const
{
    BigUnsigned ans;
    ans.add(*this, x);
    return ans;
}
inline BigUnsigned BigUnsigned::operator -(const BigUnsigned &x) const
{
    BigUnsigned ans;
    ans.subtract(*this, x);
    return ans;
}
inline BigUnsigned BigUnsigned::operator *(const BigUnsigned &x) const
{
    BigUnsigned ans;
    ans.multiply(*this, x);
    return ans;
}
inline BigUnsigned BigUnsigned::operator /(const BigUnsigned &x) const
{
    if (x.isZero())
    {
        cout << "[ERROR] Division by zero (/)" << endl;
    }
    BigUnsigned q, r;
    r = *this;
    r.divide(x, q);
    return q;
}
inline BigUnsigned BigUnsigned::operator %(const BigUnsigned &x) const
{
    if (x.isZero())
    {
        cout << "[ERROR] Division by zero (%)" << endl;
    }
    BigUnsigned q, r;
    r = *this;
    r.divide(x, q);
    return r;
}
inline BigUnsigned BigUnsigned::operator <<(int b) const
{
    BigUnsigned ans;
    ans.bitShiftLeft(*this, b);
    return ans;
}
inline BigUnsigned BigUnsigned::operator >>(int b) const
{
    BigUnsigned ans;
    ans.bitShiftRight(*this, b);
    return ans;
}

// CONSTRUCTION FROM PRIMITIVE INTEGERS
template <class X>
void BigUnsigned::initFromPrimitive(X x)
{
    // NumberBlockArray already initialized us to zero.
    if (x != 0)
    {
        // Create a single block.
        cap = 1;
        block = new Block[1];
        len = 1;
        block[0] = Block(x);
    }
}

// CONVERSION TO PRIMITIVE INTEGERS
template <class X>
X BigUnsigned::convertToPrimitive() const
{
    X x;
    if (len == 0)
    {
        // The number is zero; return zero.
        return 0;
    }
    else if (len == 1)
    {
        // The single block might fit in an X.  Try the conversion.
        x = X(block[0]);
        // Make sure the result accurately represents the block.
        if (Block(x) == block[0])
        {
            // Successful conversion.
            return x;
        }
        // Otherwise fall through.
    }
    cout << "[ERROR] Value is too big to fit in the requested type" << endl;
    return x;
}

#endif
