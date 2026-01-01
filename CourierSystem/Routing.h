#ifndef ROUTING_H
#define ROUTING_H

#include <string>
#include <vector>

using namespace std;


class Routing {
private:
    static const int MAX_CITIES = 20;

    string cities[MAX_CITIES];
    int cityCount;
    int distance[MAX_CITIES][MAX_CITIES];
    bool blocked[MAX_CITIES][MAX_CITIES];


    int getCityIndex(string city);

    void loadRoutesFromFile();
    void saveRouteToFile();

public:
    Routing();

    void addRoute();
    void viewRoutes();
    void findShortestPath();
    void blockRoute();
    void unblockRoute();

};

#endif
