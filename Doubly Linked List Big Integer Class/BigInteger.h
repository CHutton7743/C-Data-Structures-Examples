#ifndef BIG_INTEGER
#define BIG_INTEGER

#include "Node.h"
#include "DoublyLinkedList.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

class BigInteger : public DoublyLinkedList<int>
{
  protected:
    bool negative;
  
  public:

    BigInteger();
    
    BigInteger(const string &);

    BigInteger(const BigInteger &);

    ~BigInteger();

    BigInteger operator=(const BigInteger &);

    BigInteger operator+(BigInteger &);

    BigInteger operator-(BigInteger &);

    bool operator==(BigInteger &);

    bool operator>(BigInteger &);

    bool operator<(BigInteger &);

    bool operator>=(BigInteger &);

    bool operator<=(BigInteger &);

    bool isNegative();
  
    string toString(BigInteger);

    void print();

    friend ostream& operator<<(ostream &, BigInteger &);

    friend istream& operator>>(istream &, BigInteger &);

    bool isDigits(const string &);
};

#endif