#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double PI = acos(-1);

struct Point {
    double x, y;
};

int main() {
    int N, x, y;
    cin >> N;
    vector<Point> points(N);

    for (int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;
    
    double slope, theta, left, right, current, max_val = 0.0;
    vector<double> thetas(N);
    for (int j = 0; j < N; j++) {
        // P_jからP_uへのベクトルとx軸とのなす角(0 ~ 2 * PI)を計算する
        thetas[j] = -1.0; // j != u
        for (int u = 0; u < N; u++) {
            if (u == j) continue;
            // 傾きが無限大あるいは無限小の場合
            if (points[u].x == points[j].x) {
                // PI / 2 か 3 * PI / 2かをy座標の比較により算出
                thetas[u] = PI / 2 + PI * (points[u].y < points[j].y);
                continue;
            }

            // 傾きが有限の場合
            slope = (points[u].y - points[j].y) / (points[u].x - points[j].x);
            theta = atan(slope); // -PI / 2 ~ PI / 2

            // 0 ~ 2 * PIに調整
            if (points[u].x < points[j].x) theta += PI;
            if (theta < 0) theta += 2 * PI;

            // 記録
            thetas[u] = theta;
        }

        // sort
        sort(thetas.begin(), thetas.end());

        // 偏角の差がPIに近いペアを探索し、その差の最大値をmax_valに保存
        for (int v = 0; v < N; v++) {
            if (thetas[v] < 0) continue; // P_jと現在のthetas[v]が指し示す頂点が同じ

            // thetas[v] + PI 以上の最小偏角を探索
            decltype(thetas)::iterator it = lower_bound(thetas.begin(), thetas.end(), thetas[v] + PI);

            if (it == thetas.end()) { // なかった場合
                current = thetas[N - 1] - thetas[v]; // 最大の偏角で代用
                if (current > max_val) max_val = current; // 更新
                break; // thetas[v]は単調増加するためこれ以上の探索は無駄
            }
            left = *(it - 1) - thetas[v]; // thetas[v] + PI 未満の最大偏角とthetas[v]との差
            right = 2 * PI - (*it - thetas[v]); // thetas[v] + PI以上の最小偏角とthetas[v]との差(PI以上のため2 * PIから引く)
            
            current = left > right ? left : right; // 大きい方を選択

            if (current > max_val) max_val = current; // 更新
        }

    }

    cout << setprecision(10);
    cout << (max_val * 180 / PI) << endl;
}