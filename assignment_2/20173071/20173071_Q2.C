

#include <iostream>
#include <cstddef> // For size_t
#include <cstring> // For strlen
#include <string>
#include <vector>
using namespace std;

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Hashing Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //

static const int KEY_HASH_SEED = 5381;
static const int KEY_HASH_MULTIPLIER = 33;
static const int KEY_HASH_MASK = unsigned(-1) >> 1;

// computing hash keys for various data types
int keyHash(int key) { return key & KEY_HASH_MASK; }
int keyHash(bool key) { return keyHash(static_cast<int>(key)); }
int keyHash(char key) { return keyHash(static_cast<int>(key)); }
int keyHash(unsigned int key) { return keyHash(static_cast<int>(key)); }
int keyHash(short key) { return keyHash(static_cast<int>(key)); }
int keyHash(unsigned short key) { return keyHash(static_cast<int>(key)); }
int keyHash(long key) { return keyHash(static_cast<int>(key)); }
int keyHash(unsigned long key) { return keyHash(static_cast<int>(key)); }
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
int keyHash(const char* str) { return keyHash(str, strlen(str)); }
int keyHash(const string& str) { return keyHash(str.data(), str.length()); }
int keyHash(float key) { return keyHash(reinterpret_cast<const char*> (&key), sizeof(float)); }
int keyHash(double key) { return keyHash(reinterpret_cast<const char*> (&key), sizeof(double)); }
int keyHash(long double key) { return keyHash(reinterpret_cast<const char*> (&key), sizeof(long double)); }


// >>>>>>>>>>>>>>>>>>>>>>>>> Unordered Map (Hash Table) Implementation <<<<<<<<<<<<<<<<<<<<<<<<< //

static const int HASH_BUCKET_SIZE    = 101;
static const int MAX_LOAD_PERCENTAGE = 70;

// A node in the Hash Table
template <typename K, typename V>
class Node
{
  public:
    Node(K keyParm, V valueParm):key(keyParm),value(valueParm),next(NULL){};
    ~Node(){};
    K     key;
    V     value;
    Node<K,V>* next;
};


template <typename K, typename V>
class HashMap
{
  public:
    HashMap();
    HashMap(K key, V value);
    ~HashMap();

    void insert(K key, V value);
    V    fetch(K key);
    bool find(K key);
    void erase(K key);
    V& operator[](K key);
    V  operator[](K key) const;
    // additional features
    int  size() const;
    bool isEmpty() const;
    void clear();
    void print();

  protected:
    // helper functions
    int   pKeyHash(K key);
    void  pCreateBuckets(int bucketsCount);
    void  pDeleteBuckets(vector<Node<K,V>*>& buckets);
    void  pExpandAndReHash();
    Node<K,V>* pFindNode(int bucket, K key) const;
    Node<K,V>* pFindNode(int bucket, K key, Node<K,V>* prevNode) const;

  private:
    int nBuckets;
    int nEntries;
    vector<Node<K,V>*> buckets;
};

// PUBLIC definitions

template <typename K,typename V>
HashMap<K,V>::HashMap()
{
    pCreateBuckets(HASH_BUCKET_SIZE);
}

template <typename K,typename V>
HashMap<K,V>::HashMap(K key, V value)
{
    pCreateBuckets(HASH_BUCKET_SIZE);
    insert(key, value);
}

template <typename K,typename V>
HashMap<K,V>::~HashMap()
{
    clear();
}

template <typename K,typename V>
void HashMap<K,V>::insert(K key, V value)
{
    (*this)[key] = value;
}

template <typename K,typename V>
V HashMap<K,V>::fetch(K key)
{
    int hash = pKeyHash(key);
    Node<K,V>* node = pFindNode(hash, key);
    if (node == NULL)
    {
        return V();
    }
    return node->value;
}

template <typename K,typename V>
bool HashMap<K,V>::find(K key)
{
    int hash = pKeyHash(key);
    return pFindNode(hash, key) != NULL;
}

template <typename K,typename V>
void HashMap<K,V>::erase(K key)
{
    int bucket = pKeyHash(key);
    Node<K,V>* prevNode = NULL;
    Node<K,V>* node = pFindNode(bucket, key, prevNode);
    if (node != NULL)
    {
        if (prevNode == NULL)
        {
            buckets[bucket] = node->next;
        }
        else
        {
            prevNode->next = node->next;
        }
        delete node;
        nEntries--;
    }
}

template <typename K,typename V>
V& HashMap<K,V>::operator[](K key)
{
    int bucket = pKeyHash(key);
    Node<K,V>* node = pFindNode(bucket, key);
    if (node == NULL)
    {
        if (nEntries > MAX_LOAD_PERCENTAGE * nBuckets / 100.0)
        {
            pExpandAndReHash();
            bucket = pKeyHash(key);
        }
        V value = V();
        node = new Node<K,V>(key, value);
        node->next = buckets[bucket];
        buckets[bucket] = node;
        nEntries++;
    }
    return node->value;
}

template <typename K, typename V>
V HashMap<K,V>::operator[](K key) const
{
   return fetch(key);
}

template <typename K,typename V>
int HashMap<K,V>::size() const
{
    return nEntries;
}

template <typename K,typename V>
bool HashMap<K,V>::isEmpty() const
{
    return (nEntries == 0);
}

template <typename K,typename V>
void HashMap<K,V>::clear()
{
    pDeleteBuckets(buckets);
    nBuckets = 0;
    nEntries = 0;
}

template <typename K,typename V>
void HashMap<K,V>::print()
{
    int bucketsSize = buckets.size();
    for (int i = 0; i < bucketsSize; i++)
    {
        Node<K,V>* node = buckets[i];
        if (node != NULL)
        {
            cout << "[" << i << "]: ";
            while (node != NULL)
            {
                cout << "(" << node->key << "," << node->value << ") ";
                node = node->next;
            }
            cout << endl;
        }
    }
}

// PROTECTED members definitions

template <typename K,typename V>
int HashMap<K,V>::pKeyHash(K key)
{
    int hash = keyHash(key);
    return (hash % nBuckets);
}

template <typename K,typename V>
void HashMap<K,V>::pCreateBuckets(int bucketsCount)
{
    bucketsCount = (bucketsCount == 0) ? 1 : bucketsCount;
    buckets = vector<Node<K,V>*> (bucketsCount, NULL);
    this->nBuckets = bucketsCount;
    nEntries = 0;
}

template <typename K,typename V>
void HashMap<K,V>::pDeleteBuckets(vector<Node<K,V>*>& buckets)
{
    int bucketsSize = buckets.size();
    for (int i = 0; i < bucketsSize; i++)
    {
        Node<K,V>* node = buckets[i];
        while (node != NULL)
        {
            Node<K,V>* tmpNode = node->next;
            delete node;
            node = tmpNode;
        }
        buckets[i] = NULL;
    }
}

template <typename K,typename V>
void HashMap<K,V>::pExpandAndReHash()
{
    vector<Node<K,V>*> oldBuckets = buckets;
    int oldBucketsSize = oldBuckets.size();
    pCreateBuckets(oldBucketsSize * 2 + 1);
    for (int i = 0; i < oldBucketsSize; i++)
    {
        for (Node<K,V>* node = oldBuckets[i]; node != NULL; node = node->next)
        {
            insert(node->key, node->value);
        }
    }
    pDeleteBuckets(oldBuckets);
}

template <typename K,typename V>
Node<K,V>* HashMap<K,V>::pFindNode(int bucket, K key) const
{
    Node<K,V>* dummy = NULL;
    return pFindNode(bucket, key, dummy);
}

template <typename K,typename V>
Node<K,V>* HashMap<K,V>::pFindNode(int bucket, K key, Node<K,V>* prevNode) const
{
    prevNode = NULL;
    Node<K,V>* node = NULL;
    try
    {
        node = buckets.at(bucket);
    }
    catch(...)
    {
        node = NULL;
    }

    while (node != NULL && key != node->key)
    {
        prevNode = node;
        node = node->next;
    }
    return node;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DRIVER PROGRAM <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //

// Test the functionality of the HashMap Class

int main (int argc, char* argv[])
{
    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Testing Unordered Map (HashMap) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    string aditya = "Aditya";
    string laasya = "Laasya";
    string lahari = "Lahari";
    string anusha = "Anusha";
    string chandu = "Chandu";
    string vishwa = "Vishwanath";

    HashMap<string, int> sHashMap(aditya, 1984);
    sHashMap[laasya] = 1990;
    cout << "HASHMAP[Lahari] = " << sHashMap[lahari] << endl;
    cout << "SIZE() = " << sHashMap.size() << endl;
    sHashMap.insert(lahari, 1994);
    sHashMap.insert(anusha, 1990);
    sHashMap[chandu] = 1984;
    sHashMap[vishwa] = 1981;
    cout << "HASHMAP[Lahari] = " << sHashMap.fetch(lahari) << endl;
    cout << "HASHMAP[Anusha] = " << sHashMap.fetch(anusha) << endl;
    cout << "SIZE() = " << sHashMap.size() << endl;
    sHashMap.print();
    cout << "\nErasing Chandu ...\n" << endl;
    sHashMap.erase(chandu);
    sHashMap.print();
    cout << endl;
    cout << "FIND(Lahari) = " << sHashMap.find(lahari) << endl;
    cout << "FIND(Aditya) = " << sHashMap.find(aditya) << endl;
    cout << "FIND(Chandu) = " << sHashMap.find(chandu) << endl;
    cout << "SIZE() = " << sHashMap.size() << endl;
    cout << endl;
    cout << "Updating data in HasMap ...\n" << endl;
    sHashMap.insert(aditya, 1994);
    sHashMap.insert(laasya, 2004);
    sHashMap.insert(lahari, 2002);
    sHashMap.insert(string("ashuna"), 1987);
    sHashMap.insert(aditya, 2006);
    sHashMap.print();
    return 0;
}
