#include "Routing.h"
#include <iostream>
#include <climits>
#include <fstream>
#include <iomanip>

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

using namespace std;

Routing::Routing() {
    cityCount = 0;

    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            distance[i][j] = INT_MAX;
            blocked[i][j] = false;  
        }
    }

    loadRoutesFromFile();
}


int Routing::getCityIndex(string city) {
    for (int i = 0; i < cityCount; i++) {
        if (cities[i] == city)
            return i;
    }
    return -1;
}


void Routing::loadRoutesFromFile() {
    ifstream file("routes.txt");

    string from, to;
    int dist;
    int blockFlag = 0;

    while (file >> from >> to >> dist) {

        if (!(file >> blockFlag))
            blockFlag = 0;

        int i = getCityIndex(from);
        if (i == -1) {
            cities[cityCount] = from;
            i = cityCount++;
        }

        int j = getCityIndex(to);
        if (j == -1) {
            cities[cityCount] = to;
            j = cityCount++;
        }

        distance[i][j] = distance[j][i] = dist;
        blocked[i][j] = blocked[j][i] = (blockFlag == 1);
    }

    file.close();
}



void Routing::saveRouteToFile() {
    ofstream file("routes.txt");

    for (int i = 0; i < cityCount; i++) {
        for (int j = i + 1; j < cityCount; j++) {
            if (distance[i][j] != INT_MAX) {
                file << cities[i] << " "
                    << cities[j] << " "
                    << distance[i][j] << " "
                    << blocked[i][j] << endl;
            }
        }
    }

    file.close();
}






void Routing::addRoute() {
    string from, to;
    int dist;

    cout << "Enter source city: ";
    cin >> from;
    cout << "Enter destination city: ";
    cin >> to;
    cout << "Enter distance: ";
    cin >> dist;

    int i = getCityIndex(from);
    if (i == -1) {
        cities[cityCount] = from;
        i = cityCount++;
    }

    int j = getCityIndex(to);
    if (j == -1) {
        cities[cityCount] = to;
        j = cityCount++;
    }

    distance[i][j] = distance[j][i] = dist;

    saveRouteToFile();

    cout << "Route added & saved successfully!\n";
}


void Routing::viewRoutes() {
    system("cls");

    cout << CYAN;
    cout << "+=====================================================+\n";
    cout << "|                AVAILABLE ROUTES                     |\n";
    cout << "+=====================================================+\n";
    cout << RESET;

    cout << YELLOW;
    cout << "| From City          | To City            | Dist  | Status   |\n";
    cout << "+--------------------+--------------------+------------------+\n";
    cout << RESET;

    bool found = false;

    for (int i = 0; i < cityCount; i++) {
        for (int j = i + 1; j < cityCount; j++) {
            if (distance[i][j] != INT_MAX) {
                found = true;

                string status = blocked[i][j] ? "BLOCKED" : "ACTIVE";


                cout << GREEN;
                cout << "| " << left << setw(18) << cities[i]
                    << " | " << setw(18) << cities[j]
                    << " | " << setw(6) << distance[i][j]
                    << " | " << setw(8) << status << " |\n";

                cout << RESET;
            }
        }
    }

    if (!found) {
        cout << RED;
        cout << "|           No routes available in system             |\n";
        cout << RESET;
    }

    cout << CYAN;
    cout << "+=====================================================+\n";
    cout << RESET;

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}




void Routing::findShortestPath() {
    string src, dest;
    cout << CYAN << " Enter source city: " << RESET;
    cin >> src;
    cout << CYAN << " Enter destination city: " << RESET;
    cin >> dest;

    int s = getCityIndex(src);
    int d = getCityIndex(dest);

    if (s == -1 || d == -1) {
        cout << RED << "\n City not found!" << RESET << endl;
        return;
    }

    int dist[MAX_CITIES];
    bool visited[MAX_CITIES];
    int parent[MAX_CITIES];

    for (int i = 0; i < cityCount; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[s] = 0;

    //  Dijkstra
    for (int count = 0; count < cityCount - 1; count++) {
        int u = -1;
        for (int i = 0; i < cityCount; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < cityCount; v++) {
            if (!visited[v] && distance[u][v] != INT_MAX && !blocked[u][v] &&
                dist[u] + distance[u][v] < dist[v]) {

                dist[v] = dist[u] + distance[u][v];
                parent[v] = u;  
            }
        }
    }

    if (dist[d] == INT_MAX) {
        cout << RED << "\n No route found!" << RESET << endl;
        return;
    }

   
    int path[MAX_CITIES];
    int pathLength = 0;

    for (int v = d; v != -1; v = parent[v])
        path[pathLength++] = v;

    // Output
    cout << CYAN;
    cout << "\n+=============================================+\n";
    cout << "|            Shortest Route Found              |\n";
    cout << "+=============================================+\n";
    cout << RESET;

    cout << GREEN << "\n Total Distance : "
        << dist[d] << " km\n\n" << RESET;

    cout << YELLOW << " Route :\n   " << RESET;

    for (int i = pathLength - 1; i >= 0; i--) {
        cout << GREEN << cities[path[i]] << RESET;
        if (i != 0)
            cout << CYAN << "  ->  " << RESET;
    }

    cout << endl;

    cout << CYAN;
    cout << "\n+=============================================+\n";
    cout << RESET;
}


void Routing::blockRoute() {
    string from, to;
    cout << "Enter source city: ";
    cin >> from;
    cout << "Enter destination city: ";
    cin >> to;

    int i = getCityIndex(from);
    int j = getCityIndex(to);

    if (i == -1 || j == -1 || distance[i][j] == INT_MAX) {
        cout << RED << "\nRoute not found!\n" << RESET;
        return;
    }

    blocked[i][j] = blocked[j][i] = true;
    saveRouteToFile();

    cout << GREEN << "\nRoute BLOCKED successfully!\n" << RESET;
}


void Routing::unblockRoute() {
    string from, to;
    cout << "Enter source city: ";
    cin >> from;
    cout << "Enter destination city: ";
    cin >> to;

    int i = getCityIndex(from);
    int j = getCityIndex(to);

    if (i == -1 || j == -1 || distance[i][j] == INT_MAX) {
        cout << RED << "\nRoute not found!\n" << RESET;
        return;
    }

    blocked[i][j] = blocked[j][i] = false;
    saveRouteToFile();

    cout << GREEN << "\nRoute UNBLOCKED successfully!\n" << RESET;
}
