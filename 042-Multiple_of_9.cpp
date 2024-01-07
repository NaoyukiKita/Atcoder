#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

const ll MOD = 1000000007;

int main() {
    int K;
    cin >> K;
    
    if (K % 9) {
        cout << 0 << endl;
        return 0;
    }
    
    vector<ll> dp(K + 1);
    dp[0] = 1;
    
    for (int i = 1; i <= K; i++) {
        for (int d = 1; d <= 9; d++) {
            if (i - d < 0) break;
            dp[i] += dp[i - d];
            dp[i] %= MOD;
        }
    }
    
    cout << dp[K] << endl;
}
