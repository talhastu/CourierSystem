#ifndef ROUTING_H
#define ROUTING_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Routing {
private:
    // Graph: city -> (neighbor city, distance)
    map<string, vector<pair<string, int>>> graph;

public:
    void addRoute(string from, string to, int distance);
    void findShortestPath(string source, string destination);
    void loadDefaultRoutes();
};

#endif
