#ifndef TWO_HASH_TABLE_H
#define TWO_HASH_TABLE_H
#include "position.h"
#include "UPCEntry.h"
#include <cmath>
#include "list.h"
using namespace std;

class TwoHashTable {
public:
    List<UPCEntry> *array; //dynamic array of UPCEntry linked lists
    int size = 0; 
    int *lengths; //dynamic array of integers

    float getStdDev(); 
    float stddev(int *binLengths, int tableSize);
    Position search(UPCEntry &item); // if not found, return the default position with both indices set as -1
    TwoHashTable(string filename, int tableSize); //constructor
    bool insert(UPCEntry &item);     // returns true if successful, false otherwise.

};
#endif