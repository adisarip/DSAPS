#include "BigUnsigned.H"
#include <iostream>
using namespace std;


void BigUnsigned::trimLeadingZeros()
{
    while (len > 0 && block[len - 1] == 0)
    {
        len--;
    }
}

bool BigUnsigned::isZero() const
{
    return NumberBlockArray::isEmpty();
}

// COMPARISON
BigUnsigned::CmpRes BigUnsigned::compareTo(const BigUnsigned &x) const
{
    // A bigger length implies a bigger number.
    if (len < x.len)
    {
        return less;
    }
    else if (len > x.len)
    {
        return greater;
    }
    else
    {
        // Compare blocks one by one from left to right.
        Index i = len;
        while (i > 0)
        {
            i--;
            if (block[i] == x.block[i])
            {
                continue;
            }
            else if (block[i] > x.block[i])
            {
                return greater;
            }
            else
            {
                return less;
            }
        }
        // If no blocks differed, the numbers are equal.
        return equal;
    }
}

// A repeated check to be performed by all the arithmentic operations
#define IF_ALIASED(cond, op) \
    if (cond) \
    { \
        BigUnsigned tmpThis; \
        tmpThis.op; \
        *this = tmpThis; \
        return; \
    }

void BigUnsigned::add(const BigUnsigned &a, const BigUnsigned &b)
{
    IF_ALIASED(this == &a || this == &b, add(a, b));

    // If one argument is zero, copy the other.
    if (a.len == 0)
    {
        operator =(b);
        return;
    }
    else if (b.len == 0)
    {
        operator =(a);
        return;
    }

    // Carries in and out of an addition stage
    bool carryIn, carryOut;
    Block temp;
    Index i;

    // bigInput points to the longer input
    // smallInput points to the shorter Input
    const BigUnsigned *bigInput, *smallInput;
    if (a.len >= b.len)
    {
        bigInput = &a;
        smallInput = &b;
    }
    else
    {
        bigInput = &b;
        smallInput = &a;
    }

    // Set prelimiary length and make room in this BigUnsigned
    len = bigInput->len + 1;
    allocate(len);

    // For each block index that is present in both inputs...
    for (i = 0, carryIn = false; i < smallInput->len; i++)
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
    for (; i < bigInput->len && carryIn; i++)
    {
        temp = bigInput->block[i] + 1;
        carryIn = (temp == 0);
        block[i] = temp;
    }

    // If the carry was resolved but the larger number
    // still has blocks, copy them over.
    for (; i < bigInput->len; i++)
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
        len--;
    }
}


void BigUnsigned::subtract(const BigUnsigned &a, const BigUnsigned &b)
{
    IF_ALIASED(this == &a || this == &b, subtract(a, b));

    if (b.len == 0)
    {
        // If b is zero, copy a.
        operator =(a);
        return;
    }
    else if (a.len < b.len)
    {
        // If a is shorter than b, the result is negative.
        cout << "ERROR: Negative result in unsigned calculation" << endl;
        return;
    }

    bool borrowIn, borrowOut;
    Block temp;
    Index i;

    // Set preliminary length and make room
    len = a.len;
    allocate(len);

    // For each block index that is present in both inputs...
    for (i = 0, borrowIn = false; i < b.len; i++)
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
    for (; i < a.len && borrowIn; i++)
    {
        borrowIn = (a.block[i] == 0);
        block[i] = a.block[i] - 1;
    }
    // If there's still a borrow, the result is negative.
    // print error, but zero out this object.
    if (borrowIn)
    {
        len = 0;
        cout << "ERROR: Negative result in unsigned calculation" << endl;
    }
    else
    {
        // Copy over the rest of the blocks
        for (; i < a.len; i++)
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
// 0 to 'num.len'.

inline BigUnsigned::Block getShiftedBlock(const BigUnsigned &num,
                                          BigUnsigned::Index x,
                                          unsigned int y)
{
    BigUnsigned::Block part1 = (x == 0 || y == 0) ? 0 : (num.block[x - 1] >> (BigUnsigned::N - y));
    BigUnsigned::Block part2 = (x == num.len) ? 0 : (num.block[x] << y);
    return part1 | part2;
}

void BigUnsigned::multiply(const BigUnsigned &a, const BigUnsigned &b)
{
    IF_ALIASED(this == &a || this == &b, multiply(a, b));

    // If either a or b is zero, set to zero.
    if (a.len == 0 || b.len == 0)
    {
        len = 0;
        return;
    }

    // Variables for the calculation
    Index i, j, k;
    unsigned int i2;
    Block temp;
    bool carryIn, carryOut;

    // Set preliminary length and make room
    len = a.len + b.len;
    allocate(len);

    // Zero out this object
    for (i = 0; i < len; i++)
    {
        block[i] = 0;
    }

    // For each block of the first number...
    for (i = 0; i < a.len; i++)
    {
        // For each 1-bit of that block...
        for (i2 = 0; i2 < N; i2++)
        {
            if ((a.block[i] & (Block(1) << i2)) == 0)
            {
                continue;
            }

            for (j = 0, k = i, carryIn = false; j <= b.len; j++, k++)
            {
                temp = block[k] + getShiftedBlock(b, j, i2);
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
    if (block[len - 1] == 0)
    {
        len--;
    }
}

// DIVISION WITH REMAINDER
// This function mods *this by the given divisor 'b' while storing the
// quotient in the given object 'q' and at the end *this contains the remainder.

void BigUnsigned::divide(const BigUnsigned &b, BigUnsigned &q)
{
    if (this == &q)
    {
        cout <<  "Cannot write quotient and remainder into the same variable" << endl;
        return;
    }

    // If b is aliased to *this or q - use a temporary copy of b
    if (this == &b || &q == &b)
    {
        BigUnsigned tmpB(b);
        divide(tmpB, q);
        return;
    }

    if (b.len == 0)
    {
        q.len = 0;
        return;
    }

    if (len < b.len)
    {
        q.len = 0;
        return;
    }

    // At this point we know this->len >= b.len > 0

    // Variables for the calculation
    Index i, j, k;
    unsigned int i2;
    Block temp;
    bool borrowIn, borrowOut;
    Index origLen = len; // Save real length.

    //To avoid an out-of-bounds access in case of reallocation, allocate
    //first and then increment the logical length.
    allocateAndCopy(len + 1);

    len++;
    block[origLen] = 0; // Zero the added block.

    // subtractBuf holds part of the result of a subtraction; see above.
    Block *subtractBuf = new Block[len];

    // Set preliminary length for quotient and make room
    q.len = origLen - b.len + 1;
    q.allocate(q.len);

    // Zero out the quotient
    for (i = 0; i < q.len; i++)
    {
        q.block[i] = 0;
    }

    // For each possible left-shift of b in blocks...
    i = q.len;
    while (i > 0)
    {
        i--;
        // For each possible left-shift of b in bits...
        // Here 'N' is the number of bits in a Block.
        q.block[i] = 0;
        i2 = N;
        while (i2 > 0)
        {
            i2--;
            for (j = 0, k = i, borrowIn = false; j <= b.len; j++, k++)
            {
                temp = block[k] - getShiftedBlock(b, j, i2);
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
                q.block[i] |= (Block(1) << i2);
                while (k > i)
                {
                    k--;
                    block[k] = subtractBuf[k];
                }
            }
        }
    }

    // Trim possible leading zero in quotient
    if (q.block[q.len - 1] == 0)
    {
        q.len--;
    }
    // Trim any/all leading zeros in remainder
    trimLeadingZeros();

    // Deallocate subtractBuf.
    delete [] subtractBuf;
}


void BigUnsigned::bitShiftLeft(const BigUnsigned &a, int b)
{
    IF_ALIASED(this == &a, bitShiftLeft(a, b));

    Index shiftBlocks = b / N;
    unsigned int shiftBits = b % N;

    // make room for high bits nudged left into another block
    len = a.len + shiftBlocks + 1;
    allocate(len);

    Index i, j;
    for (i = 0; i < shiftBlocks; i++)
    {
        block[i] = 0;
    }

    for (j = 0, i = shiftBlocks; j <= a.len; j++, i++)
    {
        block[i] = getShiftedBlock(a, j, shiftBits);
    }

    // Trim possible leading zero
    if (block[len - 1] == 0)
    {
        len--;
    }
}


void BigUnsigned::bitShiftRight(const BigUnsigned &a, int b)
{
    IF_ALIASED(this == &a, bitShiftRight(a, b));

    Index rightShiftBlocks = (b + N - 1) / N;
    unsigned int leftShiftBits = N * rightShiftBlocks - b;

    // Now (N * rightShiftBlocks - leftShiftBits) == b
    // and 0 <= leftShiftBits < N.
    if (rightShiftBlocks >= a.len + 1)
    {
        // All of a is guaranteed to be shifted off, even considering the left bit shift
        len = 0;
        return;
    }

    // Now we're allocating a positive amount.
    // make room for high bits nudged left into another block
    len = a.len + 1 - rightShiftBlocks;
    allocate(len);

    Index i, j;
    for (j = rightShiftBlocks, i = 0; j <= a.len; j++, i++)
    {
        block[i] = getShiftedBlock(a, j, leftShiftBits);
    }

    // Trim possible leading zero
    if (block[len - 1] == 0)
    {
        len--;
    }
}
