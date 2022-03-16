#ifndef STACK
#define STACK


#include "LinkedStack.h"
#include "iostream"

using namespace std;

template<class ItemType>
class Stack : public LinkedStack<ItemType>
{ 

  private:

    Node<ItemType>* topPtr;
    Node<ItemType>* nullPtr;
  
    int high = 0;
    int avg = 0;
    int numNodes = 0;
    int totalValue = 0;

  public:

    Stack()
    {
      topPtr = nullptr;
    }

    bool push(const ItemType& input)
    {
      //update max
      if(input > high)
      {
        high = input;
      }

      //update numNodes
      numNodes++;

      //update totalValue
      totalValue += input;
      
      //update mean
      avg = totalValue / numNodes;

      Node<ItemType>* newNode = new Node<ItemType>(input, topPtr);
      topPtr = newNode;
      newNode = nullptr;
      return true;
    };


    bool pop()
    {
      bool result = false;
      if(!LinkedStack<ItemType>::isEmpty() || !isEmpty())
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

        result = true;
      } //end if

      return result;
    } //end pop

    ItemType max() const
    {
      return high;
    };

    ItemType mean() const
    {
      return avg;
    }; 

    Stack<ItemType> operator+(const Stack<ItemType>& input2)
    {
      Stack<ItemType> newStack;
      Node<ItemType>* stackPtr;
      Node<ItemType>* runner2 = topPtr;
      Node<ItemType>* runner1 = input2.topPtr;
    
      
      Node<ItemType>* newNode1 = new Node<ItemType>(runner1->getItem());
      newStack.high = runner1->getItem();

      Node<ItemType>* newNode2 = new Node<ItemType>(runner2->getItem(), newNode1);
      if(runner2->getItem() > high)
      {
        newStack.high = runner2->getItem();
      }

      newStack.numNodes = 2;
      newStack.totalValue = runner1->getItem() + runner2->getItem();
      newStack.avg = newStack.totalValue / newStack.numNodes;

      newStack.topPtr = newNode2;
      stackPtr = newStack.topPtr;
      stackPtr->setNext(newNode1);
      stackPtr = stackPtr->getNext();



      runner1 = runner1->getNext();
      runner2 = runner2->getNext();

      while(runner2 != NULL)
      {
        newNode1 = new Node<ItemType>(runner1->getItem());
        if(runner1->getItem() > newStack.high)
        {
          newStack.high = runner1->getItem();
        }
        newNode2 = new Node<ItemType>(runner2->getItem(), newNode1);
        if(runner2->getItem() > newStack.high)
        {
          newStack.high = runner2->getItem();
        }
        newStack.numNodes += 2;
        newStack.totalValue = newStack.totalValue + runner1->getItem() + runner2->getItem();
        newStack.avg = newStack.totalValue / newStack.numNodes;
        stackPtr->setNext(newNode2);
        stackPtr = stackPtr->getNext();
        stackPtr->setNext(newNode1);
        stackPtr = stackPtr->getNext();
        runner1 = runner1->getNext();
        runner2 = runner2->getNext();
      }
      return newStack;
    };

    bool isEmpty()
    {
      if(numNodes == 0)
      {
        cout << "no nodes found" << endl;
      }
      return numNodes == 0;
    }

    void print()
    {
      cout << "print method" << endl;
      Node<ItemType>* runner = topPtr;
      while(runner != NULL)
      {
        cout << runner->getItem();
        runner = runner->getNext();
      }
      cout << endl;
      cout << high << ", " << avg << ", " << numNodes << ", " << totalValue << endl;
      cout << "print ended" << endl;
    }
};

#endif
