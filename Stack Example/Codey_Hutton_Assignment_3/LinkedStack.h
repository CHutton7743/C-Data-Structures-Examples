#ifndef LINKED_STACK_
#define LINKED_STACK_

#include "StackInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
  private:
    Node<ItemType>* topPtr; //Pointer to first node in chain
                            //this node contains the stack's top
    int high = 0;
    int avg = 0;
    int numNodes = 0;
    int totalValue = 0;

  public:
  //Constructors and destructor
  ItemType max() const;
  ItemType mean() const;
  LinkedStack();
  LinkedStack(const LinkedStack<ItemType>& aStack);
  virtual ~LinkedStack();

  //Stack Operations:
  bool isEmpty() const;
  bool push(const ItemType& newItem);
  bool pop();
  ItemType peek() const;
}; //end LinkedStack

#include "LinkedStack.cpp"
#endif