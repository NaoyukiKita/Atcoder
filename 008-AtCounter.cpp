#include <iostream>
#include <vector>
using namespace std;

int MOD = 1000000007;

int main() {
    int M = 7;
    string A = "atcoder";

    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<vector <int> > dp(M + 1, vector<int>(N + 1));
    for (int j = 0; j <= N; j++) dp[0][j] = 1;

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            dp[i][j] = dp[i][j - 1];
            if (S[j - 1] == A[i - 1]) dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] %= MOD;
        }
    }

    cout << dp[M][N] << endl;
}