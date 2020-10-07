
#include "keyHash.H"
#include <iostream>
#include <string>
#include <cstddef> // For size_t
#include <cstring> // For strlen
using namespace std;

static const int KEY_HASH_SEED = 5381;
static const int KEY_HASH_MULTIPLIER = 33;
static const int KEY_HASH_MASK = unsigned(-1) >> 1;


int keyHash(int key)
{
    return key & KEY_HASH_MASK;
}

int keyHash(bool key)
{
    return keyHash(static_cast<int>(key));
}

int keyHash(char key)
{
    return keyHash(static_cast<int>(key));
}

int keyHash(unsigned int key)
{
    return keyHash(static_cast<int>(key));
}

int keyHash(short key)
{
    return keyHash(static_cast<int>(key));
}

int keyHash(unsigned short key)
{
    return keyHash(static_cast<int>(key));
}

int keyHash(long key)
{
    return keyHash(static_cast<int>(key));
}

int keyHash(unsigned long key)
{
    return keyHash(static_cast<int>(key));
}

// This specific algorithm used here is called djb2 after the initials of its inventor,
// Daniel J. Bernstein, Professor of Mathematics at the University of Illinois at Chicago.
// The general method is called "linear congruence", which is also used in random-number generators.
int keyHash(const char* data, size_t numBytes)
{
    unsigned hash = KEY_HASH_SEED;
    for (size_t i = 0; i < numBytes; i++)
    {
        hash = KEY_HASH_MULTIPLIER * hash + data[i];
    }
    return keyHash(hash);
}

int keyHash(const char* str)
{
    return keyHash(str, strlen(str));
}

int keyHash(const string& str)
{
    return keyHash(str.data(), str.length());
}

int keyHash(float key)
{
    return keyHash(reinterpret_cast<const char*> (&key), sizeof(float));
}

int keyHash(double key)
{
    return keyHash(reinterpret_cast<const char*> (&key), sizeof(double));
}

int keyHash(long double key)
{
    return keyHash(reinterpret_cast<const char*> (&key), sizeof(long double));
}
