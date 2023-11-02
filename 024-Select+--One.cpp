#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N), B(N);

    for (int& a : A) cin >> a;
    for (int& b : B) cin >> b;

    int counter = 0;
    for (int i = 0; i < N; i++) {
        counter += abs(A[i] - B[i]);
        if (counter <= K) continue;
        cout << "No\n";
        return 0;
    }

    if ((K - counter) % 2 == 0) cout << "Yes\n";
    else cout << "No\n";
}