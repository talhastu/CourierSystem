#include <iostream>
//#include "Utils.h"
#include <cstdlib>
#include "Parcel.h"
#include "ParcelManager.h"
#include "Tracking.h"

Tracking trackingSystem;


ParcelManager parcelManager;

    
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
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "Parcel Management\n";
        cout << "1. Add New Parcel\n";
        cout << "2. View All Parcels\n";
        cout << "3. Process Next Parcel\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            parcelManager.addParcel();
            pauseScreen();
            break;
        case 2:
            parcelManager.viewParcels();
            pauseScreen();
            break;
        case 3:
            parcelManager.processNextParcel();
            pauseScreen();
            break;
        }
    } while (choice != 0);
}



void routingMenu() {
    cout << "\n[Routing Menu Placeholder]\n";
    pauseScreen();
}

void trackingMenu() {
    int id;
    clearScreen();
    printHeader();

    cout << "Parcel Tracking\n";
    cout << "Enter Parcel ID: ";
    cin >> id;

    trackingSystem.showParcel(id);
    pauseScreen();
}


void courierMenu() {
    cout << "\n[Courier Menu Placeholder]\n";
    pauseScreen();
}
