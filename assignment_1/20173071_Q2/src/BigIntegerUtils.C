
#include "BigIntegerUtils.H"
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
    BigInteger exp;
    return exp;
}
