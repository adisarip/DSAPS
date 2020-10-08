
// A template based implementation of "Ordered-Map" using AVL Tree as the internal Balanced BST

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


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DRIVER PROGRAM <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //

// Test the functionality of the Ordered Map

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
    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Testing Ordered Map using Integers <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    Map<int, int> iMap;
    iMap.insert(0, 40);
    iMap.insert(1, 20);
    iMap.insert(2, 60);
    iMap.insert(3, 10);
    iMap.insert(4, 5);
    iMap.insert(5, 15);
    iMap.insert(6, 55);
    iMap.insert(7, 65);
    iMap.insert(8, 75);
    iMap.insert(9, 32);
    iMap.insert(10, 12);
    iMap.display();
    iMap.print();
    iMap.insert(3, 100);
    iMap.insert(5, 200);
    iMap.display();
    iMap.erase(5);
    iMap.erase(7);
    iMap.display();
    cout << "SIZE() = " << iMap.size() << endl;
    iMap.insert(5, 15);
    iMap.insert(7, 65);
    iMap.display();
    iMap.print();
    cout << "FIND(4) = " << iMap.find(4) << endl;
    cout << "FIND(9) = " << iMap.find(9) << endl;
    cout << "FIND(20) = " << iMap.find(20) << endl;
    cout << "SIZE() = " << iMap.size() << endl;
    cout << "SIZE() = " << iMap.size() << endl;
    cout << "MAP[4] = " << iMap[4] << endl;
    cout << "MAP[9] = " << iMap[9] << endl;
    cout << "MAP[20] = " << iMap[20] << endl;
    iMap.print();
    cout << "Modifying values at '4' and '9'. Adding '20'" << endl;
    iMap[4] = 100;
    iMap[9] = 200;
    iMap[20] = 500;
    cout << "MAP[4] = " << iMap[4] << endl;
    cout << "MAP[9] = " << iMap[9] << endl;
    cout << "MAP[20] = " << iMap[20] << endl;
    iMap.display();
    iMap.print();


    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Testing Ordered Map using Strings <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
    Map<string, string> sMap;
    sMap.insert(string("a"), string("aaa"));
    sMap.insert(string("b"), string("bbb"));
    sMap.insert(string("c"), string("ccc"));
    sMap.insert(string("d"), string("ddd"));
    sMap.insert(string("e"), string("eee"));
    sMap.insert(string("f"), string("fff"));
    sMap.insert(string("g"), string("ggg"));
    sMap.insert(string("h"), string("hhh"));
    sMap.insert(string("i"), string("iii"));
    sMap.insert(string("j"), string("jjj"));
    sMap.insert(string("k"), string("kkk"));
    sMap.display();
    sMap.print();
    sMap.insert(string("c"), string("cccc"));
    sMap.insert(string("e"), string("eeee"));
    sMap.display();
    sMap.erase(string("e"));
    sMap.erase(string("g"));
    sMap.display();
    cout << "SIZE() = " << sMap.size() << endl;
    sMap.insert(string("e"), string("eeeee"));
    sMap.insert(string("g"), string("ggggg"));
    sMap.display();
    sMap.print();
    cout << "FIND(d) = " << sMap.find(string("d")) << endl;
    cout << "FIND(i) = " << sMap.find(string("i")) << endl;
    cout << "FIND(x) = " << sMap.find(string("x")) << endl;
    cout << "SIZE() = " << sMap.size() << endl;
    cout << "SIZE() = " << sMap.size() << endl;
    cout << "MAP[d] = " << sMap[string("d")] << endl;
    cout << "MAP[i] = " << sMap[string("i")] << endl;
    cout << "MAP[x] = " << sMap[string("x")] << endl;
    sMap.print();
    cout << "Modifying values at 'd' and 'i'. Adding 'x'" << endl;
    sMap[string("d")] = "dddd";
    sMap[string("i")] = "iiii";
    sMap[string("x")] = "xxxx";
    cout << "MAP[d] = " << sMap[string("d")] << endl;
    cout << "MAP[i] = " << sMap[string("i")] << endl;
    cout << "MAP[x] = " << sMap[string("x")] << endl;
    sMap.display();
    sMap.print();


    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Testing Ordered Map using Class Objects <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
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

    Map<Student, string> cMap;
    cMap.insert(aditya, "ADITYA");
    cMap.insert(laasya, "LAASYA");
    cMap.insert(anusha, "ANUSHA");
    cMap.insert(chandu, "CHANDU");
    cMap.insert(aruna, "ARUNA");
    cMap.insert(suraj, "SURAJ");
    cMap.insert(tubli, "TUBLI");
    cMap.insert(rama, "RAMA");
    cMap.insert(kambu, "KAMBU");
    cMap.insert(chacha, "CHACHA");
    cMap.insert(chachi, "CHACHI");
    cMap.insert(lahari, "LAHARI");
    cMap.display();
    cout << "\nUpdating entries for 'anusha' & 'aruna' ...\n" << endl;
    cMap.insert(anusha, "ANUSHA_ANUSHA");
    cMap.insert(aruna, "ARUNA_ARUNA");
    cMap.display();
    cout << "\nErasing entries of 'aruna' & 'tubli' ...\n" << endl;
    cMap.erase(aruna);
    cMap.erase(tubli);
    cMap.display();
    cout << "SIZE() = " << cMap.size() << endl;
    cout << "\nInserting entries for 'aruna' & 'tubli' ...\n" << endl;
    cMap.insert(aruna, "ARU_ARUNA");
    cMap.insert(tubli, "TUB_TUBLI");
    cMap.display();
    cout << "FIND(chandu) = " << cMap.find(chandu) << endl;
    cout << "FIND(aditya) = " << cMap.find(aditya) << endl;
    Student kumar(2000, "Kumar", "E.C.E", "kumar@gmail.com");
    cout << "FIND(kumar) = " << cMap.find(kumar) << endl;
    cout << "SIZE() = " << cMap.size() << endl;
    cout << endl;
    cout << "MAP[chandu] = " << cMap[chandu] << endl;
    cout << "MAP[aditya] = " << cMap[aditya] << endl;
    cout << "MAP[kumar] = " << cMap[kumar] << endl;
    cMap.display();
    cout << "\nModifying values at 'chandu' and 'aditya'. Adding 'kumar'\n" << endl;
    cMap[chandu] = "CHANDU_CHANDU";
    cMap[aditya] = "ADITYA_ADITYA";
    cMap[kumar] = "KUMAR_KUMAR";
    cout << "MAP[chandu] = " << cMap[chandu] << endl;
    cout << "MAP[aditya] = " << cMap[aditya] << endl;
    cout << "MAP[kumar] = " << cMap[kumar] << endl;
    cout << endl;
    cMap.display();
    cout << endl;
    cMap.print();
    cout << endl;
    return 0;
}
