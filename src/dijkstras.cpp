// dijsktras.cpp

// Main Execution
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Structure representing a grid coordinate.
struct Point {
    int r, c;
};

// Node for the priority queue used by Dijkstra’s algorithm.
struct Node {
    int cost, r, c;
    // Priority is based on the current total cost.
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the number of tile types.
    int tiles_n;
    cin >> tiles_n;

    // Map from tile symbol to its cost.
    unordered_map<char, int> tileCost;
    for (int i = 0; i < tiles_n; i++) {
        char tile;
        int cost;
        cin >> tile >> cost;
        tileCost[tile] = cost;
    }

    // Read the dimensions of the grid map.
    int map_rows, map_cols;
    cin >> map_rows >> map_cols;
    vector<vector<char>> grid(map_rows, vector<char>(map_cols));
    for (int i = 0; i < map_rows; i++) {
        for (int j = 0; j < map_cols; j++) {
            cin >> grid[i][j];
        }
    }

    // Read the runner's starting and ending coordinates.
    int start_r, start_c, end_r, end_c;
    cin >> start_r >> start_c;
    cin >> end_r >> end_c;

    // Create a distance matrix; initialize all distances as "infinite".
    vector<vector<int>> dist(map_rows, vector<int>(map_cols, numeric_limits<int>::max()));
    // Parent matrix to reconstruct the path.
    vector<vector<Point>> parent(map_rows, vector<Point>(map_cols, {-1, -1}));

    // Priority queue to select the grid cell with the smallest cost.
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Start with the runner's starting location with a cost of zero.
    // Note: we add the starting tile’s cost only when leaving it.
    dist[start_r][start_c] = 0;
    pq.push({0, start_r, start_c});

    // Direction vectors for moving up, down, left, right.
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // If this node's cost does not match the minimal cost found, skip it.
        if (current.cost != dist[current.r][current.c])
            continue;

        // If we reached the destination, we can stop early.
        if (current.r == end_r && current.c == end_c)
            break;

        // Try all four adjacent moves.
        for (int k = 0; k < 4; k++) {
            int nr = current.r + dr[k];
            int nc = current.c + dc[k];

            // Check map boundaries.
            if (nr < 0 || nr >= map_rows || nc < 0 || nc >= map_cols)
                continue;

            // When moving from the current tile, add its leaving cost.
            int newCost = current.cost + tileCost[grid[current.r][current.c]];

            // Update if a lower cost path is found.
            if (newCost < dist[nr][nc]) {
                dist[nr][nc] = newCost;
                parent[nr][nc] = {current.r, current.c};
                pq.push({newCost, nr, nc});
            }
        }
    }

    // Reconstruct the path from destination back to the start.
    vector<Point> path;
    int cur_r = end_r, cur_c = end_c;
    while (!(cur_r == start_r && cur_c == start_c)) {
        path.push_back({cur_r, cur_c});
        Point par = parent[cur_r][cur_c];
        cur_r = par.r;
        cur_c = par.c;
    }
    // Add the starting coordinate.
    path.push_back({start_r, start_c});

    // Reverse the path to show it from the start to the destination.
    reverse(path.begin(), path.end());

    // Output: first the total cost, then each coordinate on a newline.
    cout << dist[end_r][end_c] << "\n";
    for (const auto &p : path) {
        cout << p.r << " " << p.c << "\n";
    }

    return 0;
}


