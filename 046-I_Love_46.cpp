#include <iostream>
using namespace std;
using ll = long long int;

int main() {
    int N, value;
    ll counter[3][46];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 46; j++) {
            counter[i][j] = 0;
        }
    }
    
    cin >> N;
    for (int i = 0; i < 3; i++) {
        for (int n = 0; n < N; n++) {
            cin >> value;
            counter[i][value % 46]++;
        }
    }
    
    ll sum = 0;
    for (int p = 0; p < 46; p++) {
        for (int q = 0; q < 46; q++) {
            int r = 46 - ((p + q) % 46);
            if (r == 46) r = 0;
            
            sum += counter[0][p] * counter[1][q] * counter[2][r];
        }
    }
    
    cout << sum << endl;
}
