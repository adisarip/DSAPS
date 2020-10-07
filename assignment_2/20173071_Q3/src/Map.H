
// A template based implementation of "Ordered-Map" using AVL Tree as the internal Balanced BST

#ifndef __MAP__
#define __MAP__

#include <iostream>
#include <string>
using namespace std;


template <class K, class V>
class Node
{
  public:
    inline Node(K keyParm, V value)
    :key(keyParm),data(value),height(0),parent(NULL),left(NULL),right(NULL){};
    inline ~Node(){};

    K key;  // key to index the data
    V data;   // Node Data
    int height;
    Node<K,V>* parent;
    Node<K,V>* left;
    Node<K,V>* right;
};

template <class K, class V>
class Map
{
  public:
    Map();
    Map(K key, const V& value);
    ~Map();
    void insert(K key, V value);
    void erase(K key);
    bool find(K key);
    V& operator[](K index);
    int size();   // return number of keys present in the Map
    void clear(); // remove all the elements from the Map
    void print();
    void display(bool detailFlag=false);

  protected:
    inline int pMax(int x, int y)
    {
        return (x>y) ? x : y;
    };
    inline int pGetHeight(const Node<K,V>* node)
    {
        return ((node) ? node->height : -1);
    };
    // Balance factor of any node is defined as: HEIGHT(left subtree) - HEIGHT(right subtree).
    inline int pGetBalance(const Node<K,V>* node)
    {
        return ((node) ? (pGetHeight(node->left) - pGetHeight(node->right)) : 0);
    };
    Node<K,V>* pGetMinNode(Node<K,V>* node);
    Node<K,V>* pGetMaxNode(Node<K,V>* node);
    void pLeftRotate(Node<K,V>* x);
    void pRightRotate(Node<K,V>* x);
    void pBalanceAVLInsert(Node<K,V>* node); // Balance AVL Tree after insert
    void pTransplant(Node<K,V>* x, Node<K,V>* y);
    void pBalanceAVLDelete(Node<K,V>* node); // Balance AVL Tree after delete
    void pDisplayTree(const string& prefix,
                      const Node<K,V>* node,
                      bool isLeft,
                      bool detailFlag=false);
    void pInOrderPrint(Node<K,V>* node);
    void pPostOrderDelete(Node<K,V>* node);

  private:
    int nodeCount;
    Node<K,V>* root;
};

template <class K, class V>
Map<K,V>::Map()
:nodeCount(0)
,root(NULL)
{
}

template <class K, class V>
Map<K,V>::Map(K key, const V& value)
{
    root = new Node<K,V>(key, value);
    nodeCount++;
}

template <class K, class V>
Map<K,V>::~Map()
{
    clear();
}

template <class K, class V>
void Map<K,V>::print()
{
    // print in-order traversal of the tree
    pInOrderPrint(root);
    cout << endl;
}

template <class K, class V>
void Map<K,V>::display(bool detailFlag)
{
    pDisplayTree("", root, false, detailFlag);
}

// INSERT A NODE

template <class K, class V>
void Map<K,V>::insert(K key, V value)
{
    bool isDuplicateKey = false;
    Node<K,V>* x = root; // x => used to traverse the tree
    Node<K,V>* y = NULL; // stores the position of new node's parent node

    // traverse the tree to get the insert location
    while (x != NULL)
    {
        y = x;
        if (key == x->key)
        {
            isDuplicateKey = true;
            break;
        }
        else if (key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    // y holds the insert location here
    if (isDuplicateKey)
    {
        // no need to create new node. replace the contents
        y->data = value;
    }
    else
    {
        Node<K,V>* node = new Node<K,V>(key, value);
        node->parent = y;
        if (y == NULL)
        {
            root = node;
        }
        else if (node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
        pBalanceAVLInsert(node);
        nodeCount++;
    }
}


template <class K, class V>
void Map<K,V>::erase(K key)
{
    Node<K,V>* x = root; // to traverse the tree
    while (x != NULL)
    {
        if (key < x->key)
        {
            x = x->left;
        }
        else if (key > x->key)
        {
            x = x->right;
        }
        else
        {
            break; // key == x->key
        }
    }

    if (x != NULL)
    {
        if (x->left == NULL)
        {
            pTransplant(x, x->right);
            if (x->right != NULL)
            {
                pBalanceAVLDelete(x->right);
            }
            delete(x);
        }
        else if (x->right == NULL)
        {
            pTransplant(x, x->left);
            if (x->left != NULL)
            {
                pBalanceAVLDelete(x->left);
            }
            delete(x);
        }
        else
        {
            Node<K,V>* y = pGetMinNode(x->right); // get minimum node in right subtree
            if (y->parent != x)
            {
                pTransplant(y, y->right);
                y->right = x->right;
                y->right->parent = y;
            }
            pTransplant(x, y);
            y->left = x->left;
            y->left->parent = y;
            if(y != NULL)
            {
                pBalanceAVLDelete(y);
            }
            delete(x);
        }
        nodeCount--;
    }
    else
    {
        cout << "Node with key:" << key << " not found." << endl;
    }
}

template <class K, class V>
bool Map<K,V>::find(K key)
{
    bool isPresent = true;
    Node<K,V>* x = root; // to traverse the tree
    while (x != NULL)
    {
        if (key < x->key)
        {
            x = x->left;
        }
        else if (key > x->key)
        {
            x = x->right;
        }
        else
        {
            break; // key == x->key
        }
    }

    if (x == NULL)
    {
        isPresent = false;
    }
    return isPresent;
}

template <class K, class V>
V& Map<K,V>::operator[](K index)
{
    // overload subscript operator
    bool isKeyPresent = false;
    Node<K,V>* x = root; // x => used to traverse the tree
    Node<K,V>* y = NULL; // stores the position of new node's parent node
    Node<K,V>* z = NULL; // to return

    // traverse the tree to get the insert location
    while (x != NULL)
    {
        y = x;
        if (index == x->key)
        {
            isKeyPresent = true;
            break;
        }
        else if (index < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    // y holds the insert location here
    if (isKeyPresent)
    {
        // return the node data reference
        z = y;
    }
    else
    {
        V tmpValue;
        V& tmpRef = tmpValue;
        Node<K,V>* node = new Node<K,V>(index, tmpRef);
        node->parent = y;
        if (y == NULL)
        {
            root = node;
        }
        else if (node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
        pBalanceAVLInsert(node);
        nodeCount++;
        z = node;
    }
    return z->data;
}

template <class K, class V>
int Map<K,V>::size()
{
    return nodeCount;
}

template <class K, class V>
void Map<K,V>::clear()
{
    // implement post-order-delete of nodes
    pPostOrderDelete(root);
    cout << "ALL NODES DELETED" << endl;
}


// PROTECTED Helper functions

template <class K, class V>
Node<K,V>* Map<K,V>::pGetMinNode(Node<K,V>* node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <class K, class V>
Node<K,V>* Map<K,V>::pGetMaxNode(Node<K,V>* node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

template <class K, class V>
void Map<K,V>::pLeftRotate(Node<K,V>* x)
{
    Node<K,V>* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
    	y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL)
    {
    	root = y;
    }
    else if (x == x->parent->left)
    {
    	x->parent->left = y;
    }
    else
    {
    	x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

    // update the heights
    x->height = 1 + pMax(pGetHeight(x->left), pGetHeight(x->right));
    y->height = 1 + pMax(pGetHeight(y->left), pGetHeight(y->right));
}


template <class K, class V>
void Map<K,V>::pRightRotate(Node<K,V>* x)
{
    Node<K,V>* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
    {
    	y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL)
    {
    	root = y;
    }
    else if (x == x->parent->right)
    {
    	x->parent->right = y;
    }
    else
    {
    	x->parent->left = y;
    }

    y->right = x;
    x->parent = y;

    // update the heights
    x->height = 1 + pMax(pGetHeight(x->left), pGetHeight(x->right));
    y->height = 1 + pMax(pGetHeight(y->left), pGetHeight(y->right));
}

template <class K, class V>
void Map<K,V>::pBalanceAVLInsert(Node<K,V>* node)
{
    Node<K,V>* y = node->parent;
    Node<K,V>* z = node;

    while (y != NULL)
    {
        y->height = 1 + pMax(pGetHeight(y->left), pGetHeight(y->right));

        Node<K,V>* x = y->parent;
        if (pGetBalance(x) <= -2 || pGetBalance(x) >= 2)
        {
            if(y == x->left)
            {
                if(z == x->left->left)
                {
                    pRightRotate(x);
                }
                else if(z == x->left->right)
                {
                    pLeftRotate(y);
                    pRightRotate(x);
                }
            }
            else if (y == x->right)
            {
                if(z == x->right->right)
                {
                    pLeftRotate(x);
                }
                else if(z == x->right->left)
                {
                    pRightRotate(y);
                    pLeftRotate(x);
                }
            }
            break;
        }
        y = y->parent;
        z = z->parent;
    }
}

// move y-subtree to x
template <class K, class V>
void Map<K,V>::pTransplant(Node<K,V>* x, Node<K,V>* y)
{
    if (x->parent == NULL)
    {
        // x is root node
        root = y;
    }
    else if (x == x->parent->left)
    {
        // x is the left child
        x->parent->left = y;
    }
    else if (x == x->parent->right)
    {
        // x is the right child
        x->parent->right = y;
    }

    if (y != NULL)
    {
        y->parent = x->parent;
    }
}

template <class K, class V>
void Map<K,V>::pBalanceAVLDelete(Node<K,V>* node)
{
    Node<K,V>* p = node;

    while (p != NULL)
    {
        p->height = 1 + pMax(pGetHeight(p->left), pGetHeight(p->right));
        if (pGetBalance(p) <= -2 || pGetBalance(p) >= 2)
        {
            Node<K,V>* x;
            Node<K,V>* y;
            Node<K,V>* z;
            x = p;

            // Store the taller child of x in y
            if (x->left->height > x->right->height)
            {
                y = x->left;
            }
            else
            {
                y = x->right;
            }

            // Store the taller child of y in z
            if (y->left->height > y->right->height)
            {
                z = y->left;
            }
            else if (y->left->height < y->right->height)
            {
                z = y->right;
            }
            else
            {
                // if same height then go for single rotation
                if (y == x->left)
                {
                    z = y->left;
                }
                else
                {
                    z = y->right;
                }
            }

            // now perform balancing
            if(y == x->left)
            {
                if(z == x->left->left)
                {
                    pRightRotate(x);
                }
                else if(z == x->left->right)
                {
                    pLeftRotate(y);
                    pRightRotate(x);
                }
            }
            else if(y == x->right)
            {
                if(z == x->right->right)
                {
                    pLeftRotate(x);
                }
                else if(z == x->right->left)
                {
                    pRightRotate(y);
                    pLeftRotate(x);
                }
            }
        }
        p = p->parent;
    }
}

// Additional helper functions

template <class K, class V>
void Map<K,V>::pDisplayTree(const string& prefix,
                            const Node<K,V>* node,
                            bool isLeft,
                            bool detailFlag)
{
    if(node != NULL)
    {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        if (detailFlag)
            cout << node->key << "{" << node->data << "," << node->height << "," << pGetBalance(node) << "}" << endl;
        else
            cout << "[" << node->key << "," << node->data << "]" << endl;
        pDisplayTree( prefix + (isLeft ? "│   " : "    "), node->left, true, detailFlag);
        pDisplayTree( prefix + (isLeft ? "│   " : "    "), node->right, false, detailFlag);
    }
}


template <class K, class V>
void Map<K,V>::pInOrderPrint(Node<K,V>* node)
{
    if (node == NULL)
    {
        return;
    }
    pInOrderPrint(node->left);
    cout << "[" << node->key << "," << node->data << "]  ";
    pInOrderPrint(node->right);
}


template <class K, class V>
void Map<K,V>::pPostOrderDelete(Node<K,V>* node)
{
    if (node == NULL)
    {
        return;
    }
    pPostOrderDelete(node->left);
    pPostOrderDelete(node->right);
    delete(node);
    nodeCount--;
}


#endif
