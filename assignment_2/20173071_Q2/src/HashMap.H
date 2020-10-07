
// A template based implementation of "Unordered-Map" using Hash Table as the internal data structure.
// using chaining to handle the collisions

#ifndef __MAP__
#define __MAP__

//#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

static const int HASH_BUCKET_SIZE    = 101;
static const int MAX_LOAD_PERCENTAGE = 70;

template <typename K, typename V>
class HashMap
{
  public:
    HashMap();
    HashMap(K key, V value);
    ~HashMap();

    class Node
    {
      public:
        Node(K keyParm, V valueParm):key(keyParm),value(valueParm),next(NULL){};
        ~Node(){};
        K     key;
        V     value;
        Node* next;
    };

    void insert(K key, V value);
    V    fetch(K key) const;
    bool find(K key) const;
    void erase(K key);
    V& operator[](K key);
    V  operator[](K key) const;
    // additional features
    int  size() const;
    bool isEmpty() const;
    void clear();

  protected:
    // helper functions
    K keyHash(K key){return key;};
    int   pKeyHash(K key);
    void  pCreateBuckets(int nBuckets);
    void  pDeleteBuckets(vector<Node*>& buckets);
    void  pExpandAndRehash();

  private:
    int nBuckets;
    int numEntries;
    vector<Node*> buckets;

  protected:
    Node* pFindNode(int bucket, K key) const
    {
        Node* dummy = NULL;
        return pFindNode(bucket, key, dummy);
    }
    Node* pFindNode(int bucket, K key, Node* parent) const
    {
        parent = NULL;
        Node* node = buckets.at(bucket);
        while (node != NULL && key != node->key)
        {
            parent = node;
            node = node->next;
        }
        return node;
    }
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
int HashMap<K,V>::size() const
{
   return numEntries;
}

template <typename K,typename V>
bool HashMap<K,V>::isEmpty() const
{
   return (numEntries == 0);
}

template <typename K,typename V>
void HashMap<K,V>::insert(K key, V value)
{
   (*this)[key] = value;
}

template <typename K,typename V>
V HashMap<K,V>::fetch(K key) const
{
   Node* node = pFindNode(pKeyHash(key), key);
   if (node == NULL)
   {
       return V();
   }
   return node->value;
}

template <typename K,typename V>
bool HashMap<K,V>::find(K key) const
{
   return pFindNode(pKeyHash(key), key) != NULL;
}

template <typename K,typename V>
void HashMap<K,V>::erase(K key)
{
    int bucket = pKeyHash(key);
    Node* parent;
    Node* node = pFindNode(bucket, key, parent);
    if (node != NULL)
    {
        if (parent == NULL)
        {
            buckets[bucket] = node->next;
        }
        else
        {
            parent->next = node->next;
        }
        delete node;
        numEntries--;
    }
}

template <typename K,typename V>
void HashMap<K,V>::clear()
{
    pDeleteBuckets(buckets);
    numEntries = 0;
}

template <typename K,typename V>
V& HashMap<K,V>::operator[](K key)
{
    int bucket = pKeyHash(key);
    Node* node = pFindNode(bucket, key);
    if (node == NULL)
    {
        if (numEntries > MAX_LOAD_PERCENTAGE * nBuckets / 100.0)
        {
            pExpandAndRehash();
            bucket = pKeyHash(key);
        }
        V value = V();
        node = new Node(key, value);
        node->next = buckets[bucket];
        buckets[bucket] = node;
        numEntries++;
    }
    return node->value;
}

template <typename K, typename V>
V HashMap<K,V>::operator[](K key) const
{
   return fetch(key);
}


// PROTECTED members definitions

template <typename K,typename V>
int HashMap<K,V>::pKeyHash(K key)
{
    return (keyHash(key) % nBuckets);
}

template <typename K,typename V>
void HashMap<K,V>::pCreateBuckets(int nBuckets)
{
    nBuckets = (nBuckets == 0) ? 1 : nBuckets;
    buckets = vector<Node*> (nBuckets, NULL);
    this->nBuckets = nBuckets;
    numEntries = 0;
}

template <typename K,typename V>
void HashMap<K,V>::pDeleteBuckets(vector<Node*>& buckets)
{
    int bucketsSize = buckets.size();
    for (int i = 0; i < bucketsSize; i++)
    {
        Node* node = buckets[i];
        while (node != NULL)
        {
            Node* tmpNode = node->next;
            delete node;
            node = tmpNode;
        }
        buckets[i] = NULL;
    }
}

template <typename K,typename V>
void HashMap<K,V>::pExpandAndRehash()
{
    vector<Node*> oldBuckets = buckets;
    int oldBucketsSize = oldBuckets.size();
    pCreateBuckets(oldBucketsSize * 2 + 1);
    for (int i = 0; i < oldBucketsSize; i++)
    {
        for (Node* node = oldBuckets[i]; node != NULL; node = node->next)
        {
            insert(node->key, node->value);
        }
    }
    pDeleteBuckets(oldBuckets);
}

#endif
