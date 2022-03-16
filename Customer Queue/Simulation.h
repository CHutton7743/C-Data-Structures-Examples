#ifndef Simulation_H
#define Simulation_H

class Simulation {
    public:
        double averageDelay = -1;
        int maxDelay = -1;
        Simulation();
        virtual ~Simulation();
        virtual void processCustomers(std::vector<Customer> input);
        virtual void printStatistics();
};
#endif



