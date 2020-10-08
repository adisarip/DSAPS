
// A template based generic Implementation of an AVL tree.

#include <iostream>
#include <string>
using namespace std;

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
    void display(bool detailFlag=false);
    void insertNode(T keyValue);
    void deleteNode(T keyValue);
    void search(T keyValue);
    void lowerBound(T keyValue);
    void upperBound(T keyValue);
    void kthLargestElement(int k);
    void closestElement(T keyValue);
    int getCount(T keyValue);
    int getCountInRange(T xKey, T yKey);

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
    int pGetCountInRange(Node<T>* node, const T& xKey, const T& yKey, int& count);
    void pDisplayTree(const string& prefix,
                      const Node<T>* node,
                      bool isLeft,
                      bool detailFlag=false);
    void pInOrderPrint(Node<T>* node);
    void pReverseInOrderCount(Node<T>* node, int k, int& count, bool& found);

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
void AVLTree<T>::display(bool detailFlag)
{
    pDisplayTree("", root, false, detailFlag);
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
        cout << "SEARCH(" << keyValue << "): = FOUND" << endl;
    }
    else
    {
        cout << "SEARCH(" << keyValue << "): = NOT FOUND" << endl;
    }
}

//lower bound refers to the element which has value "not less than" the key.
// Eg: lowerBound(6) in 5 6 7 7 6 5 5 6 => 5 5 5 6 6 6 7 7 is
// element with index 3 in the sorted list => 6
// Hence to compute that we take the following approach
// 1. Traverse down the tree looking for the key
// 2. If any node is greater than the keyValue then save the node value and go left.
// 3. Traverse until we reach NULL or the key element.
// 4. If key element exist then return its value.
// 5. If the key element donot exits then return the last saved node key value.

template <class T>
void AVLTree<T>::lowerBound(T keyValue)
{
    Node<T>* x = root; // to traverse the tree
    T sMinValue = pGetMinNode(x)->key;
    T sMaxValue = pGetMaxNode(x)->key;
    if (keyValue >= sMinValue && keyValue <= sMaxValue)
    {
        T sRetValue;
        while (x != NULL)
        {
            if (keyValue < x->key)
            {
                sRetValue = x->key;
                x = x->left;
            }
            else if (keyValue > x->key)
            {
                x = x->right;
            }
            else
            {
                sRetValue = x->key;
                break;
            }
        }
        cout << "LOWER-BOUND(" << keyValue << ") = " << sRetValue << endl;
    }
    else
    {
        cout << "Entered key is OUT-OF-RANGE for the tree. lower_bound donot exist." << endl;
    }
}

template <class T>
void AVLTree<T>::upperBound(T keyValue)
{
    Node<T>* x = root; // to traverse the tree
    T sMinValue = pGetMinNode(x)->key;
    T sMaxValue = pGetMaxNode(x)->key;
    if (keyValue >= sMinValue && keyValue <= sMaxValue)
    {
        T sRetValue = sMaxValue;
        while (x != NULL)
        {
            if (keyValue < x->key)
            {
                sRetValue = x->key;
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        cout << "UPPER-BOUND(" << keyValue << ") = " << sRetValue << endl;
    }
    else
    {
        cout << "Entered key is OUT-OF-RANGE for the tree. upper_bound donot exist." << endl;
    }
}

// perform a reverse in-order traversal and stop when the k elements are counted.
template <class T>
void AVLTree<T>::kthLargestElement(int k)
{
    int count = 0;
    bool found = false;
    pReverseInOrderCount(root, k, count, found);
}


// largest element less than or equal to given key
template <class T>
void AVLTree<T>::closestElement(T keyValue)
{
    Node<T>* x = root; // to traverse the tree
    T sMinValue = pGetMinNode(x)->key;
    T sMaxValue = pGetMaxNode(x)->key;
    T sLeftValue;
    T sRightValue;
    T sRetValue;
    if (keyValue < sMinValue)
    {
        sRetValue = sMinValue;
    }
    else if (keyValue > sMaxValue)
    {
        sRetValue = sMaxValue;
    }
    else
    {
        while (x != NULL)
        {
            if (keyValue < x->key)
            {
                sRightValue = x->key;
                x = x->left;
            }
            else if (keyValue > x->key)
            {
                sLeftValue = x->key;
                x = x->right;
            }
            else
            {
                sRightValue = x->key;
                break;
            }
        }
        if ((keyValue + keyValue) > (sRightValue + sLeftValue))
        {
            sRetValue = sRightValue;
        }
        else
        {
            sRetValue = sLeftValue;
        }
    }
    cout << "CLOSEST-ELEMENT(" << keyValue << ") = " << sRetValue << endl;
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
int AVLTree<T>::getCountInRange(T xKey, T yKey)
{
    Node<T>* node = root;
    int count = 0;
    pGetCountInRange(node, xKey, yKey, count);
    return count;
}

template <class T>
int AVLTree<T>::pGetCountInRange(Node<T>* node,
                                 const T& xKey,
                                 const T& yKey,
                                 int& count)
{
    if (node == NULL)
    {
        return 0;
    }

    if (node->key == xKey && node->key == yKey)
    {
        return node->count;
    }

    if (node->key >= xKey && node->key <= yKey)
    {
        count = node->count + pGetCountInRange(node->left, xKey, yKey, count)
                            + pGetCountInRange(node->right, xKey, yKey, count);
    }
    else if (node->key < xKey)
    {
        count = pGetCountInRange(node->right, xKey, yKey, count);
    }
    else
    {
        count = pGetCountInRange(node->left, xKey, yKey, count);
    }
    return count;
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
                              const Node<T>* node,
                              bool isLeft,
                              bool detailFlag)
{
    if(node != NULL)
    {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        if (detailFlag)
            cout << node->key << "{" << pGetBalance(node) << "," << node->height << "," << node->count << "}" << endl;
        else
            cout << node->key << "[" << node->count << "]" << endl;
        pDisplayTree( prefix + (isLeft ? "│   " : "    "), node->left, true, detailFlag);
        pDisplayTree( prefix + (isLeft ? "│   " : "    "), node->right, false, detailFlag);
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

template <class T>
void AVLTree<T>::pReverseInOrderCount(Node<T>* node, int k, int& count, bool& found)
{
    if (node == NULL || count >= k)
    {
        return;
    }
    pReverseInOrderCount(node->right, k, count, found);
    count += node->count;
    if (count >= k && found==false)
    {
        cout << "Kth-LARGEST-ELEMENT(" << k << ") = " << node->key << endl;
        found = true;
        return;
    }
    pReverseInOrderCount(node->left, k, count, found);
}



// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DRIVER PROGRAM <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //

// Test the functionality of the AVLTree Class

struct Student
{
    int mRollNumber;
    string mName;
    string mBranch;
    string mEmailId;

    // Object should have a default constructor
    Student():mRollNumber(0),mName(""),mBranch(""),mEmailId(""){};
    Student(int roll, string name, string branch, string email)
    :mRollNumber(roll),mName(name),mBranch(branch),mEmailId(email){};
    ~Student(){};

    // Overloaded comparision  operators needed for the AVLTree
    inline bool operator ==(const Student& x) const { return (this->mRollNumber == x.mRollNumber); }
    inline bool operator !=(const Student& x) const { return (this->mRollNumber != x.mRollNumber); }
    inline bool operator < (const Student& x) const { return (this->mRollNumber < x.mRollNumber); }
    inline bool operator > (const Student& x) const { return (this->mRollNumber > x.mRollNumber); }
    inline bool operator <=(const Student& x) const { return (this->mRollNumber <= x.mRollNumber); }
    inline bool operator >=(const Student& x) const { return (this->mRollNumber >= x.mRollNumber); }

    // overloaded arithemetic operators needed for the AVLTree
    inline int operator +(const Student &x) const { return (this->mRollNumber + x.mRollNumber); }
    inline int operator -(const Student &x) const { return (this->mRollNumber - x.mRollNumber); }
};

// for printing using cout
ostream& operator <<(ostream& os, const Student &x)
{
    os << x.mRollNumber << ":" << x.mName << ":" << x.mBranch << ":" << x.mEmailId;
    return os;
}

int main (int argc, char* argv[])
{
    cout << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Testing AVL Tree for Integers <<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    AVLTree<int> iAVLTree;
    iAVLTree.insertNode(40);
    iAVLTree.insertNode(20);
    iAVLTree.insertNode(60);
    iAVLTree.insertNode(10);
    iAVLTree.insertNode(5);
    iAVLTree.insertNode(15);
    iAVLTree.insertNode(55);
    iAVLTree.insertNode(65);
    iAVLTree.insertNode(65);
    iAVLTree.insertNode(75);
    iAVLTree.insertNode(32);
    iAVLTree.insertNode(20);
    iAVLTree.insertNode(12);
    iAVLTree.insertNode(60);
    iAVLTree.insertNode(60);
    iAVLTree.insertNode(32);
    iAVLTree.insertNode(15);
    iAVLTree.display();
    cout << "\nDeleting 55 ...\n" << endl;
    iAVLTree.deleteNode(55);
    iAVLTree.display();
    cout << "\nDeleting 40 ...\n" << endl;
    iAVLTree.deleteNode(40);
    iAVLTree.display();
    cout << "\nDeleting 20 ...\n" << endl;
    iAVLTree.deleteNode(20);
    iAVLTree.display();
    iAVLTree.print();
    iAVLTree.search(12);
    cout << "OCCURANCES(60) = " << iAVLTree.getCount(60) << endl;
    iAVLTree.lowerBound(60);
    iAVLTree.upperBound(60);
    iAVLTree.kthLargestElement(2);
    iAVLTree.kthLargestElement(3);
    iAVLTree.kthLargestElement(4);
    iAVLTree.kthLargestElement(5);
    iAVLTree.closestElement(30);
    iAVLTree.closestElement(15);
    iAVLTree.closestElement(62);
    iAVLTree.closestElement(63);
    iAVLTree.closestElement(4);
    iAVLTree.closestElement(80);
    cout << "COUNT-ELEMENTS-IN-RANGE[15,60] = " << iAVLTree.getCountInRange(15, 60) << endl;


    cout << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Testing AVL Tree for Strings <<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    string a = "a";
    string b = "b";
    string c = "c";
    string d = "d";
    string e = "e";
    string f = "f";
    string g = "g";
    string h = "h";
    string i = "i";
    string p = "p";
    AVLTree<string> sAVLTree;
    sAVLTree.insertNode(p);
    sAVLTree.insertNode(b);
    sAVLTree.insertNode(c);
    sAVLTree.insertNode(d);
    sAVLTree.insertNode(e);
    sAVLTree.insertNode(f);
    sAVLTree.insertNode(g);
    sAVLTree.insertNode(h);
    sAVLTree.insertNode(i);
    sAVLTree.display(true);
    cout << "\nDeleting e ...\n" << endl;
    sAVLTree.deleteNode(e);
    sAVLTree.display(true);
    cout << "\nDeleting f ...\n" << endl;
    sAVLTree.deleteNode(f);
    sAVLTree.display(true);
    cout << "\nAdding some additional nodes ...\n" << endl;
    sAVLTree.insertNode(f);
    sAVLTree.insertNode(e);
    sAVLTree.insertNode(b);
    sAVLTree.insertNode(c);
    sAVLTree.insertNode(p);
    sAVLTree.insertNode(p);
    sAVLTree.insertNode(d);
    sAVLTree.insertNode(e);
    sAVLTree.display(true);
    sAVLTree.search(a);
    sAVLTree.search(f);
    sAVLTree.search(string("z"));
    cout << "OCCURANCES(a): = " << sAVLTree.getCount(a) << endl;
    cout << "OCCURANCES(f): = " << sAVLTree.getCount(f) << endl;
    sAVLTree.lowerBound(b);
    sAVLTree.upperBound(e);
    sAVLTree.lowerBound(string("i"));
    sAVLTree.upperBound(string("f"));
    sAVLTree.kthLargestElement(2);
    sAVLTree.kthLargestElement(3);
    sAVLTree.kthLargestElement(4);
    sAVLTree.kthLargestElement(5);
    sAVLTree.closestElement(string("a"));
    sAVLTree.closestElement(string("z"));
    sAVLTree.closestElement(string("k"));
    sAVLTree.closestElement(string("o"));
    cout << "COUNT-ELEMENTS-IN-RANGE[b,g] = " << sAVLTree.getCountInRange(b, g) << endl;


    cout << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Testing AVL Tree for Class Objects <<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    Student aditya(1000, "Aditya", "C.S.E", "aditya@gmail.com");
    Student laasya(1010, "Laasya", "M.Pharm", "laasya@gmail.com");
    Student anusha(1020, "Anusha", "M.Pharm", "anusha@gmail.com");
    Student chandu(1030, "Chandrashekhar", "M.S.C", "chandu@gmail.com");
    Student aruna(1040, "Aruna", "M.C.A", "aruna@gmail.com");
    Student suraj(1050, "Suraj", "C.S.E", "suraj@gmail.com");
    Student tubli(1060, "Sharanya", "F.tech", "tubli@gmail.com");
    Student rama(1070, "Rama", "B.Ed", "rama@gmail.com");
    Student kambu(1080, "Kamalakar", "B.Com", "kambu@gmail.com");
    Student chacha(1090, "Kameshwar", "B.Com", "chacha@gmail.com");
    Student chachi(1100, "Vijaya", "B.Ed", "chachi@gmail.com");
    Student lahari(1200, "Lahari", "E.C.E", "lahari@gmail.com");
    AVLTree<Student> cAVLTree;
    cAVLTree.insertNode(aditya);
    cAVLTree.insertNode(laasya);
    cAVLTree.insertNode(anusha);
    cAVLTree.insertNode(chandu);
    cAVLTree.insertNode(aruna);
    cAVLTree.insertNode(suraj);
    cAVLTree.insertNode(tubli);
    cAVLTree.insertNode(rama);
    cAVLTree.insertNode(kambu);
    cAVLTree.insertNode(chacha);
    cAVLTree.insertNode(chachi);
    cAVLTree.insertNode(lahari);
    cAVLTree.insertNode(aruna);
    cAVLTree.insertNode(aditya);
    cAVLTree.insertNode(laasya);
    cAVLTree.insertNode(lahari);
    cAVLTree.insertNode(aditya);
    cAVLTree.insertNode(chandu);
    cAVLTree.insertNode(laasya);
    cAVLTree.insertNode(tubli);
    sAVLTree.display();
    cout << "\nDeleting Aditya ...\n" << endl;
    cAVLTree.deleteNode(aditya);
    cAVLTree.display();
    cout << "\nDeleting Rama ...\n" << endl;
    cAVLTree.deleteNode(rama);
    cAVLTree.display();
    cout << "\nDeleting Anusha ...\n" << endl;
    cAVLTree.deleteNode(suraj);
    cAVLTree.display();
    cAVLTree.search(laasya);
    cAVLTree.search(Student(2000, "Kumar", "E.C.E", "kumar@gmail.com"));
    cout << "OCCURANCES(Laasya) = " << cAVLTree.getCount(laasya) << endl;
    cAVLTree.lowerBound(aditya);
    cAVLTree.upperBound(aditya);
    cAVLTree.lowerBound(aruna);
    cAVLTree.upperBound(aruna);
    cAVLTree.kthLargestElement(2);
    cAVLTree.kthLargestElement(3);
    cAVLTree.kthLargestElement(4);
    cAVLTree.kthLargestElement(5);
    cAVLTree.closestElement(aditya);
    cAVLTree.closestElement(aruna);
    cAVLTree.closestElement(Student(2000, "Kumar", "E.C.E", "kumar@gmail.com"));
    cAVLTree.closestElement(Student(1000, "Veeramani", "E.C.E", "veeru@gmail.com"));
    cAVLTree.closestElement(Student(1028, "Prabhat", "E.C.E", "prabhat@gmail.com"));
    cAVLTree.closestElement(Student(1022, "Vinod", "E.C.E", "vinod@gmail.com"));
    cout << "COUNT-ELEMENTS-IN-RANGE[Chandrashekhar,Vijaya] = " << cAVLTree.getCountInRange(chandu, chachi) << endl;
    return 0;
}
