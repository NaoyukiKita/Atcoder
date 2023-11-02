#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;
using ull = unsigned long long int;

const ll mod = 1000000007;

bool judge(ll i, ll j, int W, vector<char>& grid) {
    // cout << i << ", " << j << ", " << W << ", grid\n";
    bool A, B;

    // 範囲外、あるいは黒の座標に駒が置かれている
    for (ll k = i - W - 1; k < i; k++) {
        A = j & (1 << (k - (i - W - 1)));
        if (k <= 0 && A) return false;
        if (k > 0 && A && grid[k] == '#') return false;
        // cout << "\tk = " << k << " A = " << A << " grid[" << k << "] = " << int(grid[k]) << endl;
    }
    // cout << "\t範囲外、あるいは黒の座標に駒が置かれている OK\n";

    // 駒が横方向に連続して置かれている(範囲外の座標は考慮しない)
    for (ll k = max(1LL, i - W - 1); k < i - 1; k++) {
        if (k % W == 0) continue; // 右端と次の行の左端なので違反しない
        A = j & (1 << (k - (i - W - 1)));
        B = j & (1 << (k - (i - W - 2))); // 右隣の状態
        if (A && B) return false;
    }
    // cout << "\t駒が横方向に連続して置かれている OK\n";

    // 駒が縦方向に連続して置かれている
    if (i - W - 1 > 0) {
        A = j & 1;
        B = j & (1 << (W));
        if (A && B) return false;
    }
    // cout << "\t駒が縦方向に連続して置かれている OK\n";

    // 駒が斜め方向(W - 1, W + 1マス先の座標)に連続して置かれている
    for (ll k = max(1LL, i - W - 1); k < i; k++) {
        // 左斜め下
        if (k % W == 1) continue; // 同じ行の左端と右端の場合は違反しない
        if (k + W - 1 >= i) break;
        A = j & (1 << (k - (i - W - 1)));
        B = j & (1 << (k + W - 1 - (i - W - 1)));
        if (A & B) return false;

        // // 右斜め下
        // if (k + W + 1 >= i - 1) continue;
        // B = j & (1 << (k + W + 1 - (i - W - 1)));
        // if (A & B) return false;
    }
    // cout << "\t駒が斜め方向に連続して置かれている OK\n";

    return true;
}

int main() {
    ll H, W;
    cin >> H >> W;
    vector<char> grid(H * W + 1);

    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) {
            cin >> grid[W * h + w + 1];
        }
    }

    vector<vector <ll> > dp((H * W + 2), vector<ll>(1 << (W + 1)));
    dp[1][0] = 1;

    for (ll i = 2; i <= H * W + 1; i++) {
        for (ll j = 0; j < (1 << (W + 1)); j++) {
            // judge j is possible
            if (!judge(i, j, W, grid)) continue;
            // calc dp[i][j]
            ll m = min((ll)(W + 1), i - 1);

            // i - W - 2マス目に置かない場合の場合の数を加算
            dp[i][j] += dp[i - 1][(j << 1) & ((1 << m) - 1)];

            // i - W - 2マス目に置く場合の場合の数を加算
            // 但し、i - W - 2マス目の右斜め下がi - 1マス目の時かつ
            // i - 1マス目に置く場合を除く
            if ((i - 1) % W == 1 || j < (1 << W)) {
                dp[i][j] %= mod;
                dp[i][j] += dp[i - 1][((j << 1) + 1) & ((1 << m) - 1)];
            }

            dp[i][j] %= mod;
        }
    }

    ull ans = 0;
    for (ll j = 0; j < (1 << (W + 1)); j++) {
        ans += dp[H * W + 1][j];
    }
    cout << ans << endl;

    // for (int i = 1; i <= H * W + 1; i++) {
    //     cout << i << ":\t";
    //     for (ll j = 0; j < (1 << (W + 1)); j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}