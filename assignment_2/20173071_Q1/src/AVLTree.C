
// Test the functionality of the AVLTree Class

#include "AVLTree.H"
#include <iostream>
using namespace std;


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
    sAVLTree.insertNode(65);
    sAVLTree.insertNode(65);
    sAVLTree.insertNode(75);
    sAVLTree.insertNode(32);
    sAVLTree.insertNode(20);
    sAVLTree.insertNode(12);
    sAVLTree.insertNode(60);
    sAVLTree.insertNode(60);
    sAVLTree.insertNode(32);
    sAVLTree.insertNode(15);
    sAVLTree.display();
    sAVLTree.deleteNode(55);
    sAVLTree.display();
    sAVLTree.deleteNode(60);
    sAVLTree.display();
    sAVLTree.deleteNode(20);
    sAVLTree.display();
    sAVLTree.print();

    return 0;
}
