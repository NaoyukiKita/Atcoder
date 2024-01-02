#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    
    vector<int> A(N);
    for (int& a : A) cin >> a;
    
    map<int, int> counter;
    int n_kinds = 0, begin = 0, end = 0, max_len = 0, cur_len = 0;
    
    while (begin < N && end < N) {
        if (counter[A[end]] == 0 && n_kinds == K) {
            if (cur_len > max_len) max_len = cur_len;
            while (n_kinds == K) {
                begin++;
                cur_len--;
                counter[A[begin - 1]]--;
                if (counter[A[begin - 1]] == 0) n_kinds--;
            }
        }
        
        if (counter[A[end]] == 0) n_kinds++;
        counter[A[end++]]++;
        cur_len++;
    }
    if (cur_len > max_len) max_len = cur_len;
    
    cout << max_len << endl;
}