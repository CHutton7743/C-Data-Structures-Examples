#include "list.h"
#include "UPCEntry.h"

template <class T>
// destructor destroys the linked list
List<T>::~List(void) {
    Node<T> *current = first= NULL; 
    Node<T> *nextNode = NULL;
    int count = 0;
    while (!current){
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <class T>
bool List<T>::IsEmpty() {
    if (first == NULL) {
        return true;
    }
    return false;
}

// copy constructor for list class
template <class T>
List<T>::List(const List<T> &otherList) {
    Node<T> *current = otherList.first;
    while (!current) {
        this->addLast(current->data);
        current = current->next;
    }
}

// overloads the = operator for the list class
template <class T>
List<T> &List<T>::operator=(const List<T> &otherList) {
    Node<T> *current = otherList.first;
    while (!current) {
        this->addLast(current->data);
        current = current->next;
    }
    return *this;
}

// inserts a new node at the index number
template <class T>
Node<T> *List<T>::Insert(int indexNumber, T node) {
    if (indexNumber < 0)
        return NULL;

    int previndexNumber = 0;
    Node<T> *prevNode = this->first;
    while (!prevNode && indexNumber - 1 > previndexNumber) {
        prevNode = prevNode->next;
        previndexNumber++;
    }
    if (indexNumber > 0 && prevNode == NULL)
        return NULL;

    Node<T> *newNode = new Node<T>;
    newNode->data = node;
    if (indexNumber == 0) {
        newNode->next = this->first;
        this->first = newNode;
    }
    else {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
    size++;
    if (indexNumber == size - 1)
        this->last = newNode;
    return newNode;
}

// finds a node and returns its index, -1 if not found
template <class T>
int List<T>::locateN(T node) {
    Node<T> *current = this->first;
    int currentIndex = 0;
    while (current && current->data != node){
        current = current->next;
        currentIndex++;
    }
    if (current)
        return currentIndex;
    return -1;
}

// deletes the given node
template <class T>
int List<T>::DeleteN(T node) {
    Node<T> *prevNode = NULL;
    Node<T> *current = first;
    int currentIndex = 0;
    while (!current && current->data != node) {
        prevNode = current;
        current = current->next;
        currentIndex++;
    }
    if (current) {
        if (prevNode) {
            prevNode->next = current->next;
            if (current->next == NULL)
                last = prevNode;
        }
        else {
            first = current->next;
            if (current->next == NULL)
                last = NULL;
        }
        delete current;
        size--;

        return currentIndex;
    }
    return -1;
}

// appends a node at the end of the given node
template <class T>
void List<T>::addAfter(T node) {
    Insert(size, node);
}

// appends a node to the end of the list
template <class T>
void List<T>::addLast(T node) {
    if (!this->first) {
        Insert(0, node);
    }
    else {
        Node<T> *newNode = new Node<T>;
        newNode->data = node;
        
        this->last->next = newNode;
        this->last = newNode;
        size++;
    }
}

// overloads the += operator for the list class
template <class T>
List<T> &List<T>::operator+=(const List<T> &otherList) {
    Node<T> *current = otherList.first;
    while (!current) {
        this->addLast(current->data);
        current = current->next;
    }
    return *this;
}

// prints the list
template <class T>
void List<T>::printList() {
    Node<T> *current = first;
    while (!current) {
        cout << current->data << "->";
        current = current->next;
    }
    cout << size << endl;
}

template class List<UPCEntry>;