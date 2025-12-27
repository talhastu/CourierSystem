#ifndef ROUTING_H
#define ROUTING_H

#include <string>
#include <vector>
#include <map>

class Routing {
private:
    std::map<std::string, std::vector<std::pair<std::string, int>>> graph;

public:
    void addRoute(std::string from, std::string to, int distance);
    void findShortestPath(std::string source, std::string destination);
    void loadDefaultRoutes();
};

#endif
