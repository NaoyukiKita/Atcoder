#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

const ll MOD = 1000000007;

int main() {
    int N, L;
    cin >> N >> L;
    
    vector<ll> dp(N + 1);
    dp[0] = 1;
    
    for (int step = 1; step <= N; step++) {
        dp[step] = dp[step - 1];
        if (step < L) continue;
        dp[step] += dp[step - L];
        dp[step] %= MOD;
    }
    
    cout << dp[N] << endl;
}
