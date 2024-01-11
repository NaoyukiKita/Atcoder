#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

const ll MOD = 1000000007;

int main() {
    int N, a;
    cin >> N;
    
    vector<ll> sums(N);
    for (int n = 0; n < N; n++) {
        for (int j = 0; j < 6; j++) {
            cin >> a;
            sums[n] += a;
        }
    }
    
    
    ll ans = 1;
    for (int n = 0; n < N; n++) {
        ans = (ans * sums[n]) % MOD;
    }
    
    cout << ans << endl;
}
