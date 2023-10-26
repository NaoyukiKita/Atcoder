#include <iostream>
#include <stack>
using namespace std;

const int MOD = 1000000007; // prime number

int fastPow(int a, int p) {
    // returns a^{p} mod `MOD`

    int len, current = p;
    for (len = 0; current != 1; len++) current /= 2;

    cout << "len = " << len << endl;
    return 0;
}

void calcMods(vector<int>& res, int N) {
    // res[i] = i! % MOD; for each i = 0, ..., N
    if (res.size() != N + 1) {
        cout << "size unmatch: expected " << N + 1 << ", got" << res.size() << endl;
    }

    res[0] = 1;
    for (int i = 1; i <= N; i++) {
        res[i] = (res[i - 1] * i) % MOD;
    }
}

void calcInvMods(vector<int>& res, int N) {
    // res[i] = (i!)^{-1} % MOD; for each i = 0, ..., N
    if (res.size() != N + 1) {
        cout << "size unmatch: expected " << N + 1 << ", got" << res.size() << endl;
    }

    // Fermat's little theorem: a^{-1} = a^{M - 2} mod M

}

int main() {
    
    fastPow(2, 5);
}