#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll MOD = 1000000007;
int len = 62;

vector<ll> func(vector<ll>& dpi, vector<ll>& dpj, int tj, int B) {
    vector<ll> res(B);
    for (int p = 0; p < B; p++) {
        for (int q = 0; q < B; q++) {
            res[(p * tj + q) % B] += dpi[p] * dpj[q];
            res[(p * tj + q) % B] %= MOD;
        }
    }

    return res;
}

int main() {
    ll N, B, K;
    cin >> N >> B >> K;

    vector<int> C(K);
    for (int& c : C) cin >> c;

    // ten[i] = 10^(2^i) % B
    vector<ll> ten(len, 10);
    for (int i = 1; i < len; i++) ten[i] = (ten[i - 1] * ten[i - 1]) % B;

    // dp[i][j] = K種類の数字のみを用いた(2^i)桁の整数であって、Bで割った余りがjであるようなものの個数
    vector<vector <ll> > dp(len, vector<ll>(B));

    // initialize
    for (int k = 0; k < K; k++) dp[0][C[k] % B] += 1;

    // doubling
    for (int i = 1; i < len; i++) dp[i] = func(dp[i - 1], dp[i - 1], ten[i - 1], B);

    // res[j] = K種類の数字のみを用いたN桁の整数であって、Bで割った余りがjであるようなものの個数
    vector<ll> res(B);
    res[0] = 1;
    for (int i = 0; i < len; i++) {
        if (!(N & (1LL << i))) continue;
        res = func(res, dp[i], ten[i], B);
    }

    cout << res[0] << endl;
}