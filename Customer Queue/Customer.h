#ifndef Customer_H
#define Customer_H

#include <iostream>
#include <vector>

class Customer {
    public:
        int timeOfArrival;
        int durationAtTeller;
        Customer();
        ~Customer();
};
#endif