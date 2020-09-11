
#include <string>
#include <iostream>
using namespace std;

#ifndef NULL
#define NULL 0
#endif

// This class implements a heap-allocated array of unsigned long blocks with
// a given length and a capacity and provides basic memory management features.
template <class Block>
class NumberBlockArray
{
  public:
    // Type for the index of a block in the array
    typedef unsigned int Index;
    // The number of bits in a block, defined below.
    static const unsigned int N;
    // The current allocated capacity of this NumberBlockArray (in blocks)
    Index mCapacity;
    // The actual length of the value stored in this NumberBlockArray (in blocks)
    Index mLength;
    // Heap-allocated array of the blocks
    Block *block;

    // Constructs a 'zero' NumberBlockArray with the given capacity.
    NumberBlockArray(Index c);
    // Constructs a zero NumberBlockArray without allocating a Block array.
    NumberBlockArray();
    // Destructor
    ~NumberBlockArray() { delete [] block; }
    // Ensures that the array has at least the requested capacity.
    // may destroy the contents.
    void allocate(Index capacity);
    // Ensures that the array has at least the requested capacity.
    // does not destroy the contents.
    void allocateAndCopy(Index capacity);
    // Copy constructor
    NumberBlockArray(const NumberBlockArray<Block> &x);
    // Constructor that copies from a given array of blocks
    NumberBlockArray(const Block *b, Index blockLength);

    // exposing the member data
    Index getCapacity()     const { return mCapacity; }
    Index getLength()       const { return mCapacity; }
    Block getBlock(Index i) const { return block[i];   }
    bool  isEmpty()         const { return mLength == 0; }

    // Assignment operator
    void operator=(const NumberBlockArray<Block> &x);
    bool operator ==(const NumberBlockArray<Block> &x) const;
    bool operator !=(const NumberBlockArray<Block> &x) const;
};

template <class Block>
const unsigned int NumberBlockArray<Block>::N = 8 * sizeof(Block);

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(Index capacity)
:mCapacity(capacity),
mLength(0)
{
    block = (mCapacity > 0) ? (new Block[mCapacity]) : NULL;
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray()
:mCapacity(0),
mLength(0)
{
    block = NULL;
}

template <class Block>
void NumberBlockArray<Block>::allocate(Index capacity)
{
    // If the requested capacity is more than the current capacity...
    if (capacity > mCapacity)
    {
        // Delete the old number array
        delete [] block;
        // Allocate the new array
        mCapacity = capacity;
        block = new Block[mCapacity];
    }
}

template <class Block>
void NumberBlockArray<Block>::allocateAndCopy(Index capacity)
{
    // If the requested capacity is more than the current capacity...
    if (capacity > mCapacity)
    {
        Block *oldBlock = block;
        // Allocate the new number array
        mCapacity = capacity;
        block = new Block[mCapacity];
        // Copy number blocks
        Index i;
        for (i = 0; i < mLength; i++)
        {
            block[i] = oldBlock[i];
        }
        // Delete the old array
        delete [] oldBlock;
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const NumberBlockArray<Block> &x)
:mLength(x.mLength)
{
    // Create array
    mCapacity = mLength;
    block = new Block[mCapacity];
    // Copy blocks
    Index i;
    for (i = 0; i < mLength; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const Block *b, Index blockLength)
:mCapacity(blockLength)
,mLength(blockLength)
{
    // Create array
    block = new Block[mCapacity];
    // Copy blocks
    Index i;
    for (i = 0; i < mLength; i++)
    {
        block[i] = b[i];
    }
}

template <class Block>
void NumberBlockArray<Block>::operator=(const NumberBlockArray<Block> &x)
{
    // Calls like a = a have no effect
    if (this == &x)
    {
        return;
    }

    // Copy length & Expand array if necessary
    mLength = x.mLength;
    allocate(mLength);

    // Copy number blocks
    Index i;
    for (i = 0; i < mLength; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator ==(const NumberBlockArray<Block> &x) const
{
    if (mLength != x.mLength)
    {
        // Definitely unequal.
        return false;
    }
    else
    {
        // Compare corresponding blocks one by one.
        Index i;
        for (i = 0; i < mLength; i++)
        {
            if (block[i] != x.block[i])
            {
                return false;
            }
        }
        // No blocks differed, so the objects are equal.
        return true;
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator !=(const NumberBlockArray<Block> &x) const
{
    return !operator ==(x);
}



// ============================

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
    enum CompareResult
    {
        LESS    = 1,
        EQUAL   = 2,
        GREATER = 3,
    };

    // BigIntegers are built with a Block type of unsigned long.
    typedef unsigned long Block;
    typedef NumberBlockArray<Block>::Index Index;

  protected:
      // For internal use.
      BigInteger(int, Index c) : NumberBlockArray<Block>(0, c) {}
      // Eliminate any leading zero blocks.
      void trimLeadingZeros();

  public:

    BigInteger() : NumberBlockArray<Block>() {}
    // Copy constructor
    BigInteger(const BigInteger &x) : NumberBlockArray<Block>(x) {}
    // Assignment operator
    void operator=(const BigInteger &x) { NumberBlockArray<Block>::operator =(x); }
    // Copy Constructor - that copies from a given array of blocks.
    BigInteger(const Block *b, Index blockLength) : NumberBlockArray<Block>(b, blockLength)
    {
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

    bool isZero() const;

    // Overloaded operators
    // Helper function -> Compares *this to x
    CompareResult compareTo(const BigInteger &x) const;
    // Ordinary comparison operators
    bool operator ==(const BigInteger &x) const { return NumberBlockArray<Block>::operator ==(x); }
    bool operator !=(const BigInteger &x) const { return NumberBlockArray<Block>::operator !=(x); }
    bool operator < (const BigInteger &x) const { return compareTo(x) == BigInteger::LESS; }
    bool operator <=(const BigInteger &x) const { return compareTo(x) != BigInteger::GREATER; }
    bool operator >=(const BigInteger &x) const { return compareTo(x) != BigInteger::LESS; }
    bool operator > (const BigInteger &x) const { return compareTo(x) == BigInteger::GREATER; }

    // Arguments are read-only operands
    // Result of the operation is saved in *this.
    void add(const BigInteger &a, const BigInteger &b);
    void subtract(const BigInteger &a, const BigInteger &b);
    void multiply(const BigInteger &a, const BigInteger &b);
    void bitShiftLeft(const BigInteger &a, int b);
    void bitShiftRight(const BigInteger &a, int b);
    // After division
    // 'q' has the qoutient
    // *this has the remainder
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

template <class X>
void BigInteger::initFromPrimitive(X x)
{
    if (x != 0)
    {
        // Create a single block.
        mCapacity = 1;
        block = new Block[1];
        mLength = 1;
        block[0] = Block(x);
    }
}

template <class X>
X BigInteger::convertToPrimitive() const
{
    X x;
    if (mLength == 0)
    {
        return 0;
    }
    else if (mLength == 1)
    {
        x = X(block[0]);
        if (Block(x) == block[0])
        {
            return x; // conversion successful.
        }
    }
    cout << "[ERROR] Value is too big to fit in the requested type" << endl;
    return x;
}


// =========================

void BigInteger::trimLeadingZeros()
{
    while (mLength > 0 && block[mLength - 1] == 0)
    {
        mLength--;
    }
}

bool BigInteger::isZero() const
{
    return NumberBlockArray::isEmpty();
}

BigInteger::CompareResult BigInteger::compareTo(const BigInteger &x) const
{
    BigInteger::CompareResult sResult = BigInteger::EQUAL;
    // A bigger length implies a bigger number.
    if (mLength < x.mLength)
    {
        sResult = BigInteger::LESS;
    }
    else if (mLength > x.mLength)
    {
        sResult = BigInteger::GREATER;
    }
    else
    {
        // Compare blocks one by one from left to right.
        Index i = mLength;
        while (i > 0)
        {
            i--;
            if (block[i] == x.block[i])
            {
                continue;
            }
            else if (block[i] > x.block[i])
            {
                sResult = BigInteger::GREATER;
            }
            else
            {
                sResult = BigInteger::LESS;
            }
        }
        // If no blocks differed, the numbers are equal.
        sResult = BigInteger::EQUAL;
    }
    return sResult;
}

// A macro defined to use for the repeated checks that needs to be performed
// by all the arithmentic operations
#define IF_ALIASED(condition, operation) \
    if (condition) \
    { \
        BigInteger tmp; \
        tmp.operation; \
        *this = tmp; \
        return; \
    }

void BigInteger::add(const BigInteger &a, const BigInteger &b)
{
    IF_ALIASED(this == &a || this == &b, add(a, b));

    if (a.mLength == 0)
    {
        operator =(b);
        return;
    }
    else if (b.mLength == 0)
    {
        operator =(a);
        return;
    }

    // Carries IN and OUT
    bool carryIn, carryOut;
    Block temp;
    Index i;

    // bigInput points to the longer input
    // smallInput points to the shorter Input
    const BigInteger *bigInput, *smallInput;
    if (a.mLength >= b.mLength)
    {
        bigInput = &a;
        smallInput = &b;
    }
    else
    {
        bigInput = &b;
        smallInput = &a;
    }

    // Set prelimiary length and make room in this BigInteger
    mLength = bigInput->mLength + 1;
    allocate(mLength);

    // For each block index that is present in both inputs...
    for (i = 0, carryIn = false; i < smallInput->mLength; i++)
    {
        // Add input blocks
        temp = bigInput->block[i] + smallInput->block[i];

        // If a rollover occurred, the result is less than either input.
        carryOut = (temp < bigInput->block[i]);

        // If a carry was input, handle it
        if (carryIn)
        {
            temp++;
            carryOut |= (temp == 0);
        }
        block[i] = temp; // Save the addition result
        carryIn = carryOut; // Pass the carry along
    }

    // If there is a carry left over, increase blocks until
    // one does not roll over.
    for (; i < bigInput->mLength && carryIn; i++)
    {
        temp = bigInput->block[i] + 1;
        carryIn = (temp == 0);
        block[i] = temp;
    }

    // If the carry was resolved but the larger number
    // still has blocks, copy them over.
    for (; i < bigInput->mLength; i++)
    {
        block[i] = bigInput->block[i];
    }

    // Set the extra block if there's still a carry, decrease length otherwise
    if (carryIn)
    {
        block[i] = 1;
    }
    else
    {
        mLength--;
    }
}


void BigInteger::subtract(const BigInteger &a, const BigInteger &b)
{
    IF_ALIASED(this == &a || this == &b, subtract(a, b));

    if (b.mLength == 0)
    {
        // If b is zero, copy a.
        operator =(a);
        return;
    }
    else if (a.mLength < b.mLength)
    {
        // If a is shorter than b, the result is negative.
        cout << "ERROR: Negative result in unsigned calculation" << endl;
        return;
    }

    bool borrowIn, borrowOut;
    Block temp;
    Index i;

    // Set preliminary length and make room
    mLength = a.mLength;
    allocate(mLength);

    // For each block index that is present in both inputs...
    for (i = 0, borrowIn = false; i < b.mLength; i++)
    {
        temp = a.block[i] - b.block[i];

        // If a reverse rollover occurred, the result is greater than the block from a.
        borrowOut = (temp > a.block[i]);

        // Handle an incoming borrow
        if (borrowIn)
        {
            borrowOut |= (temp == 0);
            temp--;
        }
        block[i] = temp; // Save the subtraction result
        borrowIn = borrowOut; // Pass the borrow along
    }

    // If there is a borrow left over, decrease blocks until
    // one does not reverse rollover.
    for (; i < a.mLength && borrowIn; i++)
    {
        borrowIn = (a.block[i] == 0);
        block[i] = a.block[i] - 1;
    }
    // If there's still a borrow, the result is negative.
    // print error, but zero out this object.
    if (borrowIn)
    {
        mLength = 0;
        cout << "ERROR: Negative result in unsigned calculation" << endl;
    }
    else
    {
        // Copy over the rest of the blocks
        for (; i < a.mLength; i++)
        {
            block[i] = a.block[i];
        }
    }
    // Trim leading zeros
    trimLeadingZeros();
}

// Multiplication and Division algorithms
// Here we use bit-shifting algorithms for multiplication and division.
// To multiply 'a' and 'b', we zero out the result. Then, for each '1'
// bit in 'a', we shift 'b' left the appropriate amount and add it to
// the result. Similarly, to divide 'a' by 'b', we shift 'b' left varying
// amounts, repeatedly trying to subtract it from 'a'. When we succeed,
// we note the fact by setting a bit in the quotient.

// A helper function used by both the multiplication and the division routines.
// getShiftedBlock() returns the 'x'th block of 'num << y'.
// 'y' may be anything from 0 to N - 1, and 'x' may be anything from
// 0 to 'num.mLength'.

inline BigInteger::Block getShiftedBlock(const BigInteger &num,
                                          BigInteger::Index x,
                                          unsigned int y)
{
    BigInteger::Block part1 = (x == 0 || y == 0) ? 0 : (num.block[x - 1] >> (BigInteger::N - y));
    BigInteger::Block part2 = (x == num.mLength) ? 0 : (num.block[x] << y);
    return part1 | part2;
}

void BigInteger::multiply(const BigInteger &a, const BigInteger &b)
{
    IF_ALIASED(this == &a || this == &b, multiply(a, b));

    // If either a or b is zero, set to zero.
    if (a.mLength == 0 || b.mLength == 0)
    {
        mLength = 0;
        return;
    }

    // Variables for the calculation
    Index i, j, k;
    unsigned int i2;
    Block temp;
    bool carryIn, carryOut;

    // Set preliminary length and make room
    mLength = a.mLength + b.mLength;
    allocate(mLength);

    // Zero out this object
    for (i = 0; i < mLength; i++)
    {
        block[i] = 0;
    }

    // For each block of the first number...
    for (i = 0; i < a.mLength; i++)
    {
        // For each 1-bit of that block...
        for (i2 = 0; i2 < N; i2++)
        {
            if ((a.block[i] & (Block(1) << i2)) == 0)
            {
                continue;
            }

            for (j = 0, k = i, carryIn = false; j <= b.mLength; j++, k++)
            {
                temp = block[k] + getShiftedBlock(b, j, i2);
                carryOut = (temp < block[k]);
                if (carryIn)
                {
                    temp++;
                    carryOut |= (temp == 0);
                }
                block[k] = temp;
                carryIn = carryOut;
            }
            // Roll-over a carry as necessary.
            for (; carryIn; k++)
            {
                block[k]++;
                carryIn = (block[k] == 0);
            }
        }
    }
    // Trim possible leading zero
    if (block[mLength - 1] == 0)
    {
        mLength--;
    }
}

// DIVISION WITH REMAINDER
// This function mods *this by the given divisor 'b' while storing the
// quotient in the given object 'q' and at the end *this contains the remainder.

void BigInteger::divide(const BigInteger &b, BigInteger &q)
{
    if (this == &q)
    {
        cout <<  "Cannot write quotient and remainder into the same variable" << endl;
        return;
    }

    // If b is aliased to *this or q - use a temporary copy of b
    if (this == &b || &q == &b)
    {
        BigInteger tmpB(b);
        divide(tmpB, q);
        return;
    }

    if (b.mLength == 0)
    {
        q.mLength = 0;
        return;
    }

    if (mLength < b.mLength)
    {
        q.mLength = 0;
        return;
    }

    // At this point we know this->mLength >= b.mLength > 0

    // Variables for the calculation
    Index i, j, k;
    unsigned int i2;
    Block temp;
    bool borrowIn, borrowOut;
    Index origLen = mLength; // Save real length.

    //To avoid an out-of-bounds access in case of reallocation, allocate
    //first and then increment the logical length.
    allocateAndCopy(mLength + 1);

    mLength++;
    block[origLen] = 0; // Zero the added block.

    // subtractBuf holds part of the result of a subtraction; see above.
    Block *subtractBuf = new Block[mLength];

    // Set preliminary length for quotient and make room
    q.mLength = origLen - b.mLength + 1;
    q.allocate(q.mLength);

    // Zero out the quotient
    for (i = 0; i < q.mLength; i++)
    {
        q.block[i] = 0;
    }

    // For each possible left-shift of b in blocks...
    i = q.mLength;
    while (i > 0)
    {
        i--;
        // For each possible left-shift of b in bits...
        // Here 'N' is the number of bits in a Block.
        q.block[i] = 0;
        i2 = N;
        while (i2 > 0)
        {
            i2--;
            for (j = 0, k = i, borrowIn = false; j <= b.mLength; j++, k++)
            {
                temp = block[k] - getShiftedBlock(b, j, i2);
                borrowOut = (temp > block[k]);
                if (borrowIn)
                {
                    borrowOut |= (temp == 0);
                    temp--;
                }
                subtractBuf[k] = temp;
                borrowIn = borrowOut;
            }
            for (; k < origLen && borrowIn; k++)
            {
                borrowIn = (block[k] == 0);
                subtractBuf[k] = block[k] - 1;
            }

            if (!borrowIn)
            {
                q.block[i] |= (Block(1) << i2);
                while (k > i)
                {
                    k--;
                    block[k] = subtractBuf[k];
                }
            }
        }
    }

    // Trim possible leading zero in quotient
    if (q.block[q.mLength - 1] == 0)
    {
        q.mLength--;
    }
    // Trim any/all leading zeros in remainder
    trimLeadingZeros();

    // Deallocate subtractBuf.
    delete [] subtractBuf;
}


void BigInteger::bitShiftLeft(const BigInteger &a, int b)
{
    IF_ALIASED(this == &a, bitShiftLeft(a, b));

    Index shiftBlocks = b / N;
    unsigned int shiftBits = b % N;

    // make room for high bits nudged left into another block
    mLength = a.mLength + shiftBlocks + 1;
    allocate(mLength);

    Index i, j;
    for (i = 0; i < shiftBlocks; i++)
    {
        block[i] = 0;
    }

    for (j = 0, i = shiftBlocks; j <= a.mLength; j++, i++)
    {
        block[i] = getShiftedBlock(a, j, shiftBits);
    }

    // Trim possible leading zero
    if (block[mLength - 1] == 0)
    {
        mLength--;
    }
}

void BigInteger::bitShiftRight(const BigInteger &a, int b)
{
    IF_ALIASED(this == &a, bitShiftRight(a, b));

    Index rightShiftBlocks = (b + N - 1) / N;
    unsigned int leftShiftBits = N * rightShiftBlocks - b;

    // Now (N * rightShiftBlocks - leftShiftBits) == b
    // and 0 <= leftShiftBits < N.
    if (rightShiftBlocks >= a.mLength + 1)
    {
        // All of a is guaranteed to be shifted off, even considering the left bit shift
        mLength = 0;
        return;
    }

    // Now we're allocating a positive amount.
    // make room for high bits nudged left into another block
    mLength = a.mLength + 1 - rightShiftBlocks;
    allocate(mLength);

    Index i, j;
    for (j = rightShiftBlocks, i = 0; j <= a.mLength; j++, i++)
    {
        block[i] = getShiftedBlock(a, j, leftShiftBits);
    }

    // Trim possible leading zero
    if (block[mLength - 1] == 0)
    {
        mLength--;
    }
}



//===========================

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


// ===============================


BigIntegerIO::BigIntegerIO(const Digit *d, Index l, Base base)
:NumberBlockArray<Digit>(d, l)
,base(base)
{
    // Check the base
    if (base < 2 || base > 10)
    {
        cout << "[ERROR] Invalid Base(1): " << base << endl;
        return;
    }

    // Validate the digits.
    for (Index i = 0; i < l; i++)
    {
        if (block[i] >= base)
        {
            cout << "[ERROR] A digit is too large for the specified base(1)" << endl;
        }
    }
    trimLeadingZeros();
}

namespace
{
    unsigned int bitLen(unsigned int x)
    {
        unsigned int length = 0;
        while (x > 0)
        {
            x >>= 1;
            length++;
        }
        return length;
    }
    unsigned int ceilingDiv(unsigned int a, unsigned int b)
    {
        return (a + b - 1) / b;
    }
}

BigIntegerIO::BigIntegerIO(const BigInteger &x, Base base)
{
    // Check the base
    if (base < 2 || base > 10)
    {
        cout << "[ERROR] Invalid Base(2): " << base << endl;
        return;
    }

    this->base = base;

    // Get an upper bound on how much space we need
    int maxBitLenOfX = x.getLength() * BigInteger::N;
    int minBitsPerDigit = bitLen(base) - 1;
    int maxDigitLenOfX = ceilingDiv(maxBitLenOfX, minBitsPerDigit);
    mLength = maxDigitLenOfX;
    allocate(mLength);

    BigInteger x_copy(x), buBase(base);
    Index digitNum = 0;

    while (!x_copy.isZero())
    {
        BigInteger lastDigit(x_copy);
        lastDigit.divide(buBase, x_copy);
        block[digitNum] = lastDigit.toUnsignedShort();
        digitNum++;
    }

    // Save the actual length.
    mLength = digitNum;
}

BigIntegerIO::operator BigInteger() const
{
    BigInteger ans, buBase(base), temp;
    Index digitNum = mLength;
    while (digitNum > 0)
    {
        digitNum--;
        temp.multiply(ans, buBase);
        ans.add(temp, BigInteger(block[digitNum]));
    }
    return ans;
}

BigIntegerIO::BigIntegerIO(const std::string &s, Base base)
{
    if (base < 2 || base > 10)
    {
        cout << "[ERROR] Invalid Base(3): " << base << endl;
        return;
    }
    this->base = base;

    mLength = Index(s.length());
    allocate(mLength);

    Index digitNum, symbolNumInString;
    for (digitNum = 0; digitNum < mLength; digitNum++)
    {
        symbolNumInString = mLength - 1 - digitNum;
        char theSymbol = s[symbolNumInString];
        if (theSymbol >= '0' && theSymbol <= '9')
        {
            block[digitNum] = theSymbol - '0';
        }
        else
        {
            cout << "[ERROR] Bad symbol in input. Only 0-9 are accepted";
            return;
        }

        if (block[digitNum] >= base)
        {
            cout << "[ERROR] A digit is too large for the specified base(2)";
            return;
        }
    }
    trimLeadingZeros();
}

BigIntegerIO::operator std::string() const
{
    if (base <2 || base > 10)
    {
        cout << "[ERROR] The default string conversion not supported for the base: " << base << endl;
        return std::string("Invalid Base");
    }
    if (mLength == 0)
    {
        return std::string("0");
    }

    char *s = new char[mLength + 1];
    s[mLength] = '\0';
    Index digitNum, symbolNumInString;
    for (symbolNumInString = 0; symbolNumInString < mLength; symbolNumInString++)
    {
        digitNum = mLength - 1 - symbolNumInString;
        Digit theDigit = block[digitNum];
        s[symbolNumInString] = char('0' + theDigit);
    }

    std::string s_copy(s);
    delete [] s;
    return s_copy;
}

string bigIntegerToString(const BigInteger &x)
{
    return string(BigIntegerIO(x));
}

BigInteger stringToBigInteger(const string &s)
{
    return BigInteger(BigIntegerIO(s));
}

ostream &operator <<(ostream &os, const BigInteger &x)
{
    BigIntegerIO::Base base;
    long osFlags = os.flags();
    if (osFlags & os.dec)
    {
        base = 10;
    }
    else if (osFlags & os.oct)
    {
        base = 8;
        if (osFlags & os.showbase)
        {
            os << '0';
        }
    }
    else
    {
        cout << "[ERROR] Could not determine the desired base from output-stream flags";
        return os;
    }
    string s = string(BigIntegerIO(x, base));
    os << s;
    return os;
}



// ==========================================

// Returns the greatest common divisor of a and b.
BigInteger gcd(BigInteger a, BigInteger b)
{
    BigInteger quotient;
    BigInteger gcd;
    // Neat in-place alternating technique.
    while(1)
    {
        if (b.isZero())
        {
            gcd = a;
            break;
        }
        a.divide(b, quotient);
        if (a.isZero())
        {
            gcd = b;
            break;
        }
        b.divide(a, quotient);
    }
    return gcd;
}

BigInteger factorial(BigInteger a)
{
    unsigned long x = 1;
    BigInteger fact(x);

    while (!a.isZero())
    {
        fact = fact * a;
        a = a - x;
    }
    return fact;
}

BigInteger exponentiation(BigInteger x, BigInteger y)
{
    BigInteger quotient;
    BigInteger t0 = stringToBigInteger("0");
    BigInteger t1 = stringToBigInteger("1");
    BigInteger t2 = stringToBigInteger("2");
    BigInteger result = stringToBigInteger("1");

    while (y > t0)
    {
        // y will hold the remainder after this division
        y.divide(t2, quotient);
        if (!y.isZero())
        {
            result = result * x;
            if (quotient == t1)
            {
                break;
            }
        }
        x = x * x;
        y = quotient;
    }
    return result;
}


// ========================

int main()
{
    // Computing Exponentiation
    unsigned long x = 999;
    unsigned long y = 999;
    BigInteger X(x);
    BigInteger Y(y);
    BigInteger result = exponentiation(X,Y);
    cout << "exp(" << x << "," << y << "): " << result << endl;
    cout << endl;

    // Computing GCD
    string s1("566752498028882558417594189386420690117559384448751654157905634076863498722302201920657508787134402865072743650474134194097117309412827177212973157160061849638167150488562953654589151552451332056806089115372808474969974012036551062752");
    string s2("1447448402632996266959601092923195406769183583922939321424508923901952455864859674545580638544673875329913712841042280444718252896521776423019972072599040280237459554744353957594494429331983696");
    BigInteger b1 = stringToBigInteger(s1);
    BigInteger b2 = stringToBigInteger(s2);
    cout << "\nb1: " << b1 << endl;
    cout << "\nb2: " << b2 << endl;
    cout << "\nGCD(b1,b2): " << gcd(b1,b2) << endl;
    cout << endl;

    // Computing Factorial
    unsigned long f = 1000;
    BigInteger b3(f);
    cout << "factorial(" << f << "): " << factorial(f) << endl;
    cout << endl;

    return 0;
}
