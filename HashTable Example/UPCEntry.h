#ifndef UPC_ENTRY_H
#define UPC_ENTRY_H
#include <string>
#include <iostream>
using namespace std;

struct UPCEntry {
    long upc = -1;
    string description = "";

    //constructor
    UPCEntry(); 
    // copy constructor
    UPCEntry(string entry); 

    // hash function 1 h1(upc) = upc % tablesize
    int hash1(int tableLength);
    // hash function 2 h2(desc) = abs(desc[0]+27*description[1]+729*desc[2]) % tablesize
    int hash2(int tableLength);
    // overload the = operator for upcentry object
    void operator=(const UPCEntry otherUPC);
    // overloads the == operator for the upc object
    bool operator==(const UPCEntry otherUPC);
    // overloads the != operator for the upc object
    bool operator!=(const UPCEntry otherUPC);
    // overloads the >= operator for the upc object
    bool operator>=(const UPCEntry otherUPC);
    // overload the > operator for upc object
    bool operator>(const UPCEntry otherUPC);
    // overloads the < operator for the upc object
    bool operator<(const UPCEntry otherUPC);
    // overloads the << operator for the upc object
    friend ostream& operator<<(ostream& os, const UPCEntry& item){
            os << "description: " << item.description;
        return os;
    }
};
#endif