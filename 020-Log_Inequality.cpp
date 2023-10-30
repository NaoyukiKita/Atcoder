#include <iostream>
using namespace std;
using ull = unsigned long long int;

int main() {
    ull a, b, c;
    cin >> a >> b >> c;
    for (int i = 0; i < b; i++) {
        a /= c;
        if (a) continue;
        cout << "Yes\n";
        return 0;
    }
    cout << "No\n";
}