#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

ll func(vector<int>& A, int begin, ll current, int counter, int target, int mod) {
    if (counter == 0) return current == target;
    
    ll sum = 0;
    for (int i = begin; i < A.size(); i++) {
        sum += func(A, i+1, (current*A[i]) % mod, counter-1, target, mod);
    }
    
    return sum;
}

int main() {
    int N, P, Q;
    cin >> N >> P >> Q;
    
    vector<int> A(N);
    for (int& a : A) cin >> a;
    
    cout << func(A, 0, 1, 5, Q, P) << endl;
}
