#include <iostream>
#include <fstream>
#include "Customer.h"
#include "Simulation.h"
#include "QueueADT.h"
#include <vector>

using namespace std;


// begin implementation of Customer Methods

vector<Customer> readCustomers() {
    ifstream myFile;
    myFile.open("data.txt");
    vector<Customer> newCustomers;
    string myLine;
    int customers;

    getline(myFile, myLine);
    customers = std::stoi(myLine);

    int timeOfArrival;

    while(getline(myFile, myLine)) {
      int timeOfArrival = std::stoi(myLine);
      Customer newCustomer;
      newCustomer.timeOfArrival =  timeOfArrival;

      myLine = myLine.substr(myLine.find_first_of(' '));

      int durationAtTeller = std:: stoi(myLine);
      newCustomer.durationAtTeller = durationAtTeller;
      newCustomers.push_back(newCustomer);
    }
    return newCustomers;
}

Customer::Customer() {
    int timeOfArrival;
    int durationAtTeller;
}

Customer::~Customer() {

}


// begin implementation of Queue methods.

template <class T>
QueueADT<T>::QueueADT() {
    front = end = -1;
    size = 100;
    count = 0;
    array = new T [100];
}
template <class T>
void QueueADT<T>::enqueue(const T &input) {
    if (isEmpty()) {
        front = end = 0;
        array[end] = input;
    } 
    else if (isFull()) {
        cout << "Queue is full!" << endl;
        return;
    }
 

    else {
        end = (end+1)%size;
        array[end] = input;
    }
    count++;
}

template <class T>
void QueueADT<T>::dequeue() {
    if (isEmpty()){
        return;
    }

    else if (front == end){
        front = end = -1;
    }

    else
        front = (front+1)%size;
        count--;
}

template <class T>
T& QueueADT<T>::qfront() {
    if (isEmpty()) {  
        return array[front];
    }
    else {
        return array[front];
    }
}

template <class T>
bool QueueADT<T>::isEmpty() {
    if (front ==-1 && end == -1) {
        return true;
    }
    return false;
}
template <class T> 
bool QueueADT<T>::isFull() {
    return count == size;
}
template <class T>
int QueueADT<T>::getCount() {
    return count;
}


//end implementation of Queue methods


//begin implementation of simulation methods

Simulation::Simulation() {
}

Simulation::~Simulation() {

}
void Simulation::processCustomers(vector<Customer> input) {
    if (input.size() == 0) {
        return;
    }
    /*
      -Fill queue with customer arrival times (from input parameter)
      -Simulate customers arriving and leaving
        -How much time it takes for them to be processed
    */
   QueueADT<Customer> Q;
   int timeArrived = 0;
   int timePassed = 0;
   double totalTime = 0;
   int personalWaitTime = 0;
   maxDelay = 0;
   averageDelay = 0;

   for (int i = 0; i < input.size(); i++){
     Q.enqueue(input.at(i));
   }

   int count = Q.getCount();

   for(int j = 0; j < count; j++){
     timeArrived = input[j].timeOfArrival;
     personalWaitTime = timePassed - timeArrived;
     if (personalWaitTime > maxDelay) {
         maxDelay = personalWaitTime;
     }
     totalTime += personalWaitTime;
     timePassed += input[j].durationAtTeller;
     Q.dequeue();
   }
   averageDelay = totalTime/count;
}

void Simulation::printStatistics() {
    cout << "Max Delay = "<< maxDelay<< endl;
    cout << "Average Delay = " << averageDelay << endl;

}


// end implementation of Simulation Methods.

//please don't modify main function
int main() {
    vector<Customer> customers = readCustomers(); //read list of customers and arrival times from a file
    Simulation s;
    cout << "Processing Customers:" << endl;
    s.processCustomers(customers); //simulates the teller serving the customers in the queue
    s.printStatistics();  // prints out the maxium delay and the average delay.

    return 0;
}
