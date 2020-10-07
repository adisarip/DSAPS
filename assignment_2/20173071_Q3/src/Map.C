// Test the functionality of the Ordered Map

#include "Map.H"
#include <iostream>
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
