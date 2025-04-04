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

    int N = stoi(argv[1]);
    srand(time(0));

    // Define tile types and costs
    vector<pair<char, int>> tiles = {
        {'f', 3}, {'g', 1}, {'G', 2},
        {'h', 4}, {'m', 7}, {'r', 5}
    };

    // Output tile definitions
    cout << tiles.size() << endl;
    for (auto& t : tiles) {
        cout << t.first << " " << t.second << endl;
    }

    // Output map dimensions
    cout << N << " " << N << endl;

    // Generate and output map
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int idx = rand() % tiles.size();
            cout << tiles[idx].first;
            if (j != N - 1) cout << " ";
        }
        cout << endl;
    }

    // Output start (0, 0) and end (N-1, N-1)
    cout << "0 0" << endl;
    cout << N-1 << " " << N-1 << endl;

    return 0;
}

