#pragma once
using namespace std;

template <class T>
class MyQueue {
private:
    T* arr;
    int frontIndex, rearIndex, size, capacity;

public:
    MyQueue(int cap = 100) {
        capacity = cap;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = -1;
        size = 0;
    }

    bool empty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }

    void push(T item) {
        if (isFull()) return;
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = item;
        size++;
    }

    T pop() {
        T item = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        size--;
        return item;
    }

    T front() {
        return arr[frontIndex];
    }
};
