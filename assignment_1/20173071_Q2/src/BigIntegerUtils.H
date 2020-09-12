#ifndef BIGINTEGERUTILS_H
#define BIGINTEGERUTILS_H

#include "BigInteger.H"

BigInteger exponentiation(BigInteger x, BigInteger y);
BigInteger gcd(BigInteger a, BigInteger b);
BigInteger factorial(BigInteger a);

// Factorial using half multiplications:
// =====================================
// for example
// 8! = 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
// now if you group them together
//
// 8! = (8 * 1) * (7 * 2) * (6 * 3) * (5 * 4)
// Which can be written as
// 8! = 8 * (8 + 8 - 2 = 14) * (14 + 8 - 4 = 18) * (18 + 8 - 6 = 20) . --> 8 * 14 * 18 * 20
// So product of 8 terms reduced to product of 4 terms
BigInteger factorial_half_multiplication(BigInteger a);

BigInteger factorial_prime_decomposition(BigInteger a, unsigned long n);

#endif
