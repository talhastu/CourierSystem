#ifndef HEAP_H
#define HEAP_H

#include "Parcel.h"
#include <vector>

class Heap {
private:
    std::vector<Parcel> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(const Parcel& p);
    Parcel extractMax();
    bool isEmpty() const;
    void display() const;
    std::vector<Parcel> getAll() const;
};

#endif
