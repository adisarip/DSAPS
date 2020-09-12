#include "BigInteger.H"
#include <iostream>
using namespace std;


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

BigInteger::CompareResult BigInteger::compareTo(const BigInteger &x) const
{
    BigInteger::CompareResult sResult = BigInteger::EQUAL;
    // A bigger length implies a bigger number.
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
        // Compare blocks one by one from left to right.
        Index i = mLength;
        while (i > 0)
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
        // If no blocks differed, the numbers are equal.
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

    // Carries IN and OUT
    bool carryIn, carryOut;
    Block temp;
    Index i;

    // bigInput points to the longer input
    // smallInput points to the shorter Input
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

    // Set prelimiary length and make room in this BigInteger
    mLength = bigInput->mLength + 1;
    allocate(mLength);

    // For each block index that is present in both inputs...
    for (i = 0, carryIn = false; i < smallInput->mLength; i++)
    {
        // Add input blocks
        temp = bigInput->block[i] + smallInput->block[i];

        // If a rollover occurred, the result is less than either input.
        carryOut = (temp < bigInput->block[i]);

        // If a carry was input, handle it
        if (carryIn)
        {
            temp++;
            carryOut |= (temp == 0);
        }
        block[i] = temp; // Save the addition result
        carryIn = carryOut; // Pass the carry along
    }

    // If there is a carry left over, increase blocks until
    // one does not roll over.
    for (; i < bigInput->mLength && carryIn; i++)
    {
        temp = bigInput->block[i] + 1;
        carryIn = (temp == 0);
        block[i] = temp;
    }

    // If the carry was resolved but the larger number
    // still has blocks, copy them over.
    for (; i < bigInput->mLength; i++)
    {
        block[i] = bigInput->block[i];
    }

    // Set the extra block if there's still a carry, decrease length otherwise
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
        // If b is zero, copy a.
        operator =(a);
        return;
    }
    else if (a.mLength < b.mLength)
    {
        // If a is shorter than b, the result is negative.
        cout << "ERROR: Negative result in unsigned calculation" << endl;
        return;
    }

    bool borrowIn, borrowOut;
    Block temp;
    Index i;

    // Set preliminary length and make room
    mLength = a.mLength;
    allocate(mLength);

    // For each block index that is present in both inputs...
    for (i = 0, borrowIn = false; i < b.mLength; i++)
    {
        temp = a.block[i] - b.block[i];

        // If a reverse rollover occurred, the result is greater than the block from a.
        borrowOut = (temp > a.block[i]);

        // Handle an incoming borrow
        if (borrowIn)
        {
            borrowOut |= (temp == 0);
            temp--;
        }
        block[i] = temp; // Save the subtraction result
        borrowIn = borrowOut; // Pass the borrow along
    }

    // If there is a borrow left over, decrease blocks until
    // one does not reverse rollover.
    for (; i < a.mLength && borrowIn; i++)
    {
        borrowIn = (a.block[i] == 0);
        block[i] = a.block[i] - 1;
    }
    // If there's still a borrow, the result is negative.
    // print error, but zero out this object.
    if (borrowIn)
    {
        mLength = 0;
        cout << "ERROR: Negative result in unsigned calculation" << endl;
    }
    else
    {
        // Copy over the rest of the blocks
        for (; i < a.mLength; i++)
        {
            block[i] = a.block[i];
        }
    }
    // Trim leading zeros
    trimLeadingZeros();
}

// Multiplication and Division algorithms
// Here we use bit-shifting algorithms for multiplication and division.
// To multiply 'a' and 'b', we zero out the result. Then, for each '1'
// bit in 'a', we shift 'b' left the appropriate amount and add it to
// the result. Similarly, to divide 'a' by 'b', we shift 'b' left varying
// amounts, repeatedly trying to subtract it from 'a'. When we succeed,
// we note the fact by setting a bit in the quotient.

// A helper function used by both the multiplication and the division routines.
// getShiftedBlock() returns the 'x'th block of 'num << y'.
// 'y' may be anything from 0 to N - 1, and 'x' may be anything from
// 0 to 'num.mLength'.

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

    // If either a or b is zero, set to zero.
    if (a.mLength == 0 || b.mLength == 0)
    {
        mLength = 0;
        return;
    }

    // Variables for the calculation
    Index i, j, k;
    unsigned int n;
    Block temp;
    bool carryIn, carryOut;

    // Set preliminary length and make room
    mLength = a.mLength + b.mLength;
    allocate(mLength);

    // Zero out this object
    for (i = 0; i < mLength; i++)
    {
        block[i] = 0;
    }

    // For each block of the first number...
    for (i = 0; i < a.mLength; i++)
    {
        // For each 1-bit of that block...
        for (n = 0; n < N; n++)
        {
            if ((a.block[i] & (Block(1) << n)) == 0)
            {
                continue;
            }

            for (j = 0, k = i, carryIn = false; j <= b.mLength; j++, k++)
            {
                temp = block[k] + getShiftedBlock(b, j, n);
                carryOut = (temp < block[k]);
                if (carryIn)
                {
                    temp++;
                    carryOut |= (temp == 0);
                }
                block[k] = temp;
                carryIn = carryOut;
            }
            // Roll-over a carry as necessary.
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

// DIVISION WITH REMAINDER
// This function mods *this by the given divisor 'b' while storing the
// quotient in the given object 'q' and at the end *this contains the remainder.

void BigInteger::divide(const BigInteger &b, BigInteger &q)
{
    if (this == &q)
    {
        cout <<  "Cannot write quotient and remainder into the same variable" << endl;
        return;
    }

    // If b is aliased to *this or q - use a temporary copy of b
    if (this == &b || &q == &b)
    {
        BigInteger tmpB(b);
        divide(tmpB, q);
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

    // At this point we know this->mLength >= b.mLength > 0

    // Variables for the calculation
    Index i, j, k;
    unsigned int n;
    Block temp;
    bool borrowIn, borrowOut;
    Index origLen = mLength; // Save real length.

    //To avoid an out-of-bounds access in case of reallocation, allocate
    //first and then increment the logical length.
    allocateAndCopy(mLength + 1);

    mLength++;
    block[origLen] = 0; // Zero the added block.

    // subtractBuf holds part of the result of a subtraction; see above.
    Block *subtractBuf = new Block[mLength];

    // Set preliminary length for quotient and make room
    q.mLength = origLen - b.mLength + 1;
    q.allocate(q.mLength);

    // Zero out the quotient
    for (i = 0; i < q.mLength; i++)
    {
        q.block[i] = 0;
    }

    // For each possible left-shift of b in blocks...
    i = q.mLength;
    while (i > 0)
    {
        i--;
        // For each possible left-shift of b in bits...
        // Here 'N' is the number of bits in a Block.
        q.block[i] = 0;
        n = N;
        while (n > 0)
        {
            n--;
            for (j = 0, k = i, borrowIn = false; j <= b.mLength; j++, k++)
            {
                temp = block[k] - getShiftedBlock(b, j, n);
                borrowOut = (temp > block[k]);
                if (borrowIn)
                {
                    borrowOut |= (temp == 0);
                    temp--;
                }
                subtractBuf[k] = temp;
                borrowIn = borrowOut;
            }
            for (; k < origLen && borrowIn; k++)
            {
                borrowIn = (block[k] == 0);
                subtractBuf[k] = block[k] - 1;
            }

            if (!borrowIn)
            {
                q.block[i] |= (Block(1) << n);
                while (k > i)
                {
                    k--;
                    block[k] = subtractBuf[k];
                }
            }
        }
    }

    // Trim possible leading zero in quotient
    if (q.block[q.mLength - 1] == 0)
    {
        q.mLength--;
    }
    // Trim any/all leading zeros in remainder
    trimLeadingZeros();

    // Deallocate subtractBuf.
    delete [] subtractBuf;
}


void BigInteger::bitShiftLeft(const BigInteger &a, int b)
{
    IF_ALIASED(this == &a, bitShiftLeft(a, b));

    Index shiftBlocks = b / N;
    unsigned int shiftBits = b % N;

    // make room for high bits nudged left into another block
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

    // Trim possible leading zero
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

    // Now (N * rightShiftBlocks - leftShiftBits) == b
    // and 0 <= leftShiftBits < N.
    if (rightShiftBlocks >= a.mLength + 1)
    {
        // All of a is guaranteed to be shifted off, even considering the left bit shift
        mLength = 0;
        return;
    }

    // Now we're allocating a positive amount.
    // make room for high bits nudged left into another block
    mLength = a.mLength + 1 - rightShiftBlocks;
    allocate(mLength);

    Index i, j;
    for (j = rightShiftBlocks, i = 0; j <= a.mLength; j++, i++)
    {
        block[i] = getShiftedBlock(a, j, leftShiftBits);
    }

    // Trim possible leading zero
    if (block[mLength - 1] == 0)
    {
        mLength--;
    }
}
