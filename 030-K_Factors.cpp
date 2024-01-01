#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> counter(N + 1);
    
    for (int i = 2; i <= N; i++) {
        if (counter[i] != 0) continue;
        for (int j = i; j <= N; j += i) counter[j]++;
    }
    
    int ans = 0;
    for (int i = 2; i <= N; i++) {
        if (counter[i] < K) continue;
        ans++;
    }
    
    cout << ans << endl;
}