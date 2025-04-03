// dijsktras.cpp

// Main Execution

/*int main(int argc, char *argv[]) {
    return 0;
}*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

struct Node {
    int row, col, cost;
    bool operator>(const Node& other) const {
        return cost > other.cost; // Min-heap priority
    }
};

// Function to perform Dijkstra's algorithm
void dijkstra(vector<vector<char>>& map, unordered_map<char, int>& tileCosts, 
              pair<int, int> start, pair<int, int> end) {
    int rows = map.size(), cols = map[0].size();
    
    // Distance matrix initialized to maximum possible integer value
    vector<vector<int>> dist(rows, vector<int>(cols, numeric_limits<int>::max()));
    
    // Parent matrix to reconstruct the path
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    // Priority queue (min-heap) for processing nodes
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    // Initialize the starting position
    dist[start.first][start.second] = tileCosts[map[start.first][start.second]];
    pq.push({start.first, start.second, dist[start.first][start.second]});

    // Possible movement directions (up, down, left, right)
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int cr = current.row, cc = current.col;

        // Stop early if we've reached the destination
        if (cr == end.first && cc == end.second) break;

        for (auto [dr, dc] : directions) {
            int nr = cr + dr, nc = cc + dc;

            // Ensure we're within bounds
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int newCost = dist[cr][cc] + tileCosts[map[nr][nc]];

                // If the new cost is lower, update the path
                if (newCost < dist[nr][nc]) {
                    dist[nr][nc] = newCost;
                    pq.push({nr, nc, newCost});
                    parent[nr][nc] = {cr, cc};  // Store the previous node for path reconstruction
                }
            }
        }
    }

    // Output the total cost
    cout << dist[end.first][end.second] << endl;

    // Reconstruct and print the shortest path
    vector<pair<int, int>> path;
    pair<int, int> step = end;
    
    while (step != start) {
        path.push_back(step);
        step = parent[step.first][step.second];
    }
    path.push_back(start);

    // Reverse the path for correct order
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}

// Function to read input data and execute pathfinding
int main() {
    int tileCount;
    cin >> tileCount;
    
    unordered_map<char, int> tileCosts;
    for (int i = 0; i < tileCount; ++i) {
        char symbol;
        int cost;
        cin >> symbol >> cost;
        tileCosts[symbol] = cost;
    }

    int rows, cols;
    cin >> rows >> cols;

    vector<vector<char>> map(rows, vector<char>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            cin >> map[i][j];

    pair<int, int> start, end;
    cin >> start.first >> start.second >> end.first >> end.second;

    // Run Dijkstra’s algorithm
    dijkstra(map, tileCosts, start, end);

    return 0;
}


