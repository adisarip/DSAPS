
// A template based implementation of "Unordered-Map" using Hash Table as the internal data structure.
// using chaining to handle the collisions

#ifndef __MAP__
#define __MAP__

#include "keyHash.H"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
        node = new Node(key, value);
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

#endif
