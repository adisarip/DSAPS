
// A template based generic Implementation of an AVL tree.

#ifndef __AVLTREE__
#define __AVLTREE__

#include <iostream>
#include <string>
using namespace std;

// Balance factor of any node is defined as height(left subtree) - height(right subtree).

template <class T>
class Node
{
  public:
    inline Node()
    :count(0),height(0),parent(NULL),left(NULL),right(NULL){};
    inline Node(T keyValue)
    :key(keyValue),count(1),height(0),parent(NULL),left(NULL),right(NULL){};
    inline ~Node(){};

    T key;       // Node Data
    int count;   // for handling duplicate nodes
    int height;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
class AVLTree
{
  public:
    AVLTree();
    AVLTree(const T& keyValue);
    ~AVLTree();
    void print();
    void display();
    void insertNode(T keyValue);
    void deleteNode(T keyValue);
    void search(T keyValue);
    void lowerBound(T keyValue);
    void upperBound(T keyValue);
    void kthLargestElement();
    void closestElement(T keyValue);
    int getCount(T keyValue);
    int getCountRange(T xKey, T yKey);



  protected:
    inline int pMax(int x, int y)
    {
        return (x>y)?x:y;
    };
    inline int pMin(int x, int y)
    {
        return (x<y)?x:y;
    };
    inline int pGetHeight(const Node<T>* node)
    {
        return ((node) ? node->height : -1);
    };
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
                      bool isLeft);
    void pInOrderPrint(Node<T>* node);

  private:
    Node<T>* root;
};

template <class T>
AVLTree<T>::AVLTree()
:root(NULL)
{
}

template <class T>
AVLTree<T>::AVLTree(const T& keyValue)
{
    root = new Node<T>(keyValue);
}

template <class T>
AVLTree<T>::~AVLTree()
{
}

template <class T>
void AVLTree<T>::print()
{
    // print in-order traversal of the tree
    pInOrderPrint(root);
    cout << endl;
}

template <class T>
void AVLTree<T>::display()
{
    pDisplayTree("", root, false);
}


// INSERT A NODE

template <class T>
void AVLTree<T>::insertNode(T keyValue)
{
    bool isDuplicateKey = false;
    Node<T>* x = root; // x => used to traverse the tree
    Node<T>* y = NULL; // stores the position of new node's parent node

    // traverse the tree to get the insert location
    while (x != NULL)
    {
        y = x;
        if (keyValue == x->key)
        {
            isDuplicateKey = true;
            break;
        }
        else if (keyValue < x->key)
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
        y->count++;
    }
    else
    {
        Node<T>* node = new Node<T>(keyValue);
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
    }
}


template <class T>
void AVLTree<T>::deleteNode(T keyValue)
{
    Node<T>* x = root; // to traverse the tree
    while (x != NULL)
    {
        if (keyValue < x->key)
        {
            x = x->left;
        }
        else if (keyValue > x->key)
        {
            x = x->right;
        }
        else
        {
            break; // keyValue == x->key
        }
    }

    if (x != NULL)
    {
        if (x->count > 1)
        {
            x->count--;
        }
        else if (x->left == NULL)
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
    }
    else
    {
        cout << "Node with key:" << keyValue << " not found." << endl;
    }
}


template <class T>
void AVLTree<T>::search(T keyValue)
{
    Node<T>* x = root; // to traverse the tree
    while (x != NULL)
    {
        if (keyValue < x->key)
        {
            x = x->left;
        }
        else if (keyValue > x->key)
        {
            x = x->right;
        }
        else
        {
            break; // keyValue == x->key
        }
    }

    if (x != NULL)
    {
        cout << "Node with key:" << keyValue << " FOUND !!!" << endl;
    }
    else
    {
        cout << "Node with key:" << keyValue << " NOT FOUND !!!" << endl;
    }
}


template <class T>
void AVLTree<T>::lowerBound(T keyValue)
{
    //@todo
}

template <class T>
void AVLTree<T>::upperBound(T keyValue)
{
    //@todo
}

template <class T>
void AVLTree<T>::kthLargestElement()
{
    //@todo
}

template <class T>
void AVLTree<T>::closestElement(T keyValue)
{
    //@todo
}

template <class T>
int AVLTree<T>::getCount(T keyValue)
{
    Node<T>* x = root; // to traverse the tree
    int sRetValue = 0;
    while (x != NULL)
    {
        if (keyValue < x->key)
        {
            x = x->left;
        }
        else if (keyValue > x->key)
        {
            x = x->right;
        }
        else
        {
            break; // keyValue == x->key
        }
    }

    if (x != NULL)
    {
        sRetValue = x->count;
    }
    else
    {
        cout << "Node with key:" << keyValue << " NOT FOUND !!!" << endl;
    }
    return sRetValue;
}


template <class T>
int AVLTree<T>::getCountRange(T xKey, T yKey)
{
    //@todo
    return 0;
}


// Protect members (helper functions)

template <class T>
Node<T>* AVLTree<T>::pGetMinNode(Node<T>* node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <class T>
Node<T>* AVLTree<T>::pGetMaxNode(Node<T>* node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

template <class T>
void AVLTree<T>::pLeftRotate(Node<T>* x)
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
void AVLTree<T>::pRightRotate(Node<T>* x)
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
void AVLTree<T>::pBalanceAVLInsert(Node<T>* node)
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
void AVLTree<T>::pTransplant(Node<T>* x, Node<T>* y)
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
void AVLTree<T>::pBalanceAVLDelete(Node<T>* node)
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
void AVLTree<T>::pDisplayTree(const string& prefix,
                              const Node<int>* node,
                              bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        // print the value of the node
        cout << node->key << "{" << pGetBalance(node) << "," << node->height << "," << node->count << "}" << endl;
        // enter the next tree level - left and right branch
        pDisplayTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        pDisplayTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}


template <class T>
void AVLTree<T>::pInOrderPrint(Node<T>* node)
{
    if (node == NULL)
    {
        return;
    }
    pInOrderPrint(node->left);
    for (int i=0; i<node->count; i++)
    {
        cout << node->key << " ";
    }
    pInOrderPrint(node->right);
}

#endif
