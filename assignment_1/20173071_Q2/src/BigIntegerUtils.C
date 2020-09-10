#include "BigIntegerUtils.H"
#include "BigUnsignedInABase.H"
using namespace std;

string bigUnsignedToString(const BigUnsigned &x)
{
	return string(BigUnsignedInABase(x));
}

BigUnsigned stringToBigUnsigned(const string &s)
{
	return BigUnsigned(BigUnsignedInABase(s));
}

ostream &operator <<(ostream &os, const BigUnsigned &x)
{
	BigUnsignedInABase::Base base;
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
	string s = string(BigUnsignedInABase(x, base));
	os << s;
	return os;
}
