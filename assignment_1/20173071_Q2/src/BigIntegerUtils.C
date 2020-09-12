
#include "BigIntegerUtils.H"
#include "BigIntegerIO.H"
#include <string>
#include <iostream>
using namespace std;

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
        y = y >> 1;
    }
    return result;
}
