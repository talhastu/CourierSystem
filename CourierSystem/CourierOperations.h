#ifndef COURIER_OPERATIONS_H
#define COURIER_OPERATIONS_H

#include "Courier.h"
//#include <queue>
//#include <stack>
#include <fstream>
#include "MyQueue.h"
#include "MyStack.h"

using namespace std;

class CourierOperations {
private:
    MyQueue<Courier> courierQueue;
    MyStack<Courier> undoStack;
    string filename = "couriers.txt";


public:
    void addCourier();
    void assignCourier();
    void undoAssignment();
    void viewCouriers();
    void loadFromFile();
    void saveToFile();

};




#endif
