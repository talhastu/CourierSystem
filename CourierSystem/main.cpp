#include <iostream>
#include <cstdlib>
#include "Parcel.h"
#include "ParcelManager.h"
#include "Tracking.h"
#include "Routing.h"
#include "CourierOperations.h"
#include <iomanip>
    
using namespace std;

Routing routing;
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
void routingMenu(Routing& r);
void trackingMenu();
void courierMenu();
void clearScreen();
void pauseScreen();
void printHeader();

// ===== main() =====
int main() {
    srand(time(0));
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
        case 2: routingMenu(routing); break;
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
        cout << "|  3. Process Next Parcel                     |\n";
        cout << "|  4. Deliver Parcel                          |\n";
        cout << "|  5. Recover Lost Parcel                     |\n";


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
        case 4:
            cout << CYAN << "+--- Deliver Parcel ---------------------------+\n" << RESET;
            parcelManager.deliverParcel();
            pauseScreen();
            break;
        case 5:
            cout << CYAN << "+--- Deliver Parcel ---------------------------+\n" << RESET;
            parcelManager.recoverParcel();
            break;

        }
    } while (choice != 0);
}



void routingMenu(Routing& r) {
    int choice;
    do {
        clearScreen();

        cout << CYAN;
        cout << "+=============================================+\n";
        cout << "|                Routing Management            |\n";
        cout << "+=============================================+\n";
        cout << RESET;

        cout << GREEN;
        cout << "|  1. Add New Route                           |\n";
        cout << "|  2. View All Routes                        |\n";
        cout << "|  3. Find Shortest Route                    |\n";
        cout << "|  4. Block Route                            |\n";
        cout << "|  5. Unblock Route                          |\n";
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
            r.addRoute();
            break;
        case 2:
            r.viewRoutes();
            break;
        case 3:
            r.findShortestPath();
            break;
        case 4:
            r.blockRoute();
            break;
        case 5:
            r.unblockRoute();
            break;
        case 0:
            return;
        default:
            cout << RED << " Invalid choice!" << RESET << endl;
        }

        system("pause");
    } while (true);
}



void trackingMenu() {
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << CYAN;
        cout << "+=====================================+\n";
        cout << "|         Parcel Tracking Menu        |\n";
        cout << "+=====================================+\n";
        cout << RESET;

        cout << GREEN;
        cout << "| 1. Track Parcel by ID               |\n";
        cout << "| 2. View Dispatched Parcels          |\n";
        cout << "| 3. View Delivered Parcels           |\n";
        cout << "| 4. View Pending Parcels             |\n";
        cout << "| 5. Tracking Summary Report          |\n";
        cout << RESET;

        cout << RED;
        cout << "| 0. Back                             |\n";
        cout << RESET;

        cout << CYAN;
        cout << "+=====================================+\n";
        cout << RESET;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            cout << "Enter Parcel ID: ";
            cin >> id;
            trackingSystem.showParcel(id);
            break;
        }
        case 2:
            trackingSystem.showByStatus("Dispatched");
            break;
        case 3:
            trackingSystem.showByStatus("Delivered");
            break;
        case 4:
            trackingSystem.showByStatus("Created");
            break;
        case 5:
            trackingSystem.showSummary();
            break;
        }
        pauseScreen();
    } while (choice != 0);
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


