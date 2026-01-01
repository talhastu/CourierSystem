#ifndef PARCEL_H
#define PARCEL_H

#include <string>
#include <iostream>

using namespace std;

class Parcel {
private:
    int id;
    int priority;
    float weight;
    string zone;
    string status;

    string history[10];
    int historyCount;

public:
    Parcel();
    Parcel(int i, int p, float w, string z);

    int getId() const;
    int getPriority() const;
    float getWeight() const;
    string getZone() const;
    string getStatus() const;

    void updateStatus(string newStatus);
    void printHistory() const;
};

#endif
