#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <iostream>
using namespace std;

template <class T>
class List{
    public:
        int size;
        // standard constructor
        List(void){
            first = NULL;
            last = NULL;
            size = 0;
        }  
        // standard destructor          
        ~List(void); 
        // copy constructor
        List(const List<T> &OtherList);
        List<T> &operator=(const List<T> &OtherList);

        bool IsEmpty();
        // appends after the given node
        void addAfter(T node);
        // aooends to the end
        void addLast(T node); 
        // inserts a node at the given index
        Node<T> *Insert(int index, T node);
        // deletes a node
        int DeleteN(T node);
        // prints the list
        void printList(void);
        // finds a node
        int locateN(T node);
        //overloads the += operator
        List<T> &operator+=(const List<T> &OtherList);

    private:
        Node<T> *first = NULL;
        Node<T> *last = NULL;
        
};

#endif