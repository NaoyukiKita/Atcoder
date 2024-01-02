#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

ll ABS(ll value) { return value > 0 ? value : -value; }

int main(void){
    ll N, Q, x, y, q;
    cin >> N >> Q;
    
    vector<ll> diffs(N), sums(N);
    ll max_diff = -2000000000, max_sum = -2000000000;
    ll min_diff = 2000000000, min_sum = 2000000000;
    
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        diffs[i] = x - y;
        if (diffs[i] > max_diff) max_diff = diffs[i];
        if (diffs[i] < min_diff) min_diff = diffs[i];
        
        sums[i] = x + y;
        if (sums[i] > max_sum) max_sum = sums[i];
        if (sums[i] < min_sum) min_sum = sums[i];
    }
    
    ll ans;
    for (int j = 0; j < Q; j++) {
        cin >> q; q--;
        ans = ABS(max_diff - diffs[q]);
        if (ans < ABS(min_diff - diffs[q])) ans = ABS(min_diff - diffs[q]);
        if (ans < ABS(max_sum - sums[q])) ans = ABS(max_sum - sums[q]);
        if (ans < ABS(min_sum - sums[q])) ans = ABS(min_sum - sums[q]);
        
        cout << ans << endl;
    }
}
