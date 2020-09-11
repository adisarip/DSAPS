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

    // Eliminate any leading zeros we may have been passed.
    trimLeadingZeros();
}

namespace
{
    unsigned int bitLen(unsigned int x)
    {
        unsigned int len = 0;
        while (x > 0)
        {
            x >>= 1;
            len++;
        }
        return len;
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
    len = maxDigitLenOfX; // Another change to comply with `staying in bounds'.
    allocate(len); // Get the space

    BigInteger x_copy(x), buBase(base);
    Index digitNum = 0;

    while (!x_copy.isZero()) {
        // Get last digit.  This is like `lastDigit = x2 % buBase, x2 /= buBase'.
        BigInteger lastDigit(x_copy);
        lastDigit.divide(buBase, x_copy);
        // Save the digit.
        block[digitNum] = lastDigit.toUnsignedShort();
        // Move on.  We can't run out of room: we figured it out above.
        digitNum++;
    }

    // Save the actual length.
    len = digitNum;
}

BigIntegerIO::operator BigInteger() const
{
    BigInteger ans, buBase(base), temp;
    Index digitNum = len;
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
    // Check the base.
    if (base < 2 || base > 10)
    {
        cout << "[ERROR] Invalid Base(3): " << base << endl;
        return;
    }

    // Save the base.
    this->base = base;

    len = Index(s.length());
    allocate(len);

    Index digitNum, symbolNumInString;
    for (digitNum = 0; digitNum < len; digitNum++)
    {
        symbolNumInString = len - 1 - digitNum;
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
    if (base > 10)
    {
        cout << "[ERROR] The default string conversion not supported for base (>10): " << base << endl;
        return std::string("Invalid Base");
    }
    if (len == 0)
    {
        return std::string("0");
    }
    // Some compilers don't have push_back, so use a char * buffer instead.
    char *s = new char[len + 1];
    s[len] = '\0';
    Index digitNum, symbolNumInString;
    for (symbolNumInString = 0; symbolNumInString < len; symbolNumInString++)
    {
        digitNum = len - 1 - symbolNumInString;
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
