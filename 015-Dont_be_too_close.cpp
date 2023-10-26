#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ull = unsigned long long int;

const int MOD = 1000000007; // prime number

ull fastPow(int a, int p) {
    // returns a^{p} mod `MOD`
    int len = ceil(log2((double)(p)));

    vector<ull> doubling(len + 1);
    // doubling[i] = a^{2^{i}} mod `MOD`
    doubling[0] = a;
    for (int i = 1; i <= len; i++) {
        doubling[i] = doubling[i - 1] * doubling[i - 1];
        doubling[i] %= MOD;
    }

    ull ans = 1;
    for (int i = 0; i <= len; i++) {
        if (!(p & 1 << i)) continue;
        ans = (ans * doubling[i]) % MOD;
    }

    return ans;
}

void calcMods(vector<ull>& mods, int N) {
    // mods[i] = i! % MOD; for each i = 0, ..., N
    if (mods.size() != N + 1) {
        cout << "size unmatch: expected " << N + 1 << ", got" << mods.size() << endl;
    }

    mods[0] = 1;
    for (int i = 1; i <= N; i++) {
        mods[i] = (mods[i - 1] * i) % MOD;
    }
}

void calcInvMods(vector<ull>& inv_mods, vector<ull>& mods, int N) {
    // inv_mods[i] = (i!)^{-1} % MOD; for each i = 0, ..., N
    // mods[i] = i! % MOD; for each i = 0, ..., N
    if (inv_mods.size() != N + 1) {
        cout << "size unmatch: expected " << N + 1 << ", got" << inv_mods.size() << endl;
    }

    // Fermat's little theorem: (N!)^{-1} = (N!)^{M - 2} mod `MOD` if `MOD` is a prime number and bigger than 2.
    inv_mods[N] = fastPow(mods[N], MOD - 2);
    // (i!)^{-1} = ((i + 1)!)^{-1} * (i + 1)
    for (int i = N - 1; i >= 0; i--) {
        inv_mods[i] = (inv_mods[i + 1] * (i + 1)) % MOD;
    }
}

int comb(int a, int b, vector<ull>& mods, vector<ull>& inv_mods) {
    // returns a C b = a! * (b!)^{-1} * ((a - b)!)^{-1} mod `MOD`
    // requires a <= N, b <= N
    ull ans = mods[a];
    ans = (ans * inv_mods[b]) % MOD;
    ans = (ans * inv_mods[a - b]) % MOD;

    return int(ans);
}

int f(int N, int k, int a, vector<ull>& mods, vector<ull>& inv_mods) {
    // N個のボールを差がk以上になるようにa個選ぶ関数
    return comb((N - (k - 1) * (a - 1)), a, mods, inv_mods);
}

int g(int N, int k, vector<ull>& mods, vector<ull>& inv_mods) {
    // N個のボールを差がk以上になるように選ぶ関数
    int max_a = (N - 1) / k + 1; // 取りうるaの最大値
    int ans = 0;
    for (int a = 1; a <= max_a; a++) {
        ans += f(N, k, a, mods, inv_mods);
        ans %= MOD;
    }

    return ans;
}

int main() {
    int N;
    cin >> N;
    
    vector<ull> mods(N + 1), inv_mods(N + 1);
    calcMods(mods, N);
    calcInvMods(inv_mods, mods, N);
    
    for (int k = 1; k <= N; k++) {
        cout <<  g(N, k, mods, inv_mods) << endl;
    }
}