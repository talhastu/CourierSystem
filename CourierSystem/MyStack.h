#pragma once
using namespace std;

template <class T>
class MyStack {
private:
    T* arr;
    int topIndex;
    int capacity;

public:
    MyStack(int cap = 100) {
        capacity = cap;
        arr = new T[capacity];
        topIndex = -1;
    }

    bool empty() {
        return topIndex == -1;
    }

    void push(T item) {
        if (topIndex == capacity - 1) return;
        arr[++topIndex] = item;
    }

    T pop() {
        return arr[topIndex--];
    }

    T top() {
        return arr[topIndex];
    }
};
