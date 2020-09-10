#ifndef NUMBERBLOCKARRAY_H
#define NUMBERBLOCKARRAY_H

// Make sure we have NULL.
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
    Index cap;
    // The actual length of the value stored in this NumberBlockArray (in blocks)
    Index len;
    // Heap-allocated array of the blocks (can be NULL if len == 0)
    Block *block;

    // Constructs a 'zero' NumberBlockArray with the given capacity.
    NumberBlockArray(Index c) : cap(c), len(0)
    {
        block = (cap > 0) ? (new Block[cap]) : NULL;
    }

    // Constructs a zero NumberBlockArray without allocating a Block array.
    NumberBlockArray() : cap(0), len(0)
    {
        block = NULL;
    }

    // Destructor
    ~NumberBlockArray()
    {
        delete [] block;
    }

    // Ensures that the array has at least the requested capacity.
    // may destroy the contents.
    void allocate(Index c);

    // Ensures that the array has at least the requested capacity.
    // does not destroy the contents.
    void allocateAndCopy(Index c);

    // Copy constructor
    NumberBlockArray(const NumberBlockArray<Block> &x);

    // Assignment operator
    void operator=(const NumberBlockArray<Block> &x);

    // Constructor that copies from a given array of blocks
    NumberBlockArray(const Block *b, Index blen);

    // exposing the member data
    Index getCapacity()     const { return cap; }
    Index getLength()       const { return cap; }
    Block getBlock(Index i) const { return block[i];   }
    bool  isEmpty()         const { return len == 0; }

    bool operator ==(const NumberBlockArray<Block> &x) const;
    bool operator !=(const NumberBlockArray<Block> &x) const { return !operator ==(x); }
};


template <class Block>
const unsigned int NumberBlockArray<Block>::N = 8 * sizeof(Block);

template <class Block>
void NumberBlockArray<Block>::allocate(Index c)
{
    // If the requested capacity is more than the current capacity...
    if (c > cap)
    {
        // Delete the old number array
        delete [] block;
        // Allocate the new array
        cap = c;
        block = new Block[cap];
    }
}

template <class Block>
void NumberBlockArray<Block>::allocateAndCopy(Index c)
{
    // If the requested capacity is more than the current capacity...
    if (c > cap)
    {
        Block *oldBlock = block;
        // Allocate the new number array
        cap = c;
        block = new Block[cap];
        // Copy number blocks
        Index i;
        for (i = 0; i < len; i++)
        {
            block[i] = oldBlock[i];
        }
        // Delete the old array
        delete [] oldBlock;
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const NumberBlockArray<Block> &x)
:len(x.len)
{
    // Create array
    cap = len;
    block = new Block[cap];
    // Copy blocks
    Index i;
    for (i = 0; i < len; i++)
    {
        block[i] = x.block[i];
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
    len = x.len;
    allocate(len);

    // Copy number blocks
    Index i;
    for (i = 0; i < len; i++)
    {
        block[i] = x.block[i];
    }
}

template <class Block>
NumberBlockArray<Block>::NumberBlockArray(const Block *b, Index blen)
:cap(blen)
,len(blen)
{
    // Create array
    block = new Block[cap];
    // Copy blocks
    Index i;
    for (i = 0; i < len; i++)
    {
        block[i] = b[i];
    }
}

template <class Block>
bool NumberBlockArray<Block>::operator ==(const NumberBlockArray<Block> &x) const
{
    if (len != x.len)
    {
        // Definitely unequal.
        return false;
    }
    else
    {
        // Compare corresponding blocks one by one.
        Index i;
        for (i = 0; i < len; i++)
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

#endif
