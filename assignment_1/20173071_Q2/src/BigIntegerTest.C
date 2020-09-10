// Sample program demonstrating the use of the Big Integer Library.

// Standard libraries
#include <string>
#include <iostream>

#include "BigIntegerUtils.H"

int main()
{
    /* The library throws `const char *' error messages when things go
     * wrong.  It's a good idea to catch them using a `try' block like this
     * one.  Your C++ compiler might need a command-line option to compile
     * code that uses exceptions. */
    BigUnsigned a; // a is 0
    unsigned long b = 535;

    /* Any primitive integer can be converted implicitly to a
     * BigInteger. */
    a = b;

    BigUnsigned c(a); // Copy a BigInteger.

    // The int literal is converted to a BigInteger.
    unsigned long _d = 314159265;
    BigUnsigned d(_d);

    // Instead you can convert the number from a string.
    //std::string s("3141592653589793238462643383279");
    //BigUnsigned f = stringToBigInteger(s);

    // You can convert the other way too.
    //std::string s2 = bigIntegerToString(f);

    // f is implicitly stringified and sent to std::cout.
    //std::cout << f << std::endl;

    /* Let's do some math!  The library overloads most of the
     * mathematical operators (including assignment operators) to
     * work on BigIntegers.  There are also ``copy-less''
     * operations; see `BigUnsigned.hh' for details. */

    // Arithmetic operators
    unsigned long _g = 314159;
    unsigned long _h = 265;
    BigUnsigned g(_g), h(_h);
    std::cout << (g + h) << '\n'
              << (g - h) << '\n'
              << (g * h) << '\n'
              << (g / h) << '\n'
              << (g % h) << std::endl;

    // Let's do some heavy lifting and calculate powers of 314.
    int maxPower = 10;
    unsigned long _result = 1;
    unsigned long _big314 = 314;
    BigUnsigned result(_result), big314(_big314);
    for (int power = 0; power <= maxPower; power++)
    {
        std::cout << "314^" << power << " = " << result << std::endl;
        result = result * big314; // A BigInteger assignment operator
    }

    // Some big-integer algorithms (albeit on small integers).
    //std::cout << gcd(BigUnsigned(60), 72) << '\n'
    //    << modinv(BigUnsigned(7), 11) << '\n'
    //    << modexp(BigUnsigned(314), 159, 2653) << std::endl;

    // Add your own code here to experiment with the library.

    return 0;
}

/*
The original sample program produces this output:

3141592653589793238462643383279
314424
313894
83252135
1185
134
0xFF
0xFF00FFFF
0xFF00FF00
0x1FFFE00000
0x3F
314^0 = 1
314^1 = 314
314^2 = 98596
314^3 = 30959144
314^4 = 9721171216
314^5 = 3052447761824
314^6 = 958468597212736
314^7 = 300959139524799104
314^8 = 94501169810786918656
314^9 = 29673367320587092457984
314^10 = 9317437338664347031806976
12
8
1931

*/
