#ifndef PARCEL_MANAGER_H
#define PARCEL_MANAGER_H

#include "Heap.h"
#include <string>
#include "Tracking.h"

class ParcelManager {
private:
    Heap priorityHeap;
    std::string filename;

    void saveToFile();

public:
    ParcelManager(std::string file = "parcels.txt");

    void loadFromFile();
    void addParcel();
    void viewParcels();
    void processNextParcel();
};

#endif
