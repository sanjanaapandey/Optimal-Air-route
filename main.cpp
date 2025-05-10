
#include <iostream>
#include "airport_graph.cpp"

int main() {
    std::cout << "Debug: Program started.\n";

    AirportGraph graph;
    graph.loadRoutes("routes.dat");

    std::string src, dest;
    int choice;

    std::cout << "===== Optimal Air Route Planner =====\n";
    std::cout << "Enter Source Airport Code (e.g., DME): ";
    std::cin >> src;
    std::cout << "Enter Destination Airport Code (e.g., KZN): ";
    std::cin >> dest;

    std::cout << "\nChoose Algorithm:\n";
    std::cout << "1. Dijkstra\n2. A*\n3. Bellman-Ford\nEnter choice (1-3): ";
    std::cin >> choice;

    std::vector<std::string> path;
    int dist = -1;

    switch (choice) {
        case 1: tie(path, dist) = graph.dijkstra(src, dest); break;
        case 2: tie(path, dist) = graph.astar(src, dest); break;
        case 3: tie(path, dist) = graph.bellmanFord(src, dest); break;
        default: std::cout << "Invalid choice\n"; return 0;
    }

    if (path.empty()) {
        std::cout << "\nNo path found from " << src << " to " << dest << ".\n";
    } else {
        std::cout << "\nOptimal Path: ";
        for (const auto& p : path) std::cout << p << (p != dest ? " -> " : "");
        std::cout << "\nTotal Distance: " << dist << "\n";
    }

    return 0;
}
