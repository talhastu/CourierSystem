#include "Routing.h"
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

void Routing::addRoute(string from, string to, int distance) {
    graph[from].push_back({ to, distance });
    graph[to].push_back({ from, distance }); // bidirectional
}

void Routing::loadDefaultRoutes() {
    addRoute("Lahore", "Islamabad", 380);
    addRoute("Lahore", "Faisalabad", 120);
    addRoute("Islamabad", "Peshawar", 180);
    addRoute("Faisalabad", "Multan", 240);
    addRoute("Multan", "Karachi", 900);
}

void Routing::findShortestPath(string source, string destination) {
    map<string, int> dist;
    map<string, string> parent;

    for (auto& city : graph)
        dist[city.first] = INT_MAX;

    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<>
    > pq;

    dist[source] = 0;
    pq.push({ 0, source });

    while (!pq.empty()) {
        auto [currentDist, city] = pq.top();
        pq.pop();

        for (auto& neighbor : graph[city]) {
            int newDist = currentDist + neighbor.second;
            if (newDist < dist[neighbor.first]) {
                dist[neighbor.first] = newDist;
                parent[neighbor.first] = city;
                pq.push({ newDist, neighbor.first });
            }
        }
    }

    if (dist[destination] == INT_MAX) {
        cout << "No route found.\n";
        return;
    }

    cout << "\nShortest Distance: " << dist[destination] << " km\n";
    cout << "Route: ";

    string current = destination;
    while (current != source) {
        cout << current << " <- ";
        current = parent[current];
    }
    cout << source << endl;
}
