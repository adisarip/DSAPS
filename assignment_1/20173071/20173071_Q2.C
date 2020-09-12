
#include <string>
#include <iostream>
using namespace std;

#ifndef NULL
#define NULL 0
#endif

//========================== Class NumberBlockArray : Begin ============================//
// This class implements a heap-allocated array of unsigned long blocks with
// a given length and a capacity and provides basic memory management features.
template <class Block>
class NumberBlockArray
{
  public:
    // member data
    typedef unsigned int Index;
    static const unsigned int N;
    Index mCapacity;
    Index mLength;
    Block *block;

    // memory allocation routines
    void allocate(Index capacity);
    void allocateAndCopy(Index capacity);

    NumberBlockArray(Index c);
    NumberBlockArray();
    ~NumberBlockArray() { delete [] block; }
    NumberBlockArray(const NumberBlockArray<Block> &x);
    NumberBlockArray(const Block *b, Index blockLength);

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
    if (capacity > mCapacity)
    {
        delete [] block;
        mCapacity = capacity;
        block = new Block[mCapacity];
    }
}

template <class Block>
void NumberBlockArray<Block>::allocateAndCopy(Index capacity)
{
    if (capacity > mCapacity)
    {
        Block *oldBlock = block;
        mCapacity = capacity;
        block = new Block[mCapacity];

        for (Index i = 0; i < mLength; i++)
        {
            block[i] = oldBlock[i];
        }
        delete [] oldBlock;
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const NumberBlockArray<Block> &x)
:mLength(x.mLength)
{
    mCapacity = mLength;
    block = new Block[mCapacity];
    for (Index i = 0; i < mLength; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const Block *b, Index blockLength)
:mCapacity(blockLength)
,mLength(blockLength)
{
    block = new Block[mCapacity];
    for (Index i = 0; i < mLength; i++)
    {
        block[i] = b[i];
    }
}

template <class Block>
void NumberBlockArray<Block>::operator=(const NumberBlockArray<Block> &x)
{
    if (this == &x)
    {
        return;
    }
    mLength = x.mLength;
    allocate(mLength);
    for (Index i = 0; i < mLength; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator ==(const NumberBlockArray<Block> &x) const
{
    if (mLength != x.mLength)
    {
        return false;
    }
    else
    {
        for (Index i = 0; i < mLength; i++)
        {
            if (block[i] != x.block[i])
            {
                return false;
            }
        }
        return true;
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator !=(const NumberBlockArray<Block> &x) const
{
    return !operator ==(x);
}

//========================== Class NumberBlockArray : End ============================//

//============================ Class BigInteger : Begin ==============================//
// BigInteger class represents a non-negative integer of size limited only by available
// memory. The number is stored as an dynamic array of unsigned long integers
class BigInteger : public NumberBlockArray<unsigned long>
{
  protected:
    BigInteger(int, Index c) : NumberBlockArray<Block>(0, c) {}
    void trimLeadingZeros();
    template <class X> void setPrimitive (X x);
    template <class X> X getPrimitive () const;

  public:
    enum CompareResult
    {
        LESS    = 1,
        EQUAL   = 2,
        GREATER = 3,
    };
    typedef unsigned long Block;
    typedef NumberBlockArray<Block>::Index Index;

    BigInteger() : NumberBlockArray<Block>() {}
    BigInteger(const BigInteger &x) : NumberBlockArray<Block>(x) {}
    void operator=(const BigInteger &x) { NumberBlockArray<Block>::operator =(x); }
    BigInteger(const Block *b, Index blockLength) : NumberBlockArray<Block>(b, blockLength)
    {
        trimLeadingZeros();
    }

    BigInteger(unsigned long  x) { setPrimitive (x); }
    BigInteger(unsigned short x) { setPrimitive (x); }
    ~BigInteger() {}

    unsigned short toUnsignedShort() const { return getPrimitive <unsigned short>(); }
    bool isZero() const;

    // Overloaded operators
    // Helper function -> Compares *this to x
    CompareResult compare(const BigInteger &x) const;
    // Ordinary comparison operators
    bool operator ==(const BigInteger &x) const { return NumberBlockArray<Block>::operator ==(x); }
    bool operator !=(const BigInteger &x) const { return NumberBlockArray<Block>::operator !=(x); }
    bool operator < (const BigInteger &x) const { return compare(x) == BigInteger::LESS; }
    bool operator <=(const BigInteger &x) const { return compare(x) != BigInteger::GREATER; }
    bool operator >=(const BigInteger &x) const { return compare(x) != BigInteger::LESS; }
    bool operator > (const BigInteger &x) const { return compare(x) == BigInteger::GREATER; }

    // Result of the operation is saved in *this.
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

    // Friend function that needs access to BigInteger internals
    friend Block getShiftedBlock(const BigInteger &num,
                                 Index x,
                                 unsigned int y);

    Block getBlock(Index i) const
    {
        return (i >= mLength) ? 0 : block[i];
    }
    bool getBitState(Index bitIndex) const
    {
        return (getBlock(bitIndex / N) & (Block(1) << (bitIndex % N))) != 0;
    }
};

// Definitions

inline BigInteger BigInteger::operator +(const BigInteger &x) const
{
    BigInteger result;
    result.add(*this, x);
    return result;
}
inline BigInteger BigInteger::operator -(const BigInteger &x) const
{
    BigInteger result;
    result.subtract(*this, x);
    return result;
}
inline BigInteger BigInteger::operator *(const BigInteger &x) const
{
    BigInteger result;
    result.multiply(*this, x);
    return result;
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
    BigInteger result;
    result.bitShiftLeft(*this, b);
    return result;
}
inline BigInteger BigInteger::operator >>(int b) const
{
    BigInteger result;
    result.bitShiftRight(*this, b);
    return result;
}

template <class X>
void BigInteger::setPrimitive(X x)
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
X BigInteger::getPrimitive() const
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

BigInteger::CompareResult BigInteger::compare(const BigInteger &x) const
{
    BigInteger::CompareResult sResult = BigInteger::EQUAL;
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
        for (Index i = mLength; i < 0;)
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

    bool carryIn, carryOut;
    Block temp;
    Index i;

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

    mLength = bigInput->mLength + 1;
    allocate(mLength);

    for (i = 0, carryIn = false; i < smallInput->mLength; i++)
    {
        temp = bigInput->block[i] + smallInput->block[i];
        carryOut = (temp < bigInput->block[i]);
        if (carryIn)
        {
            temp++;
            carryOut |= (temp == 0);
        }
        block[i] = temp;
        carryIn = carryOut;
    }

    for (; i < bigInput->mLength && carryIn; i++)
    {
        temp = bigInput->block[i] + 1;
        carryIn = (temp == 0);
        block[i] = temp;
    }

    for (; i < bigInput->mLength; i++)
    {
        block[i] = bigInput->block[i];
    }

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
        operator =(a);
        return;
    }
    else if (a.mLength < b.mLength)
    {
        cout << "ERROR: Negative result in unsigned calculation" << endl;
        return;
    }

    bool borrowIn, borrowOut;
    Block temp;
    Index i;

    mLength = a.mLength;
    allocate(mLength);

    for (i = 0, borrowIn = false; i < b.mLength; i++)
    {
        temp = a.block[i] - b.block[i];
        borrowOut = (temp > a.block[i]);
        if (borrowIn)
        {
            borrowOut |= (temp == 0);
            temp--;
        }
        block[i] = temp;
        borrowIn = borrowOut;
    }

    for (; i < a.mLength && borrowIn; i++)
    {
        borrowIn = (a.block[i] == 0);
        block[i] = a.block[i] - 1;
    }

    if (borrowIn)
    {
        mLength = 0;
        cout << "ERROR: Negative result in unsigned calculation" << endl;
    }
    else
    {
        for (; i < a.mLength; i++)
        {
            block[i] = a.block[i];
        }
    }
    trimLeadingZeros();
}

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

    if (a.mLength == 0 || b.mLength == 0)
    {
        mLength = 0;
        return;
    }

    Index i, j, k;
    unsigned int i2;
    Block temp;
    bool carryIn, carryOut;

    mLength = a.mLength + b.mLength;
    allocate(mLength);

    for (i = 0; i < mLength; i++)
    {
        block[i] = 0;
    }

    for (i = 0; i < a.mLength; i++)
    {
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

// this->divide(b,q)
// *this <- remainder
//     q <- qoutient
void BigInteger::divide(const BigInteger &b, BigInteger &q)
{
    if (this == &q)
    {
        cout <<  "Cannot write quotient and remainder into the same variable" << endl;
        return;
    }

    if (this == &b || &q == &b)
    {
        BigInteger B(b);
        divide(B, q);
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

    Index i, j, k;
    unsigned int i2;
    Block temp;
    bool borrowIn, borrowOut;
    Index origLen = mLength;

    allocateAndCopy(mLength + 1);

    mLength++;
    block[origLen] = 0;

    Block *subtractionBuffer = new Block[mLength];

    q.mLength = origLen - b.mLength + 1;
    q.allocate(q.mLength);

    for (i = 0; i < q.mLength; i++)
    {
        q.block[i] = 0;
    }

    i = q.mLength;
    while (i > 0)
    {
        i--;
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
                subtractionBuffer[k] = temp;
                borrowIn = borrowOut;
            }
            for (; k < origLen && borrowIn; k++)
            {
                borrowIn = (block[k] == 0);
                subtractionBuffer[k] = block[k] - 1;
            }

            if (!borrowIn)
            {
                q.block[i] |= (Block(1) << i2);
                while (k > i)
                {
                    k--;
                    block[k] = subtractionBuffer[k];
                }
            }
        }
    }

    if (q.block[q.mLength - 1] == 0)
    {
        q.mLength--;
    }

    trimLeadingZeros();
    delete [] subtractionBuffer;
}


void BigInteger::bitShiftLeft(const BigInteger &a, int b)
{
    IF_ALIASED(this == &a, bitShiftLeft(a, b));

    Index shiftBlocks = b / N;
    unsigned int shiftBits = b % N;

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

    if (rightShiftBlocks >= a.mLength + 1)
    {
        mLength = 0;
        return;
    }

    mLength = a.mLength + 1 - rightShiftBlocks;
    allocate(mLength);

    Index i, j;
    for (j = rightShiftBlocks, i = 0; j <= a.mLength; j++, i++)
    {
        block[i] = getShiftedBlock(a, j, leftShiftBits);
    }

    if (block[mLength - 1] == 0)
    {
        mLength--;
    }
}

//============================ Class BigInteger : End ==============================//

//========================== Class BigIntegerIO : Begin ============================//

// string conversion routines. Base 10 only.
string BigIntegerToString(const BigInteger &x);
BigInteger stringToBigInteger(const string &s);
// overloading '<<' operator for printing BinIntger using 'cout'.
ostream &operator <<(ostream &os, const BigInteger &x);

class BigIntegerIO : public NumberBlockArray<unsigned short>
{
  public:
    typedef unsigned short Digit;
    typedef Digit Base;

  protected:
    Base base;
    BigIntegerIO(int, Index c) : NumberBlockArray<Digit>(0, c) {}
    void trimLeadingZeros()
    {
        while (mLength > 0 && block[mLength - 1] == 0)
        {
            mLength--;
        }
    }
    unsigned int bitLen(unsigned int x);
    unsigned int ceilingDiv(unsigned int a, unsigned int b);

  public:
    BigIntegerIO() : NumberBlockArray<Digit>(), base(10) {}
    BigIntegerIO(const BigIntegerIO &x) : NumberBlockArray<Digit>(x), base(x.base) {}
    BigIntegerIO(const Digit *d, Index l, Base base);
    ~BigIntegerIO() {}
    BigIntegerIO(const BigInteger &x, Base base=10);
    BigIntegerIO(const string &s, Base base=10);

    operator string() const;
    operator BigInteger() const;
    void operator =(const BigIntegerIO &x)
    {
        NumberBlockArray<Digit>::operator =(x);
        base = x.base;
    }
    bool operator ==(const BigIntegerIO &x) const
    {
        return base == x.base && NumberBlockArray<Digit>::operator ==(x);
    }
    bool operator !=(const BigIntegerIO &x) const { return !operator ==(x); }

    // Accessing Member data
    Base getBase() const { return base; }
    Digit getDigit(Index i) const { return i >= mLength ? 0 : block[i]; }
    bool isZero() const { return NumberBlockArray<Digit>::isEmpty(); }
};

// Definitions

BigIntegerIO::BigIntegerIO(const Digit *d, Index l, Base base)
:NumberBlockArray<Digit>(d, l)
,base(base)
{
    if (base < 2 || base > 10)
    {
        cout << "[ERROR] Invalid Base(1): " << base << endl;
        return;
    }

    for (Index i = 0; i < l; i++)
    {
        if (block[i] >= base)
        {
            cout << "[ERROR] A digit is too large for the specified base(1)" << endl;
        }
    }

    trimLeadingZeros();
}

unsigned int BigIntegerIO::bitLen(unsigned int x)
{
    unsigned int length = 0;
    while (x > 0)
    {
        x >>= 1;
        length++;
    }
    return length;
}

unsigned int BigIntegerIO::ceilingDiv(unsigned int a, unsigned int b)
{
    return (a + b - 1) / b;
}

BigIntegerIO::BigIntegerIO(const BigInteger &x, Base base)
{
    if (base < 2 || base > 10)
    {
        cout << "[ERROR] Invalid Base(2): " << base << endl;
        return;
    }
    this->base = base;

    int maxBitLenOfX = x.getLength() * BigInteger::N;
    int minBitsPerDigit = bitLen(base) - 1;
    int maxDigitLenOfX = ceilingDiv(maxBitLenOfX, minBitsPerDigit);
    mLength = maxDigitLenOfX;
    allocate(mLength);

    BigInteger x_copy(x), bigUnsignedBase(base);
    Index digitNum = 0;

    while (!x_copy.isZero())
    {
        BigInteger lastDigit(x_copy);
        lastDigit.divide(bigUnsignedBase, x_copy);
        block[digitNum] = lastDigit.toUnsignedShort();
        digitNum++;
    }
    mLength = digitNum;
}

BigIntegerIO::operator BigInteger() const
{
    BigInteger result, temp;
    BigInteger bigUnsignedBase(base);
    Index digitNum = mLength;
    while (digitNum > 0)
    {
        digitNum--;
        temp.multiply(result, bigUnsignedBase);
        result.add(temp, BigInteger(block[digitNum]));
    }
    return result;
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

//========================== Class BigIntegerIO : End ============================//


// Returns the greatest common divisor of a and b.
BigInteger gcd(BigInteger a, BigInteger b)
{
    BigInteger quotient;
    BigInteger gcd;
    while(1)
    {
        if (b.isZero())
        {
            gcd = a;
            break;
        }
        // a will hold the remainder after this division
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
    BigInteger t0 = stringToBigInteger("0");
    BigInteger result = stringToBigInteger("1");

    while (y > t0)
    {
        if (y.getBitState(0) == true)
        {
            // odd number
            result = result * x;
        }
        x = x * x;
        y = y >> 1; // divide by 2
    }
    return result;
}

//====================== Main Driver Program : Begin =====================//

// vector is only used for the driver program
#include <vector>
int main (int argc, char* argv[])
{
    int Q = 0;
    int cmd = 0;
    string a_str("");
    string b_str("");
    BigInteger A, B, result;
    vector<string> outputLines;

    cin >> Q; // read number of queries
    for (int i=0; i<Q; i++)
    {
        cin >> cmd;
        switch (cmd)
        {
            case 1:
                // Exponentiation
                cin >> a_str >> b_str;
                A = stringToBigInteger(a_str);
                B = stringToBigInteger(b_str);
                result = exponentiation(A,B);
                outputLines.push_back(bigIntegerToString(result));
                break;
            case 2:
                // GCD
                cin >> a_str >> b_str;
                A = stringToBigInteger(a_str);
                B = stringToBigInteger(b_str);
                result = gcd(A,B);
                outputLines.push_back(bigIntegerToString(result));
                break;
            case 3:
                // Factorial
                cin >> a_str;
                A = stringToBigInteger(a_str);
                result = factorial(A);
                outputLines.push_back(bigIntegerToString(result));
                break;
            default:
                break;
        };
    }

    for (string s : outputLines)
    {
        cout << s << endl;
    }

    return 0;
}


//====================== Main Driver Program : End =====================//
