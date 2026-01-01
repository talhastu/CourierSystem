#include "Parcel.h"

// Default constructor
Parcel::Parcel() {
    id = 0;
    priority = 3;
    weight = 0.0;
    zone = "N/A";

    historyCount = 0;
    status = "Created";
    history[historyCount++] = "Created";
    history[historyCount++] = "Processing";   // ✅ added
}

// Parameterized constructor
Parcel::Parcel(int i, int p, float w, string z) {
    id = i;
    priority = p;
    weight = w;
    zone = z;

    historyCount = 0;
    status = "Created";
    history[historyCount++] = "Created";
    history[historyCount++] = "Processing";   //  added
}

int Parcel::getId() const { return id; }
int Parcel::getPriority() const { return priority; }
float Parcel::getWeight() const { return weight; }
string Parcel::getZone() const { return zone; }
string Parcel::getStatus() const { return status; }

void Parcel::updateStatus(string newStatus) {
    status = newStatus;

    if (historyCount < 10) {
        history[historyCount++] = newStatus;
    }
}

void Parcel::printHistory() const {
    cout << "\nParcel Status History:\n";
    for (int i = 0; i < historyCount; i++) {
        cout << " - " << history[i] << endl;
    }
}
