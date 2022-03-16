#ifndef Linked_Stack_
#define Linked_Stack_

#include <cassert>
#include "LinkedStack.h"

using namespace std;

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{  
}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
  //Point to nodes in original chain
  Node<ItemType>* origChainPtr = aStack.topPtr;

  if(origChainPtr == nullptr)
  {
    topPtr = nullptr;
  }
  else
  {
    //Copy first node
    topPtr = new Node<ItemType>();
    topPtr->setItem(origChainPtr->getItem());

    //Point to first node in new chain
    Node<ItemType>* newChainPtr = topPtr;

    //Advance original-chain pointer
    origChainPtr = origChainPtr->getNext();

    //Copy remaining nodes
    while(origChainPtr != nullptr)
    {
      //Get next item from original chain
      ItemType nextItem = origChainPtr->getItem();

      //Create a new node containing the next item
      Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

      //Link new node to end of new chain
      newChainPtr->setNext(newNodePtr);

      //Advance pointer to new last node
      newChainPtr = newChainPtr->getNext();

      //Advance original-chain pointer
      origChainPtr = origChainPtr->getNext();
    } //end while

    newChainPtr->setNext(nullptr);
  } //end if
} //end copy constructor

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
  while(!isEmpty())
  {
    pop();
  }
} //end destructor

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
  if(newItem > high)
  {
    high = newItem;
  }

  numNodes++;
  totalValue += newItem;

  avg = totalValue / numNodes;

  Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
  topPtr = newNodePtr;
  newNodePtr = nullptr;

  return true;
} //end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
  bool result = false;
  if(!isEmpty())
  {
    Node<ItemType>* runner = topPtr->getNext();

    //figure out data of node being popped
    int currValue = topPtr->getItem();

    //update member variables
    if(currValue == high)
    {
      high = 0;
      while(runner != NULL)
      {
        if(runner->getItem() > high)
        {
          high = runner->getItem();
        }
        runner = runner->getNext();
      }
    }

    runner = topPtr->getNext();
    delete topPtr;
    topPtr = runner;
    runner = nullptr;

    numNodes--;
    totalValue -= currValue;
    avg = totalValue / numNodes;

    //Stack is not empty; delete top
    // Node<ItemType>* nodeToDeletePtr = topPtr;
    // topPtr = topPtr->getNext();

    //Return deleted node to system
    // nodeToDeletePtr->setNext(nullptr);
    // delete nodeToDeletePtr;
    // nodeToDeletePtr = nullptr;

    result = true;
  } //end if
  return result;
} //end pop

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
  assert(!isEmpty()); //Enforce precondition during debugging

  //Stack is not empty; return top
  return topPtr->getItem();
} //end getTop

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
  return topPtr == nullptr;
} //end isEmpty

template<class ItemType>
ItemType LinkedStack<ItemType>::max() const{return high;};

template<class ItemType>
ItemType LinkedStack<ItemType>::mean() const{return avg;};

//End of implementation file.

#endif