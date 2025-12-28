#include "CourierOperations.h"
#include <iostream>
#include<iomanip>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void CourierOperations::addCourier() {
    int id;
    string name;

    cout << "Enter Courier ID: ";
    cin >> id;
    cout << "Enter Courier Name: ";
    cin >> name;

    courierQueue.push(Courier(id, name));
    saveToFile();
    system("cls");
    cout << "Courier added to queue.\n";
}

void CourierOperations::assignCourier() {
    if (courierQueue.empty()) {
        system("cls");
        cout << "No couriers available.\n";
        return;
    }

    Courier c = courierQueue.front();
    courierQueue.pop();

    undoStack.push(c);
    system("cls");
    cout << "Courier Assigned:\n";
    cout << "ID: " << c.getId() << " Name: " << c.getName() << endl;
}

void CourierOperations::undoAssignment() {
    if (undoStack.empty()) {
        system("cls");
        cout << "Nothing to undo.\n";
        return;
    }

    Courier c = undoStack.top();
    undoStack.pop();


    courierQueue.push(c);
    saveToFile();
    cout << "Last assignment undone.\n";
}

void CourierOperations::viewCouriers() {

    if (courierQueue.empty()) {
        cout << RED << "\n No couriers available.\n" << RESET;
        return;
    }

    cout << CYAN;
    cout << "+--------------------------------------------+\n";
    cout << "|               Courier List                 |\n";
    cout << "+--------------------------------------------+\n";
    cout << RESET;

    cout << YELLOW;
    cout << "| ID  | Name              | Status           |\n";
    cout << "+--------------------------------------------+\n";
    cout << RESET;

    // Copy queue so original is NOT destroyed
    MyQueue<Courier> temp = courierQueue;

    while (!temp.empty()) {
        Courier c = temp.front();
        temp.pop();

        cout << GREEN;
        cout << "| " << setw(3) << c.getId()
            << " | " << setw(17) << c.getName()
            << " |\n";
        cout << RESET;
    }

    cout << CYAN;
    cout << "+--------------------------------------------+\n";
    cout << RESET;
}



void CourierOperations::loadFromFile() {
    ifstream fin(filename);
    if (!fin.is_open()) return;

    int id;
    string name;

    while (fin >> id >> name) {
        courierQueue.push(Courier(id, name));
    }
    fin.close();
}

void CourierOperations::saveToFile() {
    ofstream fout(filename);
    MyQueue<Courier> temp = courierQueue;

    while (!temp.empty()) {
        Courier c = temp.front();
        temp.pop();
        fout << c.getId() << " " << c.getName() << endl;
    }
    fout.close();
}