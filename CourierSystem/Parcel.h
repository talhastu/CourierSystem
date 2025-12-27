#ifndef PARCEL_H
#define PARCEL_H

#include <string>
#include <vector>
using namespace std;

class Parcel {
private:
    int id;
    int priority;        // 1 = Overnight, 2 = 2-Day, 3 = Normal
    float weight;
    string zone;
    string status;
    vector<string> history;

public:
    // Constructor
    Parcel(int id, int priority, float weight, string zone);

    // Getters
    int getId() const;
    int getPriority() const;
    float getWeight() const;
    string getZone() const;
    string getStatus() const;

    // Status & history
    void updateStatus(string newStatus);
    void printHistory() const;
};

#endif
