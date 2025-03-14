#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

void loadRoutes(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string source, destination, distance;
        
        // Assuming the dataset format: source, destination, distance
        getline(ss, source, ',');
        getline(ss, destination, ',');
        getline(ss, distance, ',');

        cout << "Route: " << source << " -> " << destination << " Distance: " << distance << " miles" << endl;
    }

    file.close();
}

int main() {
    string filename = "routes.dat";
    loadRoutes(filename);
    return 0;
}
