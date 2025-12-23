#include <iostream>
//#include "Utils.h"
#include <cstdlib>
using namespace std;

// ===== Function Declarations =====
void mainMenu();
void parcelMenu();
void routingMenu();
void trackingMenu();
void courierMenu();

void clearScreen();
void pauseScreen();
void printHeader();

// ===== main() =====
int main() {
    mainMenu();
    return 0;
}

// ===== Utility Functions =====
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void printHeader() {
    cout << "=====================================\n";
    cout << "      SwiftEx Courier System\n";
    cout << "=====================================\n";
}

// ===== Menus =====
void mainMenu() {
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "1. Parcel Management\n";
        cout << "2. Parcel Routing\n";
        cout << "3. Parcel Tracking\n";
        cout << "4. Courier Operations\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: parcelMenu(); break;
        case 2: routingMenu(); break;
        case 3: trackingMenu(); break;
        case 4: courierMenu(); break;
        case 0: cout << "Exiting system...\n"; break;
        default:
            cout << "Invalid choice!\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void parcelMenu() {
    cout << "\n[Parcel Menu Placeholder]\n";
    pauseScreen();
}

void routingMenu() {
    cout << "\n[Routing Menu Placeholder]\n";
    pauseScreen();
}

void trackingMenu() {
    cout << "\n[Tracking Menu Placeholder]\n";
    pauseScreen();
}

void courierMenu() {
    cout << "\n[Courier Menu Placeholder]\n";
    pauseScreen();
}
