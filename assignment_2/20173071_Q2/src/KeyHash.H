

#ifndef __KEYHASH__
#define __KEYHASH__

#include <string>
using namespace std;

// computing hash keys for various data types

int keyHash(bool key);
int keyHash(char key);
int keyHash(int key);
int keyHash(unsigned int key);
int keyHash(short key);
int keyHash(unsigned short key);
int keyHash(long key);
int keyHash(unsigned long key);
int keyHash(float key);
int keyHash(double key);
int keyHash(long double key);
int keyHash(const char* str);
int keyHash(const std::string& str);

#endif
