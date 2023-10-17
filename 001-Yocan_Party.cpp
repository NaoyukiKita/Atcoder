#include <iostream>
#include <vector>
using namespace std;

bool check(vector<int> &pieces, int len, int target) {
    int cnt = 0, current = 0;
    for (int piece : pieces) {
        current += piece;
        if (current < len) continue;
        
        cnt++;
        current = 0;
    }

    return cnt >= target;
}

int main(void){
   int N, L, K;
   cin >> N >> L >> K;
    
    vector<int> A(N), pieces(N+1);
    for (int& a : A) cin >> a;
    
    for (int i = 0; i < N; i++) {
        pieces[i] = A[i];
        if(i) pieces[i] -= A[i - 1];
    }
    pieces[N] = L - A[N - 1];
    
    int left = 1, right = L, mid = -1, prev;
    while (left < right) {
        prev = mid;
        mid = (left + right) / 2;
        if (prev == mid) break;
        
        if (check(pieces, mid, K+1)) { left = mid; }
        else { right = mid - 1; }
    }
    
    cout << (check(pieces, right, K+1) ? right : mid) << endl;
}
