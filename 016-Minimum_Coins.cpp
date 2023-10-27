#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int p, int q) {
    if (q == 0) return p;
    return gcd(q, (p % q));
}

int main() {
    int N;
    vector<int> coins(3);
    cin >> N >> coins[0] >> coins[1] >> coins[2];

    sort(coins.rbegin(), coins.rend());

    int min_val = 9999, g = gcd(coins[1], coins[2]), current[2];
    for (int i = N / coins[0]; i >= 0; i--) {
        current[0] = N - coins[0] * i;
        if (current[0] % g) continue;
        for (int j = current[0] / coins[1]; j >= 0; j--) {
            current[1] = current[0] - coins[1] * j;
            if (current[1] % coins[2]) continue;
            if (i + j + (current[1] / coins[2]) < min_val) min_val = i + j + (current[1] / coins[2]);
            break;
        }
    }

    cout << min_val << endl;
}