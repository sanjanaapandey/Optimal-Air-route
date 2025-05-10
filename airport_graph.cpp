
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

struct Edge {
    string to;
    int weight;
};

class AirportGraph {
private:
    unordered_map<string, vector<Edge>> adjList;

public:
    void loadRoutes(const string& filename) {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string airline, flight, src, srcID, dest, destID, temp1, temp2, aircraft;
            getline(ss, airline, ',');
            getline(ss, flight, ',');
            getline(ss, src, ',');
            getline(ss, srcID, ',');
            getline(ss, dest, ',');
            getline(ss, destID, ',');
            getline(ss, temp1, ',');
            getline(ss, temp2, ',');
            getline(ss, aircraft, ',');

            if (!src.empty() && !dest.empty()) {
                adjList[src].push_back({ dest, 1 });
            }
        }
    }

    vector<string> reconstructPath(unordered_map<string, string>& prev, string src, string dest) {
        vector<string> path;
        for (string at = dest; at != ""; at = prev[at]) {
            path.push_back(at);
            if (at == src) break;
        }
        reverse(path.begin(), path.end());
        return (path.front() == src) ? path : vector<string>();
    }

    pair<vector<string>, int> dijkstra(string src, string dest) {
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;
        set<pair<int, string>> pq;

        for (auto& [node, _] : adjList) dist[node] = INT_MAX;
        dist[src] = 0;
        pq.insert({ 0, src });

        while (!pq.empty()) {
            auto [currentDist, u] = *pq.begin();
            pq.erase(pq.begin());

            for (const Edge& edge : adjList[u]) {
                string v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    pq.erase({ dist[v], v });
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.insert({ dist[v], v });
                }
            }
        }

        vector<string> path = reconstructPath(prev, src, dest);
        return { path, dist[dest] == INT_MAX ? -1 : dist[dest] };
    }

    pair<vector<string>, int> bellmanFord(string src, string dest) {
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;

        for (auto& [node, _] : adjList) dist[node] = INT_MAX;
        dist[src] = 0;

        for (size_t i = 0; i < adjList.size() - 1; ++i) {
            for (auto& [u, edges] : adjList) {
                for (const Edge& edge : edges) {
                    if (dist[u] != INT_MAX && dist[u] + edge.weight < dist[edge.to]) {
                        dist[edge.to] = dist[u] + edge.weight;
                        prev[edge.to] = u;
                    }
                }
            }
        }

        vector<string> path = reconstructPath(prev, src, dest);
        return { path, dist[dest] == INT_MAX ? -1 : dist[dest] };
    }

    pair<vector<string>, int> astar(string src, string dest) {
        return dijkstra(src, dest); // heuristic = 0 (same as Dijkstra)
    }
};
