#ifndef COURIER_H
#define COURIER_H

#include <string>
using namespace std;

class Courier {
    int id;
    string name;
    bool available;   // true = Available, false = Busy


public:
    Courier(int i = 0, string n = "") {
        id = i;
        name = n;
        available = true;

    }

    int getId() const { return id; }
    string getName() const { return name; }


    bool isAvailable() const { return available; }
    void setAvailable(bool a) { available = a; }
};

#endif
