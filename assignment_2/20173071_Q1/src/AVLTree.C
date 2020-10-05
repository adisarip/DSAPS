
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
    cout << "OCCURANCES(60) = " << sAVLTree.getCount(60) << endl;
    sAVLTree.lowerBound(60);
    sAVLTree.upperBound(60);
    sAVLTree.kthLargestElement(2);
    sAVLTree.kthLargestElement(3);
    sAVLTree.kthLargestElement(4);
    sAVLTree.kthLargestElement(5);
    sAVLTree.closestElement(30);
    sAVLTree.closestElement(15);
    sAVLTree.closestElement(62);
    sAVLTree.closestElement(63);
    sAVLTree.closestElement(4);
    sAVLTree.closestElement(80);
    cout << "COUNT-ELEMENTS-IN-RANGE[15,60] = " << sAVLTree.getCountInRange(15, 60) << endl;

    return 0;
}
