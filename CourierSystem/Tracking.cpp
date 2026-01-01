#include "Tracking.h"
#include <iostream>

Tracking::Tracking() {
    table.resize(TABLE_SIZE);
}

int Tracking::hashFunction(int id) const {
    return id % TABLE_SIZE;
}
void Tracking::insert(const Parcel& p) 
{
    int index = hashFunction(p.getId());
    for (const auto& existing : table[index]) {
        if (existing.getId() == p.getId()) {
            return;
        }
    }
    table[index].push_back(p);
}

void Tracking::update(const Parcel& p) {
    int index = hashFunction(p.getId());

    for (auto& stored : table[index]) {
        if (stored.getId() == p.getId()) {
            stored = p;   
            return;
        }
    }

    // If not found, insert
    table[index].push_back(p);
}


bool Tracking::find(int id, Parcel& result) const {
    int index = hashFunction(id);
    for (const auto& p : table[index]) {
        if (p.getId() == id) {
            result = p;
            return true;
        }
    }
    return false;
}

void Tracking::showParcel(int id) const {
    Parcel p(0, 0, 0, "");
    if (find(id, p)) {
        std::cout << "\nParcel Found\n";
        std::cout << "ID: " << p.getId() << "\n";
        std::cout << "Current Status: " << p.getStatus() << "\n";
        p.printHistory();
    }
    else {
        std::cout << "Parcel not found!\n";
    }
}


void Tracking::showByStatus(string status) const {
    bool found = false;

    cout << "\nParcels with status: " << status << "\n";

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (const auto& p : table[i]) {
            if (p.getStatus() == status) {
                found = true;
                cout << "ID: " << p.getId()
                    << " | Zone: " << p.getZone()
                    << " | Priority: " << p.getPriority()
                    << endl;
            }
        }
    }

    if (!found) {
        cout << "No parcels found with this status.\n";
    }
}

void Tracking::showSummary() const {
    int created = 0, dispatched = 0, delivered = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (const auto& p : table[i]) {
            if (p.getStatus() == "Created")
                created++;
            else if (p.getStatus() == "Dispatched")
                dispatched++;
            else if (p.getStatus() == "Delivered")
                delivered++;
        }
    }

    cout << "\n==== Parcel Tracking Summary ====\n";
    cout << "Created    : " << created << endl;
    cout << "Dispatched : " << dispatched << endl;
    cout << "Delivered  : " << delivered << endl;
}

