#include "ParcelManager.h"
#include <fstream>
#include <iostream>
#include<iomanip>

using namespace std;

extern Tracking trackingSystem;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

// Constructor
ParcelManager::ParcelManager(string file) {
    filename = file;
    heapSize = 0;     
    loadFromFile();
}

void ParcelManager::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap[parent].getPriority() <= heap[index].getPriority())
            break;

        Parcel temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;

        index = parent;
    }
}

void ParcelManager::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heapSize &&
            heap[left].getPriority() < heap[smallest].getPriority())
            smallest = left;

        if (right < heapSize &&
            heap[right].getPriority() < heap[smallest].getPriority())
            smallest = right;

        if (smallest == index)
            break;

        Parcel temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;

        index = smallest;
    }
}


// Load parcels from file
void ParcelManager::loadFromFile() {
    ifstream fin(filename);

    if (!fin.is_open()) {
        return;
    }

    int id, priority;
    float weight;
    string zone, status;

    while (fin >> id >> priority >> weight >> zone >> status) {
        Parcel p(id, priority, weight, zone);

        // restore status & history
        if (status != "Created") {
            p.updateStatus(status);
        }

        heap[heapSize] = p;
        heapifyUp(heapSize);
        heapSize++;

        trackingSystem.insert(p);
    }

    fin.close();
}

// Save parcels to file
void ParcelManager::saveToFile() {
    ofstream fout(filename);

    for (int i = 0; i < heapSize; i++) {
        fout << heap[i].getId() << " "
            << heap[i].getPriority() << " "
            << heap[i].getWeight() << " "
            << heap[i].getZone() << " "
            << heap[i].getStatus() << "\n";
    }
    fout.close();

}

// Add new parcel
void ParcelManager::addParcel() {
    int id, priority;
    float weight;
    string zone;

    cout << "Enter Parcel ID: ";
    cin >> id;
    cout << "Priority (1-Overnight, 2-2Day, 3-Normal): ";
    cin >> priority;
    cout << "Weight: ";
    cin >> weight;
    cout << "Destination Zone: ";
    cin >> zone;

    Parcel p(id, priority, weight, zone);

    heap[heapSize] = p;
    heapifyUp(heapSize);
    heapSize++;

    trackingSystem.insert(p);
    saveToFile();

    std::cout << "Parcel added successfully!\n";
}

// View all parcels
void ParcelManager::viewParcels() {
    if (heapSize == 0) {
        cout << RED << "\n No parcels available.\n" << RESET;
        return;
    }


    cout << CYAN;
    cout << "+------------------------------------------------------------------+\n";
    cout << "|                          All Parcels                             |\n";
    cout << "+------------------------------------------------------------------+\n";
    cout << RESET;

    cout << YELLOW;
    cout << "| ID  | Priority | Weight | Zone        | Status                  |\n";
    cout << "+------------------------------------------------------------------+\n";
    cout << RESET;

    for (int i = 0; i < heapSize; i++) {
        Parcel& p = heap[i];
        cout << GREEN;
        cout << "| " << setw(3) << p.getId()
            << " | " << setw(8) << p.getPriority()
            << " | " << setw(6) << p.getWeight()
            << " | " << setw(11) << p.getZone()
            << " | " << setw(22) << p.getStatus()
            << " |\n";
        cout << RESET;
    }

    cout << CYAN;
    cout << "+------------------------------------------------------------------+\n";
    cout << RESET;
}


void ParcelManager::processNextParcel() {
    if (heapSize == 0) {
        cout << RED << "No parcels to process.\n" << RESET;
        return;
    }

    Parcel p = heap[0];           
    heap[0] = heap[heapSize - 1];
    heapSize--;

    heapifyDown(0);

    p.updateStatus("Dispatched");
    trackingSystem.update(p);
    saveToFile();

    cout << GREEN << "Processed Parcel ID: "
        << p.getId() << RESET << endl;
}


void ParcelManager::deliverParcel() {
    int id;
    cout << "Enter Parcel ID to deliver: ";
    cin >> id;

    Parcel p;
    if (!trackingSystem.find(id, p)) {
        cout << "Parcel not found!\n";
        return;
    }

    // State validation
    if (p.getStatus() == "Delivered") {
        cout << "Parcel already delivered!\n";
        return;
    }

    if (p.getStatus() == "Lost") {
        cout << "Parcel is LOST. Recover it first.\n";
        return;
    }

    if (p.getStatus() != "Dispatched" && p.getStatus() != "Recovered") {
        cout << "Parcel must be dispatched or recovered before delivery!\n";
        return;
    }

    // 40% chance of loss
    int chance = rand() % 100;

    if (chance < 40) {
        p.updateStatus("Lost");
        trackingSystem.update(p);

        cout << " Parcel LOST during delivery!\n";
        cout << "You can attempt recovery.\n";
    }
    else {
        p.updateStatus("Delivered");
        trackingSystem.update(p);

        cout << " Parcel Delivered Successfully!\n";
    }

    saveToFile();
}

void ParcelManager::recoverParcel() {
    int id;
    cout << "Enter Parcel ID to recover: ";
    cin >> id;

    Parcel p;
    if (!trackingSystem.find(id, p)) {
        cout << "Parcel not found!\n";
        return;
    }

    if (p.getStatus() != "Lost") {
        cout << "Parcel is not marked as LOST!\n";
        return;
    }

    p.updateStatus("Recovered");
    trackingSystem.update(p);

    saveToFile();

    cout << "Parcel recovered successfully!\n";
}


