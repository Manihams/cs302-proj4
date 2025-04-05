/* Lab Name: Path Finding
 * Names: Pravin Adithya Srinivasan, Manihams Suraparaju
 * Resources: Lecture notes, youtube video, geeksforgeeks, github
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./generate_map N\n";
        return 1;
    }

	// map size (n*n)
    int mapSize = stoi(argv[1]);
    srand(time(0));

    // Initialized the tile types and costs
    vector<pair<char, int>> tileCost = {
        {'f', 3}, {'g', 1}, {'G', 2},
        {'h', 4}, {'m', 7}, {'r', 5}
    };

    // Outputs each map and its cost
    cout << tiles.size() << endl;
    for (auto& t : tiles) {
        cout << t.first << " " << t.second << endl;
    }

    // Output map dimensions getting rows and columns
    cout << N << " " << N << endl;

    // Calculates and prints the map grid with random tiles
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int idx = rand() % tiles.size();
            cout << tiles[idx].first;
            if (j != N - 1) cout << " ";
        }
        cout << endl;
    }

    // Output start and end positions from top-left to bottom right
    cout << "0 0" << endl;
    cout << N-1 << " " << N-1 << endl;

    return 0;
}

