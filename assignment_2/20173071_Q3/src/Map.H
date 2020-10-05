Map
// A template based implementation of "Ordered-Map" using AVL Tree as the internal Balanced BST

#ifndef __MAP__
#define __MAP__

#include <iostream>
#include <string>
using namespace std;


template <class T>
class Node
{
  public:
    inline Node(int key, T value)
    :key(key),data(value),height(0),parent(NULL),left(NULL),right(NULL){};
    inline ~Node(){};

    int key;  // key to index the data
    T data;   // Node Data
    int height;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
class Map
{
  public:
    Map();
    Map(int key, const T& value);
    ~Map();
    void insert(int key, T value);
    void erase(int key);
    bool find(int key);
    int size();   // return number of keys present in the Map
    void clear(); // remove all the elements from the Map
    void print();
    void display(bool detailFlag=false);

  protected:
    inline int pMax(int x, int y)
    {
        return (x>y) ? x : y;
    };
    inline int pGetHeight(const Node<T>* node)
    {
        return ((node) ? node->height : -1);
    };
    // Balance factor of any node is defined as: HEIGHT(left subtree) - HEIGHT(right subtree).
    inline int pGetBalance(const Node<T>* node)
    {
        return ((node) ? (pGetHeight(node->left) - pGetHeight(node->right)) : 0);
    };
    Node<T>* pGetMinNode(Node<T>* node);
    Node<T>* pGetMaxNode(Node<T>* node);
    void pLeftRotate(Node<T>* x);
    void pRightRotate(Node<T>* x);
    void pBalanceAVLInsert(Node<T>* node); // Balance AVL Tree after insert
    void pTransplant(Node<T>* x, Node<T>* y);
    void pBalanceAVLDelete(Node<T>* node); // Balance AVL Tree after delete
    void pDisplayTree(const string& prefix,
                      const Node<int>* node,
                      bool isLeft,
                      bool detailFlag=false);
    void pInOrderPrint(Node<T>* node);

  private:
    int nodeCount;
    Node<T>* root;
};

template <class T>
Map<T>::Map()
:root(NULL)
,nodeCount(0)
{
}

template <class T>
Map<T>::Map(int key, const T& value)
{
    root = new Node<T>(key, value);
    nodeCount++;
}

template <class T>
Map<T>::~Map()
{
}

template <class T>
void Map<T>::print()
{
    // print in-order traversal of the tree
    pInOrderPrint(root);
    cout << endl;
}

template <class T>
void Map<T>::display(bool detailFlag)
{
    pDisplayTree("", root, false, detailFlag);
}

// INSERT A NODE

template <class T>
void Map<T>::insert(int key, T value)
{
    bool isDuplicateKey = false;
    Node<T>* x = root; // x => used to traverse the tree
    Node<T>* y = NULL; // stores the position of new node's parent node

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
        Node<T>* node = new Node<T>(key, value);
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


template <class T>
void Map<T>::erase(int key)
{
    Node<T>* x = root; // to traverse the tree
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
            Node<T>* y = pGetMinNode(x->right); // get minimum node in right subtree
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

template <class T>
bool Map<T>::find(int key)
{
    bool isPresent = true;
    Node<T>* x = root; // to traverse the tree
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

template <class T>
int Map<T>::size()
{
    return nodeCount;
}

template <class T>
void Map<T>::clear()
{
    //@todo
    // implement post-order-delete of nodes
}


// PROTECTED Helper functions

template <class T>
Node<T>* Map<T>::pGetMinNode(Node<T>* node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <class T>
Node<T>* Map<T>::pGetMaxNode(Node<T>* node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

template <class T>
void Map<T>::pLeftRotate(Node<T>* x)
{
    Node<T>* y = x->right;
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


template <class T>
void Map<T>::pRightRotate(Node<T>* x)
{
    Node<T>* y = x->left;
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

template <class T>
void Map<T>::pBalanceAVLInsert(Node<T>* node)
{
    Node<T>* y = node->parent;
    Node<T>* z = node;

    while (y != NULL)
    {
        y->height = 1 + pMax(pGetHeight(y->left), pGetHeight(y->right));

        Node<T>* x = y->parent;
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
template <class T>
void Map<T>::pTransplant(Node<T>* x, Node<T>* y)
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

template <class T>
void Map<T>::pBalanceAVLDelete(Node<T>* node)
{
    Node<T>* p = node;

    while (p != NULL)
    {
        p->height = 1 + pMax(pGetHeight(p->left), pGetHeight(p->right));
        if (pGetBalance(p) <= -2 || pGetBalance(p) >= 2)
        {
            Node<T>* x;
            Node<T>* y;
            Node<T>* z;
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

template <class T>
void Map<T>::pDisplayTree(const string& prefix,
                              const Node<T>* node,
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


template <class T>
void Map<T>::pInOrderPrint(Node<T>* node)
{
    if (node == NULL)
    {
        return;
    }
    pInOrderPrint(node->left);
    cout << "[" << node->key << "," << node->data << "]  " << endl;
    pInOrderPrint(node->right);
}


#endif
