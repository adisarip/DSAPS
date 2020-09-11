#include "BigIntegerIO.H"
using namespace std;

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
