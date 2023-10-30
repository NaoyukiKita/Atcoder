#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long int;

int main() {
    int N;
    cin >> N;
    vector<int> A(2 * N + 1);
    vector<vector <ll> > dp(2 * N + 1, vector<ll>(2 * N + 1));

    for (int i = 1; i <= 2 * N; i++) cin >> A[i];

    for (int i = 1; i < 2 * N; i++) {
        dp[i][i + 1] = abs(A[i] - A[i + 1]);
    }

    for (int h = 3; h < 2 * N; h += 2) {
        for (int i = 1; i + h <= 2 * N; i++) {
            // calc dp[i][i + h]
            dp[i][i + h] = dp[i + 1][i + h - 1] + abs(A[i] - A[i + h]);

            for (int k = i + 1; k + 1 < i + h; k += 2) {
                if (dp[i][k] + dp[k + 1][i + h] > dp[i][i + h]) continue;
                dp[i][i + h] = dp[i][k] + dp[k + 1][i + h];
            }
        }
    }

    cout << dp[1][2 * N] << endl;
}