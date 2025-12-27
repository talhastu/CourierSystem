#include "Tracking.h"
#include <iostream>

Tracking::Tracking() {
    table.resize(TABLE_SIZE);
}

int Tracking::hashFunction(int id) const {
    return id % TABLE_SIZE;
}

// Insert ONLY if parcel does not exist
void Tracking::insert(const Parcel& p) {
    int index = hashFunction(p.getId());

    for (const auto& existing : table[index]) {
        if (existing.getId() == p.getId()) {
            return; // already exists
        }
    }
    table[index].push_back(p);
}

// Update existing parcel (KEEP HISTORY)
bool Tracking::update(const Parcel& p) {
    int index = hashFunction(p.getId());

    for (auto& existing : table[index]) {
        if (existing.getId() == p.getId()) {
            existing = p;   // overwrite with updated parcel (history preserved)
            return true;
        }
    }
    return false;
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
