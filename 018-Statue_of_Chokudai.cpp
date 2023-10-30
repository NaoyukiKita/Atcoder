#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI = acos(-1);

int main() {
    double T, L, X, Y, E;
    int Q;
    cin >> T >> L >> X >> Y >> Q;
    cout << setprecision(10);

    // point of statue
    double sx = X, sy = Y, sz = 0;

    double theta, px, py, pz, inner;
    double ux, uy, uz, unorm;
    double vx, vy, vz, vnorm;
    double cos_alpha, alpha;
    while (Q--) {
        cin >> E;

        theta = 2 * PI * E / T;

        // point of view
        px = 0;
        py = (L / 2) * (-sin(theta));
        pz = (L / 2) * (1 - cos(theta));

        // vectors
        ux = sx - px;
        uy = sy - py;
        uz = sz - pz;
        unorm = sqrt(ux * ux + uy * uy + uz * uz);

        vx = ux;
        vy = uy;
        vz = 0;
        vnorm = sqrt(vx * vx + vy * vy + vz * vz);

        // inner
        inner = ux * vx + uy * vy + uz * vz;

        // cos(alpha)
        cos_alpha = inner / (unorm * vnorm);

        // alpha
        alpha = acos(cos_alpha);

        cout << (alpha * 360 / (2 * PI)) << endl;
    }
}