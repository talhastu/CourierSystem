#include "Tracking.h"
#include <iostream>

Tracking::Tracking() {
    table.resize(TABLE_SIZE);
}

int Tracking::hashFunction(int id) const {
    return id % TABLE_SIZE;
}

void Tracking::insert(const Parcel& p) {
    int index = hashFunction(p.getId());
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
