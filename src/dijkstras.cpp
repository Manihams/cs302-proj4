#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

//struct for a grid of rows and columns
struct Point{
    int r, c;
};

//node for the priority queue
struct Node{
    int cost, r, c;
    //priority is based on the current total cost
    bool operator>(const Node &other) const{
        return cost > other.cost;
    }
};

//Main Execution
int main(int argc, char** argv){
    //Read the number of tile types.
    int tiles_n;
    cin >> tiles_n;


    unordered_map<char, int> tileCost;

    for(int i = 0; i < tiles_n; i++){
        char tile;
        int cost;
        cin >> tile >> cost;
        tileCost[tile] = cost;
    }

    //reading in the dimensions of the map
    int map_rows, map_cols;

    cin >> map_rows >> map_cols;

    vector<vector<char>> grid(map_rows, vector<char>(map_cols));

    for(int i = 0; i < map_rows; i++){
        for(int j = 0; j < map_cols; j++){
            cin >> grid[i][j];
        }
    }

    //reading the runner's starting and ending coordinates
    int start_r, start_c, end_r, end_c;

    cin >> start_r >> start_c;
    cin >> end_r >> end_c;

    //creating a distance matrix and initializing all distances as infinite
    vector<vector<int>> dist(map_rows, vector<int>(map_cols, 1000000000));
    //the parent matrix to reconstruct the path
    vector<vector<Point>> parent(map_rows, vector<Point>(map_cols, {-1, -1}));

    //priority queue to select the grid cell with the smallest cost
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    //starting with the runner's starting location with a cost of zero
    dist[start_r][start_c] = 0;
    pq.push({0, start_r, start_c});

    //the direction vectors for moving around
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};


    while(!pq.empty()){
        //getting smallest cost from queue
        Node current = pq.top();
        //removing the node from the queue
        pq.pop();

        //seeing if the node is outdated
        if(current.cost != dist[current.r][current.c]) continue;

        //exiting if we found shortest path
        if(current.r == end_r && current.c == end_c) break;

        //for loop to check all four directions
        for(int k = 0; k < 4; k++){

            //calculating new row and column based on direction
            int nr = current.r + dr[k];
            int nc = current.c + dc[k];

            //skipping if new position is not in map
            if(nr < 0 || nr >= map_rows || nc < 0 || nc >= map_cols) continue;

            //calculating new cost to move to neighbor cell
            int newCost = current.cost + tileCost[grid[current.r][current.c]];

            //seeing if new cost is lower than previous cost
            if(newCost < dist[nr][nc]){

                dist[nr][nc] = newCost;

                //setting current node as parent of neighbor cell
                parent[nr][nc] = {current.r, current.c};
                //adding new node to queue with new cost
                pq.push({newCost, nr, nc});
            }
        }
    }

    //reconstructing the path from destination back to the start
    vector<Point> path;

    int cur_r = end_r, cur_c = end_c;
    //looping till we reach starting position
    while(!(cur_r == start_r && cur_c == start_c)){
        //adding the current position to path
        path.push_back({cur_r, cur_c});
        //getting the parent
        Point par = parent[cur_r][cur_c];
        //moving to previous row/column
        cur_r = par.r;
        cur_c = par.c;
    }
    //adding start position to path
    path.push_back({start_r, start_c});
    //reversing the path
    reverse(path.begin(), path.end());

    cout << dist[end_r][end_c] << "\n";

    for(const auto &p : path){
        cout << p.r << " " << p.c << "\n";
    }

    return 0;
}
