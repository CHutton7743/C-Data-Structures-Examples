#include "twoHashTable.h"
#include "UPCEntry.h"
#include "list.h"
#include <fstream>   
#include <iostream>
using namespace std;

// creates a new array of lists and integers. Then, it reads the data from the file and updates the array
TwoHashTable::TwoHashTable(string filename, int size){ 
    this->size = size;
    array = new List<UPCEntry>[size];
   
    lengths = new int[size];

    string line; ifstream file; UPCEntry entry;
    file.open(filename); getline(file,line);
    
    while(getline(file, line)){
        entry = UPCEntry(line);
        insert(entry);
    }
    for(int i = 0; i<size; i++){
        lengths[i] = array[i].size;
    }
}

// checks h1 table and then checks h2 table. Returns the position of the item from the tables.
Position TwoHashTable::search(UPCEntry &item){ 
    int h1 = item.hash1(size);
    int h2 = item.hash2(size);
    Position place;

    if(array[h1].locateN(item) != -1){
        place.indexInTable = h1;
        place.indexInBin = array[h1].locateN(item);
        return place;
    }
    else if(array[h2].locateN(item) != -1){
        place.indexInTable = h2;
        place.indexInBin = array[h2].locateN(item);
    }
    return place;
}

// this function checks the hash value of both h1 and h2 and appends the smaller value. if both are == its appends it to h1.
bool TwoHashTable::insert(UPCEntry &item){ 
    int h1 = item.hash1(size);
    int h2 = item.hash2(size);

    if(array[h1].size <= array[h2].size){
        array[h1].Insert(0,item);
        return true;
    }
    if(array[h1].size > array[h2].size){
        array[h2].Insert(0,item);
        return true;
    }
    return false;
}

float TwoHashTable::stddev(int *binLengths, int tableSize) {
        float total = 0;
        for (int i = 0; i < tableSize; i++)
            total += binLengths[i];

        float average = total / tableSize;

        float deviationTotal = 0;
        for (int i = 0; i < tableSize; i++) {
            deviationTotal = deviationTotal + (binLengths[i] - average) * (binLengths[i] - average);
        }

        float variance = deviationTotal / tableSize;
        return sqrt(variance);
    }

//this functions returns the the deviation of the two tables.
float TwoHashTable::getStdDev(){ 
    return stddev(lengths, size);
}