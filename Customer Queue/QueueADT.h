/*
    Author: Codey Hutton
    Date: November, 2021
    Prof: Zi
    
*/

#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H
#include <iostream>

using namespace std;

template <class T>
class QueueADT{
    private:   
        int front, end, size, count;
        T *array;

    public:
        QueueADT();
        virtual void enqueue(const T&);
        virtual void dequeue();
        virtual T& qfront();
        virtual bool isEmpty();  
        virtual bool isFull();
        virtual int getCount();
};

#endif