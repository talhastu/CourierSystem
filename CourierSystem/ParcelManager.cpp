#include "ParcelManager.h"
#include <fstream>
#include <iostream>
#include<iomanip>

extern Tracking trackingSystem;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

// Constructor
ParcelManager::ParcelManager(std::string file) {
    filename = file;
    loadFromFile();
}

// Load parcels from file
void ParcelManager::loadFromFile() {
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        return;
    }

    int id, priority;
    float weight;
    std::string zone, status;

    while (fin >> id >> priority >> weight >> zone >> status) {
        Parcel p(id, priority, weight, zone);

        // restore status & history
        if (status != "Created") {
            p.updateStatus(status);
        }

        priorityHeap.insert(p);
        trackingSystem.insert(p);
    }

    fin.close();
}

// Save parcels to file
void ParcelManager::saveToFile() {
    std::ofstream fout(filename);
    auto parcels = priorityHeap.getAll();

    for (auto& p : parcels) {
        fout << p.getId() << " "
            << p.getPriority() << " "
            << p.getWeight() << " "
            << p.getZone() << " "
            << p.getStatus() << "\n";
    }
    fout.close();
}

// Add new parcel
void ParcelManager::addParcel() {
    int id, priority;
    float weight;
    std::string zone;

    std::cout << "Enter Parcel ID: ";
    std::cin >> id;
    std::cout << "Priority (1-Overnight, 2-2Day, 3-Normal): ";
    std::cin >> priority;
    std::cout << "Weight: ";
    std::cin >> weight;
    std::cout << "Destination Zone: ";
    std::cin >> zone;

    Parcel p(id, priority, weight, zone);

    priorityHeap.insert(p);
    trackingSystem.insert(p);

    saveToFile();
    std::cout << "Parcel added successfully!\n";
}

// View all parcels
void ParcelManager::viewParcels() {
    auto parcels = priorityHeap.getAll();

    if (parcels.empty()) {
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

    for (auto& p : parcels) {
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


// Process next parcel (FIXED)
void ParcelManager::processNextParcel() {
    if (priorityHeap.isEmpty()) {
        std::cout << "No parcels to process.\n";
        return;
    }

    Parcel p = priorityHeap.extractMax(); // or extractMin if using min-heap
    p.updateStatus("Dispatched");

    // IMPORTANT: update tracking, not insert
    trackingSystem.update(p);

    saveToFile();

    std::cout << "Processed Parcel ID: " << p.getId() << "\n";
}
