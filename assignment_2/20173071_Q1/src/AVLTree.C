
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
    cout << "\nDeleting 55 ...\n" << endl;
    sAVLTree.deleteNode(55);
    sAVLTree.display();
    cout << "\nDeleting 40 ...\n" << endl;
    sAVLTree.deleteNode(40);
    sAVLTree.display();
    cout << "\nDeleting 20 ...\n" << endl;
    sAVLTree.deleteNode(20);
    sAVLTree.display();
    sAVLTree.print();
    sAVLTree.search(12);
    cout << "Occurances:60:" << sAVLTree.getCount(60) << endl;

    return 0;
}
