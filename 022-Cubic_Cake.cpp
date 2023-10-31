#include <iostream>
using namespace std;
using ull = unsigned long long int;

ull gcd(ull x, ull y) {
    if (y == 0) return x;
    return gcd(y, (x % y));
}

int main() {
    ull A, B, C;
    cin >> A >> B >> C;

    ull g = gcd(gcd(A, B), C);

    ull ans = (A / g) + (B / g) + (C / g) - 3;

    cout << ans << endl;
}