#include "Parcel.h"
#include <iostream>

// Constructor
Parcel::Parcel(int id, int priority, float weight, string zone) {
    this->id = id;
    this->priority = priority;
    this->weight = weight;
    this->zone = zone;
    status = "Created";
    history.push_back("Parcel Created");
}

// Getters
int Parcel::getId() const {
    return id;
}

int Parcel::getPriority() const {
    return priority;
}

float Parcel::getWeight() const {
    return weight;
}

string Parcel::getZone() const {
    return zone;
}

string Parcel::getStatus() const {
    return status;
}

// Status update
void Parcel::updateStatus(string newStatus) {
    status = newStatus;
    history.push_back(newStatus);
}

// Print history
void Parcel::printHistory() const {
    cout << "\nParcel History:\n";
    for (const string& event : history) {
        cout << "- " << event << endl;
    }
}
