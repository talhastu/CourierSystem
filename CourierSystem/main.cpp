#include <iostream>
//#include "Utils.h"
#include <cstdlib>
#include "Parcel.h"
#include "ParcelManager.h"
#include "Tracking.h"
#include "Routing.h"
#include "CourierOperations.h"
#include <iomanip>


    
using namespace std;

Routing routingSystem;


Tracking trackingSystem;


ParcelManager parcelManager;

CourierOperations courierOps;


const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";


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
    routingSystem.loadDefaultRoutes();
    courierOps.loadFromFile();


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

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << "|         SwiftEx Courier Management System    |\n";
        cout << "+=============================================+\n";
        cout << RESET;

        cout << GREEN;
        cout << "|  1. Parcel Management                       |\n";
        cout << "|  2. Parcel Routing                          |\n";
        cout << "|  3. Parcel Tracking                         |\n";
        cout << "|  4. Courier Operations                      |\n";
        cout << RESET;

        cout << RED;
        cout << "|  0. Exit                                    |\n";
        cout << RESET;

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << RESET;

        cout << WHITE << " Enter your choice: " << RESET;
        cin >> choice;

        switch (choice) {
        case 1: parcelMenu(); break;
        case 2: routingMenu(); break;
        case 3: trackingMenu(); break;
        case 4: system("cls"); courierMenu(); break;
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

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << "|              Parcel Management               |\n";
        cout << "+=============================================+\n";
        cout << RESET;

        cout << GREEN;
        cout << "|  1. Add New Parcel                          |\n";
        cout << "|  2. View All Parcels                        |\n";
        cout << "|  3. Process Next Parcel                    |\n";
        cout << RESET;

        cout << RED;
        cout << "|  0. Back                                   |\n";
        cout << RESET;

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << RESET;

        cout << " Enter choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1:
            cout << CYAN << "+--- Add New Parcel ---------------------------+\n" << RESET;
            parcelManager.addParcel();
            pauseScreen();
            break;

        case 2:
            cout << CYAN << "+--- All Parcels ------------------------------+\n" << RESET;
            parcelManager.viewParcels();
            pauseScreen();
            break;

        case 3:
            cout << CYAN << "+--- Process Parcel ---------------------------+\n" << RESET;
            parcelManager.processNextParcel();
            pauseScreen();
            break;
        }
    } while (choice != 0);
}



void routingMenu() {
    string source, destination;

    // List of valid cities
    string cities[] = {
        "Karachi", "Lahore", "Islamabad",
        "Peshawar", "Quetta", "Multan"
    };

    bool validSource = false, validDestination = false;

    clearScreen();

    cout << CYAN;
    cout << "+=============================================+\n";
    cout << "|               Parcel Routing                |\n";
    cout << "+=============================================+\n";
    cout << RESET;

    cout << " Enter Source City      : ";
    cin >> source;
    cout << " Enter Destination City : ";
    cin >> destination;

    // Validate source city
    for (string c : cities) {
        if (source == c) {
            validSource = true;
            break;
        }
    }

    // Validate destination city
    for (string c : cities) {
        if (destination == c) {
            validDestination = true;
            break;
        }
    }

    if (!validSource || !validDestination) {
        cout << RED;
        cout << "\n Invalid city entered!\n";
        cout << " Available cities are:\n";
        cout << RESET;

        cout << YELLOW;
        for (string c : cities) {
            cout << " - " << c << "\n";
        }
        cout << RESET;

        pauseScreen();
        return;
    }

    cout << CYAN;
    cout << "+---------------------------------------------+\n";
    cout << RESET;

    routingSystem.findShortestPath(source, destination);
    pauseScreen();
}



void trackingMenu() {
    int id;
    clearScreen();

    cout << CYAN;
    cout << "+=============================================+\n";
    cout << "|               Parcel Tracking               |\n";
    cout << "+=============================================+\n";
    cout << RESET;

    cout << " Enter Parcel ID: ";
    cin >> id;

    cout << CYAN;
    cout << "+---------------------------------------------+\n";
    cout << RESET;

    trackingSystem.showParcel(id);
    pauseScreen();
}



void courierMenu() {
    int choice;
    do {
        clearScreen();

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << "|             Courier Operations              |\n";
        cout << "+=============================================+\n";
        cout << RESET;

        cout << GREEN;
        cout << "|  1. Add Courier                             |\n";
        cout << "|  2. Assign Courier                         |\n";
        cout << "|  3. Undo Assignment                        |\n";
        cout << "|  4. View Couriers                          |\n";
        cout << RESET;

        cout << RED;
        cout << "|  0. Back                                   |\n";
        cout << RESET;

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << RESET;

        cout << " Enter choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1:
            cout << CYAN << "+--- Add Courier -----------------------------+\n" << RESET;
            courierOps.addCourier();
            pauseScreen();
            break;

        case 2:
            cout << CYAN << "+--- Assign Courier --------------------------+\n" << RESET;
            courierOps.assignCourier();
            pauseScreen();
            break;

        case 3:
            cout << CYAN << "+--- Undo Assignment -------------------------+\n" << RESET;
            courierOps.undoAssignment();
            pauseScreen();
            break;

        case 4:
            cout << CYAN << "+--- Courier List ----------------------------+\n" << RESET;
            courierOps.viewCouriers();
            pauseScreen();
            break;
        }
    } while (choice != 0);
}


