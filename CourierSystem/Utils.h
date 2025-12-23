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


#include<iostream>
using namespace std;




void printHeader() {
    cout << "=====================================\n";
    cout << "      SwiftEx Courier System\n";
    cout << "=====================================\n";
}


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
        cout << "1. Insert New Parcel\n";
        cout << "2. Sort Parcels by Priority\n";
        cout << "3. Sort Parcels by Weight\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Insert Parcel Logic Here]\n";
            pauseScreen();
            break;
        case 2:
            cout << "[Priority Heap Sorting Here]\n";
            pauseScreen();
            break;
        case 3:
            cout << "[Weight Sorting Here]\n";
            pauseScreen();
            break;
        }
    } while (choice != 0);
}


void routingMenu() {
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "Parcel Routing\n";
        cout << "1. Find Shortest Route\n";
        cout << "2. Block Road\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Dijkstra Algorithm Here]\n";
            pauseScreen();
            break;
        case 2:
            cout << "[Block Edge in Graph]\n";
            pauseScreen();
            break;
        }
    } while (choice != 0);
}


void trackingMenu() {
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "Parcel Tracking\n";
        cout << "1. Track Parcel by ID\n";
        cout << "2. View Parcel History\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Hash Table Search]\n";
            pauseScreen();
            break;
        case 2:
            cout << "[Linked List History]\n";
            pauseScreen();
            break;
        }
    } while (choice != 0);
}


void courierMenu() {
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "Courier Operations\n";
        cout << "1. Assign Rider\n";
        cout << "2. View Pickup Queue\n";
        cout << "3. Undo Last Operation\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Queue + Assignment]\n";
            pauseScreen();
            break;
        case 2:
            cout << "[Display Queue]\n";
            pauseScreen();
            break;
        case 3:
            cout << "[Undo using Stack]\n";
            pauseScreen();
            break;
        }
    } while (choice != 0);
}
