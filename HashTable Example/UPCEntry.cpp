#include "UPCEntry.h"
#include <iostream>
using namespace std;

UPCEntry::UPCEntry(){}

UPCEntry::UPCEntry(string entry){ 
    string partition = ",";
    this->upc = stoll(entry.substr(0, entry.find(partition)));
    entry.erase(0, entry.find(partition));
    entry.erase(0, 1);
    this->description = entry;
}

int UPCEntry::hash1(int tableLength) {
    return upc % tableLength;
}
// hash function 2 h2(desc) = abs(desc[0]+27*description[1]+729*desc[2]) % tablesize
int UPCEntry::hash2(int tableLength) {
    return abs(description[0] + 27 * description[1] + 729 * description[2]) % tableLength;
}

// overload the > operator for upc object
bool UPCEntry::operator>(const UPCEntry otherUPC){
    return this->upc > otherUPC.upc;
}
// overload the = operator for upcentry object
void UPCEntry::operator=(const UPCEntry otherUPC){
    this->description = otherUPC.description;
    this->upc = otherUPC.upc;
}
// overloads the == operator for the upc object
bool UPCEntry::operator==(const UPCEntry otherUPC){
    return this->upc == otherUPC.upc;
}
// overloads the < operator for the upc object
bool UPCEntry::operator<(const UPCEntry otherUPC){
    return this->upc < otherUPC.upc;
}
// overloads the >= operator for the upc object
bool UPCEntry::operator>=(const UPCEntry otherUPC){
    return ((this->upc = otherUPC.upc)||(this->upc > otherUPC.upc));
}
// overloads the != operator for the upc object
bool UPCEntry::operator!=(const UPCEntry otherUPC){
    return this->upc != otherUPC.upc;
}