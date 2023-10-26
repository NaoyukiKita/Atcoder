#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ull = unsigned long long int;

int main() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for (int& a : A) cin >> a;
    for (int& b : B) cin >> b;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ull cost = 0;
    for (int i = 0; i < N; i++) {
        cost += abs(A[i] - B[i]);
    }

    cout << cost << endl;
}