
// Test the functionality of the AVLTree Class

#include "AVLTree.H"
#include <iostream>
using namespace std;

void printTree(const std::string& prefix, const Node<int>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );
        // print the value of the node
        std::cout << node->key << "[" << node->balance << "]" << std::endl;
        // enter the next tree level - left and right branch
        printTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printTree(const Node<int>* node)
{
    printTree("", node, false);
}


int main (int argc, char* argv[])
{
    cout << "Creating a AVL Tree" << endl;
    AVLTree<int> sAVLTree;
    sAVLTree.insertNode(40);
    sAVLTree.insertNode(20);
    sAVLTree.insertNode(60);
    sAVLTree.insertNode(10);
    sAVLTree.insertNode(5);
    sAVLTree.insertNode(15);
    sAVLTree.insertNode(55);
    sAVLTree.insertNode(5);
    sAVLTree.insertNode(65);
    sAVLTree.insertNode(60);
    sAVLTree.insertNode(75);
    sAVLTree.insertNode(32);
    sAVLTree.insertNode(32);
    sAVLTree.insertNode(12);
    sAVLTree.insertNode(55);
    sAVLTree.insertNode(60);
    printTree(sAVLTree.getRootNode());
    sAVLTree.deleteNode(60);
    sAVLTree.deleteNode(32);
    printTree(sAVLTree.getRootNode());

    return 0;
}
