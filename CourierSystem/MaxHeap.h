#pragma once
using namespace std;

class MaxHeap {
private:
    Parcel heap[100];
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    MaxHeap() { size = 0; }

    bool isEmpty() {
        return size == 0;
    }

    void insert(Parcel p) {
        heap[size] = p;
        int i = size;
        size++;

        while (i != 0 && heap[parent(i)].getPriority() > heap[i].getPriority()) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    Parcel extractMax() {
        Parcel root = heap[0];
        heap[0] = heap[size - 1];
        size--;

        heapify(0);
        return root;
    }

    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < size && heap[l].getPriority() < heap[smallest].getPriority())
            smallest = l;

        if (r < size && heap[r].getPriority() < heap[smallest].getPriority())
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};
