#include "Heap.h"
#include <iostream>

void Heap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].getPriority() > heap[parent].getPriority())
            break;
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

void Heap::heapifyDown(int index) {
    int size = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left].getPriority() < heap[largest].getPriority())
            largest = left;

        if (right < size && heap[right].getPriority() < heap[largest].getPriority())
            largest = right;

        if (largest == index)
            break;

        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}

void Heap::insert(const Parcel& p) {
    heap.push_back(p);
    heapifyUp(heap.size() - 1);
}

Parcel Heap::extractMax() {
    Parcel maxParcel = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
        heapifyDown(0);
    return maxParcel;
}

bool Heap::isEmpty() const {
    return heap.empty();
}

void Heap::display() const {
    std::cout << "\nID\tPriority\tWeight\tZone\tStatus\n";
    for (const auto& p : heap) {
        std::cout << p.getId() << "\t"
            << p.getPriority() << "\t\t"
            << p.getWeight() << "\t"
            << p.getZone() << "\t"
            << p.getStatus() << "\n";
    }
}

std::vector<Parcel> Heap::getAll() const {
    return heap;
}
