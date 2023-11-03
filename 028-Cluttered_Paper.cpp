#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

int main() {
    int N, lx, ly, rx, ry;
    vector<vector <ll> > grid(1002, vector<ll>(1002));

    cin >> N;
    for (int n = 0; n < N; n++) {
        cin >> lx >> ly >> rx >> ry;
        grid[lx][ly]++;
        grid[lx][ry]--;
        grid[rx][ly]--;
        grid[rx][ry]++;
    }

    for (int x = 0; x < 1002; x++) {
        for (int y = 1; y < 1002; y++) {
            grid[x][y] += grid[x][y - 1];
        }
    }

    for (int y = 0; y < 1002; y++) {
        for (int x = 1; x < 1002; x++) {
            grid[x][y] += grid[x - 1][y];
        }
    }

    vector<ll> counter(N + 1);
    for (int x = 0; x < 1002; x++) {
        for (int y = 0; y < 1002; y++) {
            if (grid[x][y] == 0) continue;
            counter[grid[x][y]]++;
        }
    }

    for (int n = 1; n <= N; n++) {
        cout << counter[n] << endl;
    }
}