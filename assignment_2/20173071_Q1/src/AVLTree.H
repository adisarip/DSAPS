
// A template based generic Implementation of an AVL tree.

#ifndef __AVLTREE__
#define __AVLTREE__

#include <iostream>
using namespace std;

template <class T>
class Node
{
  public:
    inline Node()
    :count(0),balance(0),parent(NULL),left(NULL),right(NULL){};
    inline Node(T keyParm)
    :key(keyParm),count(1),balance(0),parent(NULL),left(NULL),right(NULL){};
    inline ~Node(){};

    T key;       // Node Data
    int count;   // for handling duplicate nodes
    int balance; // {-1,0,1}, default=0
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
class AVLTree
{
  public:
    AVLTree();
    AVLTree(const T& keyParm);
    ~AVLTree();
    void print();
    void insertNode(T newKeyParm);
    void deleteNode(T keyParm);
    void clear();
    Node<T>* getRootNode();

  protected:
    void pInOrderPrint(Node<T>* nodeParm);
    void pPostOrderDelete(Node<T>* nodeParm);
    void pUpdateBalanceFactors(){};
    Node<T>* pInsertNode(Node<T>* parentParm, Node<T>* nodeParm, T& newKeyParm);
    void pDeleteNode(Node<T>* nodeParm, T& newKeyParm);

  private:
    int      mNodeCount;
    Node<T>* root;
};

template <class T>
AVLTree<T>::AVLTree()
:mNodeCount(0)
,root(NULL)
{
}

template <class T>
AVLTree<T>::AVLTree(const T& keyParm)
:mNodeCount(0)
,root(NULL)
{
    root = new Node<T>(keyParm);
    mNodeCount++;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    this->clear();
}

template <class T>
void AVLTree<T>::print()
{
    // print in-order traversal of the tree
    pInOrderPrint(root);
    cout << endl;
}

template <class T>
void AVLTree<T>::clear()
{
    // delete all nodes using post-order traversal of the tree
    pPostOrderDelete(root);
}

template <class T>
void AVLTree<T>::deleteNode(T keyParm)
{
    Node<T>* pNode = root;

    while (keyParm != pNode->key)
    {
        if (keyParm < pNode->key)
        {
            pNode = pNode->left;
        }
        else
        {
            pNode = pNode->right;
        }
    }

    if (keyParm == pNode->key)
    {
        pNode->count -= 1;
        if (pNode->count == 0)
        {
            delete(pNode);
            pNode = NULL;
        }
    }
    else
    {
        cout << "Node with key:" << keyParm << " donot exist in the tree" << endl;
    }
}

template <class T>
void AVLTree<T>::insertNode(T newKeyParm)
{
    bool isDuplicateKey = false;
    Node<T>* x = this->root;
    Node<T>* y = NULL;

    // traverse the tree to get the insert location
    while (x != NULL)
    {
        y = x;
        if (newKeyParm == x->key)
        {
            isDuplicateKey = true;
            break;
        }
        else if (newKeyParm < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    if (isDuplicateKey)
    {
        y->count++;
    }
    else
    {
        Node<T>* node = new Node<T>(newKeyParm);
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
        //@todo: update balance factors here
    }
}


// protected member functions definitions

template <class T>
void AVLTree<T>::pInOrderPrint(Node<T>* nodeParm)
{
    if (nodeParm == NULL)
    {
        return;
    }
    pInOrderPrint(nodeParm->left);
    if (nodeParm->count > 1)
    {
        cout << nodeParm->key << "(" << nodeParm->count << ")" <<  " ";
    }
    else
    {
        cout << nodeParm->key <<  " ";
    }
    pInOrderPrint(nodeParm->right);
}

template <class T>
void AVLTree<T>::pPostOrderDelete(Node<T>* nodeParm)
{
    if (nodeParm == NULL)
    {
        return;
    }
    pPostOrderDelete(nodeParm->left);
    pPostOrderDelete(nodeParm->right);
    delete(nodeParm);
}

//@todo: Add Implementation
/*
template <class T>
void AVLTree<T>::pRebalance(Node<T>* nodeParm)
{

}
*/

//@todo: Add Implementation
/*
template <class T>
void AVLTree<T>::pUpdateBalanceFactors(Node<T>* nodeParm)
{
    if (nodeParm->balance < -1 || nodeParm->balance > 1)
    {
        pRebalance(nodeParm);
    }
}
*/

template <class T>
Node<T>* AVLTree<T>::getRootNode()
{
    return root;
}

#endif
