#ifndef TRACKING_H
#define TRACKING_H

#include "Parcel.h"
#include <vector>
#include <list>

class Tracking {
private:
    static const int TABLE_SIZE = 101;
    std::vector<std::list<Parcel>> table;

    int hashFunction(int id) const;

public:
    Tracking();

    void insert(const Parcel& p);
    bool find(int id, Parcel& result) const;
    void showParcel(int id) const;
};

#endif
