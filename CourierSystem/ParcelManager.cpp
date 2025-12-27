#include "ParcelManager.h"
#include <fstream>
#include <iostream>
extern Tracking trackingSystem;


ParcelManager::ParcelManager(std::string file) {
    filename = file;
    loadFromFile();
}

void ParcelManager::loadFromFile() {
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        // File does not exist yet, nothing to load
        return;
    }

    int id, priority;
    float weight;
    std::string zone, status;

    while (fin >> id >> priority >> weight >> zone >> status) {
        Parcel p(id, priority, weight, zone);

        // Restore correct status
        if (status != "Created") {
            p.updateStatus(status);
        }

        // Insert into heap
        priorityHeap.insert(p);

        // Insert into tracking system
        extern Tracking trackingSystem;
        trackingSystem.insert(p);
    }

    fin.close();
}


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

void ParcelManager::viewParcels() {
    priorityHeap.display();
}

void ParcelManager::processNextParcel() {
    if (priorityHeap.isEmpty()) {
        std::cout << "No parcels to process.\n";
        return;
    }

    Parcel p = priorityHeap.extractMax();
    p.updateStatus("Dispatched");
    trackingSystem.insert(p);
    
    saveToFile();

    std::cout << "Processed Parcel ID: " << p.getId() << "\n";
}
