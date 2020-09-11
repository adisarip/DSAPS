#ifndef BigInteger_H
#define BigInteger_H

#include "NumberBlockArray.H"
#include <iostream>
using namespace std;

// BigInteger class represents a nonnegative integer of size limited only by
// available memory. BigIntegers support most mathematical operators and can
// be converted to and from most primitive integer types.
// The number is stored as a NumberBlockArray of unsigned longs as if it were
// written in base 256^sizeof(unsigned long). The least significant block is
// first, and the length is such that the most significant block is nonzero.
class BigInteger : public NumberBlockArray<unsigned long>
{
  public:
    // Enumeration for the result of a comparison.
    enum CmpRes
    {
        less = -1,
        equal = 0,
        greater = 1
    };

    // BigIntegers are built with a Block type of unsigned long.
    typedef unsigned long Block;
    typedef NumberBlockArray<Block>::Index Index;

  protected:
      // Creates a BigInteger with a capacity; for internal use.
      BigInteger(int, Index c) : NumberBlockArray<Block>(0, c) {}
      // Decreases len to eliminate any leading zero blocks.
      void trimLeadingZeros();

  public:

    // Constructs zero.
    BigInteger() : NumberBlockArray<Block>() {}
    // Copy constructor
    BigInteger(const BigInteger &x) : NumberBlockArray<Block>(x) {}
    // Assignment operator
    void operator=(const BigInteger &x) { NumberBlockArray<Block>::operator =(x); }

    // Copy Constructor - that copies from a given array of blocks.
    BigInteger(const Block *b, Index blen) : NumberBlockArray<Block>(b, blen)
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
    BigInteger(unsigned long  x) { initFromPrimitive (x); }
    BigInteger(unsigned short x) { initFromPrimitive (x); }

    // Destructor.
    ~BigInteger() {}

    // Converters to primitive integer types
    unsigned short toUnsignedShort() const { return convertToPrimitive <unsigned short>(); }

    // The number is zero if and only if the canonical length is zero.
    bool isZero() const;

    // Overloaded operators
    // Helper function -> Compares *this to x
    CmpRes compareTo(const BigInteger &x) const;
    // Ordinary comparison operators
    bool operator ==(const BigInteger &x) const { return NumberBlockArray<Block>::operator ==(x); }
    bool operator !=(const BigInteger &x) const { return NumberBlockArray<Block>::operator !=(x); }
    bool operator < (const BigInteger &x) const { return compareTo(x) == less; }
    bool operator <=(const BigInteger &x) const { return compareTo(x) != greater; }
    bool operator >=(const BigInteger &x) const { return compareTo(x) != less; }
    bool operator > (const BigInteger &x) const { return compareTo(x) == greater; }

    // Arguments are read-only operands, result is saved in *this.
    void add(const BigInteger &a, const BigInteger &b);
    void subtract(const BigInteger &a, const BigInteger &b);
    void multiply(const BigInteger &a, const BigInteger &b);
    void bitShiftLeft(const BigInteger &a, int b);
    void bitShiftRight(const BigInteger &a, int b);
    void divide(const BigInteger &b, BigInteger &q);

    // Overloaded Arithmetic Operators
    BigInteger operator +(const BigInteger &x) const;
    BigInteger operator -(const BigInteger &x) const;
    BigInteger operator *(const BigInteger &x) const;
    BigInteger operator /(const BigInteger &x) const;
    BigInteger operator %(const BigInteger &x) const;

    // Overloaded Biwise Shift Operators
    BigInteger operator <<(int b) const;
    BigInteger operator >>(int b) const;

    // Helper function that needs access to BigInteger internals
    friend Block getShiftedBlock(const BigInteger &num,
                                 Index x,
                                 unsigned int y);

};

inline BigInteger BigInteger::operator +(const BigInteger &x) const
{
    BigInteger ans;
    ans.add(*this, x);
    return ans;
}
inline BigInteger BigInteger::operator -(const BigInteger &x) const
{
    BigInteger ans;
    ans.subtract(*this, x);
    return ans;
}
inline BigInteger BigInteger::operator *(const BigInteger &x) const
{
    BigInteger ans;
    ans.multiply(*this, x);
    return ans;
}
inline BigInteger BigInteger::operator /(const BigInteger &x) const
{
    if (x.isZero())
    {
        cout << "[ERROR] Division by zero (/)" << endl;
    }
    BigInteger q, r;
    r = *this;
    r.divide(x, q);
    return q;
}
inline BigInteger BigInteger::operator %(const BigInteger &x) const
{
    if (x.isZero())
    {
        cout << "[ERROR] Division by zero (%)" << endl;
    }
    BigInteger q, r;
    r = *this;
    r.divide(x, q);
    return r;
}
inline BigInteger BigInteger::operator <<(int b) const
{
    BigInteger ans;
    ans.bitShiftLeft(*this, b);
    return ans;
}
inline BigInteger BigInteger::operator >>(int b) const
{
    BigInteger ans;
    ans.bitShiftRight(*this, b);
    return ans;
}

// CONSTRUCTION FROM PRIMITIVE INTEGERS
template <class X>
void BigInteger::initFromPrimitive(X x)
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
X BigInteger::convertToPrimitive() const
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
