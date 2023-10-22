#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, Q, b;

    cin >> N;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    sort(A.begin(), A.end());

    cin >> Q;
    while (Q--) {
        cin >> b;
        decltype(A)::iterator it = lower_bound(A.begin(), A.end(), b);
        int pos = (int)(distance(A.begin(), it));

        if (pos == 0) {
            cout << abs(A[pos] - b) << endl;
            continue;
        }    
        int left = abs(A[pos - 1] - b);
        int right = abs(A[pos] - b);

        cout << (left < right ? left : right) << endl;
    }
}