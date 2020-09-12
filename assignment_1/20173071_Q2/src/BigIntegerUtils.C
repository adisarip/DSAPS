
#include "BigIntegerUtils.H"
#include "BigIntegerIO.H"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

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

BigInteger factorial_half_multiplication(BigInteger a)
{
    BigInteger t0 = stringToBigInteger("0");
    BigInteger t1 = stringToBigInteger("1");
    BigInteger t2 = stringToBigInteger("2");
    BigInteger factorial = t1;
    if (a == t0 || a == t1)
    {
        // nothing to be done
    }
    else
    {
        bool isOdd = false;
        BigInteger computeUptoNumber = a;
        if (a.getBitState(0) == true)
        {
            isOdd = true;
            computeUptoNumber = computeUptoNumber - t1;
        }

        BigInteger nextSum = computeUptoNumber;
        BigInteger nextMultiplier = computeUptoNumber;
        while(nextSum >= t2)
        {
            factorial = factorial * nextMultiplier;
            nextSum = nextSum - t2;
            nextMultiplier = nextMultiplier + nextSum;
        }

        if (isOdd)
        {
            factorial = factorial * a;
        }
    }
    return factorial;
}

BigInteger factorial_prime_decomposition(BigInteger a, unsigned long n)
{
    BigInteger t1 = stringToBigInteger("1");
    BigInteger factorial = t1;
    BigInteger exp;

    // Prime numbers table
    unsigned long* isPrime = new unsigned long[n+1];
    memset(isPrime, 1, sizeof(unsigned long) * n);

    for (unsigned long i=2; i<n+1; i++)
    {
        if (isPrime[i])
        {
            // update prime table
            unsigned long j = i+i;
            while (j <= n)
            {
                isPrime[j] = 0;
                j = j + i;
            }
            // calculate the number of i's in (n!)
            unsigned long sum = 0;
            unsigned long t = i;
            while (t <= n)
            {
                sum = sum + n/t;
                t = t * i;
            }
             exp = exponentiation(BigInteger(i), BigInteger(sum));
             factorial = factorial * exp;
        }
    }
    return factorial;
}
