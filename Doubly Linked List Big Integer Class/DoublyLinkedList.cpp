#ifndef DOUBLY_LINKED_LIST_CPP
#define DOUBLY_LINKED_LIST_CPP
#include "DoublyLinkedList.h"

using namespace std;

/* NoSuchElementException
This is meant to handle an error in case the iterator tries to go to
the next element of the node its pointing at, and throws the error if
the iterator isn't pointing to a node.  This allows the program to continue
working even if next() or prev() is called on a node that doesn't exist.
*/
class NoSuchElementException
{
  public:

    string what() const throw()
    {
      return "Element does not exist";
    }
};

//Default constructor: sets all the pointers to null and length to 0
template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList()
  : first(nullptr), last(nullptr), iterator(nullptr), length(0)
{
};

//String constructor: takes a string, uses a for loop to iterate through
//the string, and appends each character into the DLL.  insertLast()
//handles appropriately handling the length variable and pointers.
template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const string & input)
: first(nullptr), last(nullptr), iterator(nullptr), length(0)
{
  for(int i = 0; i < input.length(); i++)
  {
    int digit = input.at(i) - '0';
    insertLast(digit);
  }
};

//Destructor: starts at one end of the list, uses iterator to move
//forward one node, and deletes the node behind it until the entire
//DLL is deleted.
template<class ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList()
{
  while(iterator != NULL)
  {
    iterator = last->next;
    delete last;
    last = iterator;
  }
}

//Copy constructor: creates a copy of the DLL passed in.
template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList<ItemType> & input)
{
  Node<ItemType>* runner = input.first;
  for(int i = 0; i < input.length; i++)
  {
    insertLast(runner->data);
    runner = runner->next;
    length++;
  }  
};

//Assignment Operator: sets a DLL equal to the input DLL
template<class ItemType>
DoublyLinkedList<ItemType>& DoublyLinkedList<ItemType>::operator=(const DoublyLinkedList<ItemType> & input)
{
  Node<ItemType>* runner = input.first;
  for(int i = 0; i < input.length; i++)
  {
    insertLast(runner->data);
    runner = runner->next;
  } 
  return *this;
};

//Initializer: initializes a blank list by calling the default constructor
//not 100% sure what this is supposed to do, and isn't used in the testing
//since this is technically starter code, I feel like it could be deleted,
//but it did come with the code so I've left it in.
template<class ItemType>
void DoublyLinkedList<ItemType>::init()
{
  DoublyLinkedList();
};

//isEmpty: returns true if the length equals 0, false if it doesn't
template<class ItemType>
bool DoublyLinkedList<ItemType>::isEmpty()
{
  return length == 0;
};

//getLength: returns the length variable
template<class ItemType>
int DoublyLinkedList<ItemType>::getLength()
{
  return length;
};

//insertFirst: inserts a node to the front of the DLL.  Sets the prev
//pointer to NULL, next pointer to the previous front node, which iterator
//is pointing to.  If this is inserting the first node of the DLL, both
//pointers are set to NULL, and both last and first are set to this node.
//finally, increments the length variable.
template<class ItemType>
void DoublyLinkedList<ItemType>::insertFirst(const ItemType & input)
{
  iterator = first;
  first = new Node<ItemType>();
  first->data = input;
  if(length > 0)
  {
    first->prev = NULL;
    first->next = iterator;
    iterator->prev = first;
  }
  else
  {
    first->prev = NULL;
    first->next = NULL;
    last = first;
  }
  length++;
  iterator = first;
};

//insertLast: inserts a node to the back of the DLL.  Sets the next
//pointer to NULL, prev pointer to the previous last node, which iterator
//is pointing to.  If this is inserting the first node of the DLL, both
//pointers are set to NULL, and both last and first are set to this node.
//finally, increments the length variable.
template<class ItemType>
void DoublyLinkedList<ItemType>::insertLast(const ItemType & input)
{
  iterator = last;
  last = new Node<ItemType>();
  last->data = input;

  if(length > 0)
  {
    last->prev = iterator;
    last->next = NULL;
    iterator->next = last;
  }
  else
  {
    last->prev = NULL;
    last->next = NULL;
    first = last;
  }
  length++;
  iterator = last;
};

//deleteFirst: deletes the first node in the DLL.  Moves the iterator forward
//one node, deletes first, then sets first equal to iterator.  Finally,
//decrements the length variable.
template<class ItemType>
void DoublyLinkedList<ItemType>::deleteFirst()
{
  iterator = first->next;
  delete first;
  first = iterator;
  first->prev = NULL;
  length--;
};

//deleteLast: deletes the last node in the DLL.  Moves the iterator backward
//one node, deletes last, then sets last equal to iterator.  Finally,
//decrements the length variable.
template<class ItemType>
void DoublyLinkedList<ItemType>::deleteLast()
{
  iterator = last->prev;
  delete last;
  last = iterator;
  last->next = NULL;
  length--;
};

//clear: deletes all nodes in the DLL, sets all pointers to nullptr,
//and sets the length to 0
template<class ItemType>
void DoublyLinkedList<ItemType>::clear()
{
  if(length != 0)
  {
    last = nullptr;
    iterator = first;
    while(iterator != NULL)
    {
      iterator = first->next;
      delete first;
      first = iterator;
      length--;
    }
    iterator = nullptr;
    first = nullptr;
  }
};

//setIteratorFirst: sets the iterator to point at the first node
//of the DLL
template<class ItemType>
void DoublyLinkedList<ItemType>::setIteratorFirst()
{
  iterator = first;
};

//setIteratorLast: sets the iterator to point at the last node
//of the DLL
template<class ItemType>
void DoublyLinkedList<ItemType>::setIteratorLast()
{
  iterator = last;
};

//hasPrev: returns true if the iterator's previous value isn't equal to
//NULL, and false if it is.
template<class ItemType>
bool DoublyLinkedList<ItemType>::hasPrev()
{
  return iterator->prev != NULL;
};

//hasNext: returns true if the iterator's previous value isn't equal to
//NULL, and false if it is.
template<class ItemType>
bool DoublyLinkedList<ItemType>::hasNext()
{
  return iterator->next != NULL;
};

//next: if the iterator is null, our NoSuchElementException is thrown and
//the function returns without doing anything.  Otherwise, moves the iterator
//equal to the next node the iterator is currently pointing to.
template<class ItemType>
void DoublyLinkedList<ItemType>::next()
{
  try
  {
    if(isIteratorNULL())
    {
      throw NoSuchElementException();
    }
  }
  catch(const NoSuchElementException& e)
  {
    cout << e.what() << '\n';
    return;
  }
  
    iterator = iterator->next;
};

//prev: if the iterator is null, our NoSuchElementException is thrown and
//the function returns without doing anything.  Otherwise, moves the iterator
//equal to the previous node the iterator is currently pointing to.
template<class ItemType>
void DoublyLinkedList<ItemType>::prev()
{
  try
  {
    if(isIteratorNULL())
    {
      throw NoSuchElementException();
    }
  }
  catch(const NoSuchElementException& e)
  {
    cerr << e.what() << '\n';
  }

  iterator = iterator->prev;
};

//isIteratorNull: if iterator equals nullptr, returns true.  Otherwise, returns false
template<class ItemType>
bool DoublyLinkedList<ItemType>::isIteratorNULL()
{
  return iterator == nullptr;
};

//getData: returns the data variable of the node the iterator is pointing to
template<class ItemType>
ItemType DoublyLinkedList<ItemType>::getData()
{
  return iterator->data;
};

//output operator overload: iterates through each node of the DLL and
//appends the node's data to the output stream.  Then, returns the output
//stream.
template<class U>
ostream& operator<<(ostream& os, const DoublyLinkedList<U> &input)
{
  input.setIteratorFirst();
  while(!input.isIteratorNULL())
  {
    os << input.getData();
    input.next();
  }

  return os;
}

//input operator overload: an ifstream object is created, and the open()
//function is called to select a file to read from.  Then, each line of
//the file is converted into a string, which is then passed into a DLL
//string constructor.  
template<class U>
istream& operator>>(istream& is, DoublyLinkedList<U> &input)
{
  ifstream myFile;
  myFile.open("test.txt");
  string myLine;
  if(myFile.is_open())
  {
    // getline(myFile, myLine);
    // is >> myLine;
    // input = DoublyLinkedList<U>(myLine);
  }
  else
  {
    cout << "Couldn't open file" << endl;
  }
  return is;
}

#endif