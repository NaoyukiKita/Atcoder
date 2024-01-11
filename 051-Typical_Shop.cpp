#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long int;

void bitFullSearch(vector<vector <ll> >& memo, vector<ll>& list, int max_items, ll max_price) {
    int n_items;
    ll sum_price;
    for (int b = 0; b < (1 << list.size()); b++) {
        n_items = 0;
        sum_price = 0;
        for (int d = 0; d < list.size(); d++) {
            if (!(b & (1 << d))) continue;
            n_items++;
            sum_price += list[d];
            if (n_items > max_items || sum_price > max_price) break;
        }
        if (n_items > max_items || sum_price > max_price) continue;
        memo[n_items].push_back(sum_price);
    }
    
    for (n_items = 0; n_items <= max_items; n_items++) {
        sort(memo[n_items].begin(), memo[n_items].end());
    }
}

int main() {
    int N, K;
    ll P;
    
    cin >> N >> K >> P;
    
    vector<ll> left(N / 2), right(N - (N / 2));
    for (ll& l : left) cin >> l; 
    for (ll& r : right) cin >> r;
    
    vector<vector <ll> > left_memo(K + 1, vector<ll>());
    bitFullSearch(left_memo, left, K, P);
    vector<vector <ll> > right_memo(K + 1, vector<ll>());
    bitFullSearch(right_memo, right, K, P);
    
    ll ans = 0;
    for (int left_items = 0; left_items <= K; left_items++) {
        int right_items = K - left_items;
        
        for (ll left_sum : left_memo[left_items]) {
            ll max_right_sum = P - left_sum;
            
            auto it = upper_bound(right_memo[right_items].begin(),
                                right_memo[right_items].end(),
                                max_right_sum);
            
            ans += distance(right_memo[right_items].begin(), it);
        }
    }
    
    cout << ans << endl;
}
