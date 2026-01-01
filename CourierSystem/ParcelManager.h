#ifndef PARCEL_MANAGER_H
#define PARCEL_MANAGER_H

#include <string>
#include "Tracking.h"
#include "Parcel.h"

using namespace std;

#define MAX_PARCELS 100

class ParcelManager {
private:
    Parcel heap[MAX_PARCELS];
    int heapSize;
    string filename;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void saveToFile();

public:
    ParcelManager(string file = "parcels.txt");

    void loadFromFile();
    void addParcel();
    void viewParcels();
    void processNextParcel();
    void deliverParcel();
    void recoverParcel();


};

#endif
