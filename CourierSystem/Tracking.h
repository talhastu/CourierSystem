#ifndef TRACKING_H
#define TRACKING_H

#include "Parcel.h"
#include <vector>
#include <list>

using namespace std;


class Tracking {
private:
    static const int TABLE_SIZE = 101;
    vector<list<Parcel>> table;

public:
    Tracking();

    int hashFunction(int id) const;

    void insert(const Parcel& p);
    void update(const Parcel& p);   
    bool find(int id, Parcel& result) const;

    void showParcel(int id) const;

    void showByStatus(string status) const;
    void showSummary() const;
};


#endif
