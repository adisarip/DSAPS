
#include <string>
#include <iostream>
#include <chrono>
#include "BigIntegerIO.H"
#include "BigIntegerUtils.H"
using namespace std;

int main()
{
    // Computing Exponentiation
    unsigned long x = 999;
    unsigned long y = 999;
    BigInteger X(x);
    BigInteger Y(y);

    chrono::time_point start = chrono::steady_clock::now();
    BigInteger result = exponentiation(X,Y);
    chrono::time_point end = chrono::steady_clock::now();
    cout << "exp(" << x << "," << y << "): " << result << endl;
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    cout << endl;


    // Computing GCD
    string s1("566752498028882558417594189386420690117559384448751654157905634076863498722302201920657508787134402865072743650474134194097117309412827177212973157160061849638167150488562953654589151552451332056806089115372808474969974012036551062752");
    string s2("1447448402632996266959601092923195406769183583922939321424508923901952455864859674545580638544673875329913712841042280444718252896521776423019972072599040280237459554744353957594494429331983696");
    BigInteger b1 = stringToBigInteger(s1);
    BigInteger b2 = stringToBigInteger(s2);
    cout << "\nb1: " << b1 << endl;
    cout << "\nb2: " << b2 << endl;

    start = chrono::steady_clock::now();
    BigInteger GCD = gcd(b1,b2);
    end = chrono::steady_clock::now();

    cout << "\nGCD(b1,b2): " << GCD << endl;
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << "µs" << endl;
    cout << endl;

    // Computing Factorial
    // factorial using brute force
    unsigned long f = 1000;
    start = chrono::steady_clock::now();
    BigInteger F = factorial(BigInteger(f));
    end = chrono::steady_clock::now();
    cout << "factorial(" << f << "): " << F << endl;
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    cout << endl;

    // factorial using half multiplications
    start = chrono::steady_clock::now();
    F = factorial_half_multiplication(BigInteger(f));
    end = chrono::steady_clock::now();

    cout << "factorial_half_multiplication(" << f << "): " << F << endl;
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    cout << endl;

    // factorial using prime decomposition
    start = chrono::steady_clock::now();
    F = factorial_prime_decomposition(BigInteger(f), f);
    end = chrono::steady_clock::now();
    cout << "factorial_prime_decomposition(" << f << "): " << F << endl;
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    cout << endl;

    return 0;
}
