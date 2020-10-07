
// Test the functionality of the AVLTree Class

#include "AVLTree.H"
#include <iostream>
#include <string>
using namespace std;

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
