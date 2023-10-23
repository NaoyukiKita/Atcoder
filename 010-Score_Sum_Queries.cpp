#include <iostream>
#include <vector>
using namespace std;
using ull = unsigned long long int;

int main() {
    int N, C, P, Q, L, R;
    cin >> N;
    vector<vector <ull> > psum(2, vector<ull>(N + 1));

    for (int i = 1; i <= N; i++) {
        cin >> C >> P;
        psum[C - 1][i] = P;

        psum[0][i] += psum[0][i - 1];
        psum[1][i] += psum[1][i - 1];
    }

    cin >> Q;
    for (int j = 0; j < Q; j++) {
        cin >> L >> R;
        cout << (psum[0][R] - psum[0][L - 1]) << ' ';
        cout << (psum[1][R] - psum[1][L - 1]) << endl;
    }
}