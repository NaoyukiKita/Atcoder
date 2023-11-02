#include <iostream>
#include <vector>
using namespace std;
using ull = unsigned long long int;

const ull mod = 1000000007;

int main() {
    int H, W;
    cin >> H >> W;
    vector<char> grid(H * W + 1);

    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) {
            cin >> grid[h * w + 1];
        }
    }

    vector<vector <ull> > dp((H * W + 1), vector<ull>(1 << (W + 1)));
    dp[0][0] = 1;

    for (int i = 0; i < H * W; i++) {
        for (int j = 0; j < (1 << (W + 1)); j++) {
            dp[i + 1][j / 2] += dp[i][j];
            if (!(j & (1 << (max(0. i - 2))))) continue;
            if (grid[i] != '.') continue;
            dp[i + 1][]
        }
    }
}