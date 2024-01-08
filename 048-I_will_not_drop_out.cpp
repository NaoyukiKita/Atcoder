#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long int;

int main() {
    ll N, K, A, B;
    cin >> N >> K;
    
    vector<ll> vec(2 * N);
    
    for (int n = 0; n < N; n++) {
        cin >> A >> B;
        vec[2 * n] = B;
        vec[2 * n + 1] = A - B;
    }
    
    sort(vec.rbegin(), vec.rend());
    
    ll sum = 0;
    for (int k = 0; k < K; k++) {
        sum += vec[k];
    }
    
    cout << sum << endl;
}
