#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

// this is the standard node class from the text book

template <class T>
class Node {
public:
    T data;
    Node *next = NULL;
};
#endif