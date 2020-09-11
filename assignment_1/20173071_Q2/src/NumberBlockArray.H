#ifndef NUMBERBLOCKARRAY_H
#define NUMBERBLOCKARRAY_H

#ifndef NULL
#define NULL 0
#endif


// This class implements a heap-allocated array of unsigned long blocks with
// a given length and a capacity and provides basic memory management features.
template <class Block>
class NumberBlockArray
{
  public:
    // Type for the index of a block in the array
    typedef unsigned int Index;
    // The number of bits in a block, defined below.
    static const unsigned int N;
    // The current allocated capacity of this NumberBlockArray (in blocks)
    Index mCapacity;
    // The actual length of the value stored in this NumberBlockArray (in blocks)
    Index mLength;
    // Heap-allocated array of the blocks
    Block *block;

    // Constructs a 'zero' NumberBlockArray with the given capacity.
    NumberBlockArray(Index c);
    // Constructs a zero NumberBlockArray without allocating a Block array.
    NumberBlockArray();
    // Destructor
    ~NumberBlockArray() { delete [] block; }
    // Ensures that the array has at least the requested capacity.
    // may destroy the contents.
    void allocate(Index c);
    // Ensures that the array has at least the requested capacity.
    // does not destroy the contents.
    void allocateAndCopy(Index c);
    // Copy constructor
    NumberBlockArray(const NumberBlockArray<Block> &x);
    // Constructor that copies from a given array of blocks
    NumberBlockArray(const Block *b, Index blen);

    // exposing the member data
    Index getCapacity()     const { return mCapacity; }
    Index getLength()       const { return mCapacity; }
    Block getBlock(Index i) const { return block[i];   }
    bool  isEmpty()         const { return mLength == 0; }

    // Assignment operator
    void operator=(const NumberBlockArray<Block> &x);
    bool operator ==(const NumberBlockArray<Block> &x) const;
    bool operator !=(const NumberBlockArray<Block> &x) const;
};

template <class Block>
const unsigned int NumberBlockArray<Block>::N = 8 * sizeof(Block);

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(Index c)
:mCapacity(c),
mLength(0)
{
    block = (mCapacity > 0) ? (new Block[mCapacity]) : NULL;
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray()
:mCapacity(0),
mLength(0)
{
    block = NULL;
}

template <class Block>
void NumberBlockArray<Block>::allocate(Index c)
{
    // If the requested capacity is more than the current capacity...
    if (c > mCapacity)
    {
        // Delete the old number array
        delete [] block;
        // Allocate the new array
        mCapacity = c;
        block = new Block[mCapacity];
    }
}

template <class Block>
void NumberBlockArray<Block>::allocateAndCopy(Index c)
{
    // If the requested capacity is more than the current capacity...
    if (c > mCapacity)
    {
        Block *oldBlock = block;
        // Allocate the new number array
        mCapacity = c;
        block = new Block[mCapacity];
        // Copy number blocks
        Index i;
        for (i = 0; i < mLength; i++)
        {
            block[i] = oldBlock[i];
        }
        // Delete the old array
        delete [] oldBlock;
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const NumberBlockArray<Block> &x)
:mLength(x.mLength)
{
    // Create array
    mCapacity = mLength;
    block = new Block[mCapacity];
    // Copy blocks
    Index i;
    for (i = 0; i < mLength; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const Block *b, Index blen)
:mCapacity(blen)
,mLength(blen)
{
    // Create array
    block = new Block[mCapacity];
    // Copy blocks
    Index i;
    for (i = 0; i < mLength; i++)
    {
        block[i] = b[i];
    }
}

template <class Block>
void NumberBlockArray<Block>::operator=(const NumberBlockArray<Block> &x)
{
    // Calls like a = a have no effect
    if (this == &x)
    {
        return;
    }

    // Copy length & Expand array if necessary
    mLength = x.mLength;
    allocate(mLength);

    // Copy number blocks
    Index i;
    for (i = 0; i < mLength; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator ==(const NumberBlockArray<Block> &x) const
{
    if (mLength != x.mLength)
    {
        // Definitely unequal.
        return false;
    }
    else
    {
        // Compare corresponding blocks one by one.
        Index i;
        for (i = 0; i < mLength; i++)
        {
            if (block[i] != x.block[i])
            {
                return false;
            }
        }
        // No blocks differed, so the objects are equal.
        return true;
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator !=(const NumberBlockArray<Block> &x) const
{
    return !operator ==(x);
}

#endif
