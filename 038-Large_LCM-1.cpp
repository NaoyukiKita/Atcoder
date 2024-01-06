#include <iostream>
using namespace std;
using ull = unsigned long long int;

const ull threthold = 1000000000000000000;

ull gcd(ull X, ull Y) {
    if (Y == 0) return X;
    return gcd(Y, X % Y);
}

int main() {
    ull A, B, tmp;
    cin >> A >> B;
    if (A < B) {
        tmp = A;
        A = B;
        B = tmp;
    }
    
    ull G = gcd(A, B);
    
    if (B / G > threthold / A + 1) cout << "Large\n";
    else {
        ull ans = (A / G) * B;
        if (ans > threthold) cout << "Large\n";
        else cout << ans << endl;
    }
    
}