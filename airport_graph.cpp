#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

class AirportGraph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList; // Airport -> [(Destination, Distance)]

public:
    void addEdge(const string& src, const string& dest, int distance) {
        adjList[src].push_back({dest, distance});
        adjList[dest].push_back({src, distance}); // Assuming undirected graph
    }

    void dijkstra(const string& start) {
        unordered_map<string, int> distances;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        
        for (const auto& [airport, _] : adjList) {
            distances[airport] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            auto [currDist, currAirport] = pq.top(); pq.pop();
            if (currDist > distances[currAirport]) continue;
            
            for (const auto& [neighbor, weight] : adjList[currAirport]) {
                int newDist = currDist + weight;
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    pq.push({newDist, neighbor});
                }
            }
        }
        
        cout << "Shortest distances from " << start << ":\n";
        for (const auto& [airport, dist] : distances) {
            cout << airport << " -> " << (dist == numeric_limits<int>::max() ? "INF" : to_string(dist)) << "\n";
        }
    }
};

int main() {
    AirportGraph graph;
    graph.addEdge("JFK", "LAX", 3000);
    graph.addEdge("JFK", "ORD", 800);
    graph.addEdge("ORD", "LAX", 2000);
    graph.addEdge("LAX", "DFW", 1500);
    graph.addEdge("DFW", "JFK", 1600);
    
    graph.dijkstra("JFK");
    return 0;
}
