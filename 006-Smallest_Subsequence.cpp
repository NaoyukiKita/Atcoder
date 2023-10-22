#include <iostream>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    int begin = 0, end, min_idx;
    char min_chr;
    for (int k = 0; k < K; k++) {
        end = N - K + k + 1;
        min_idx = 0;
        min_chr = 'z' + 1;
        for (int i = begin; i < end; i++) {
            if (min_chr <= S[i]) continue;
            min_idx = i;
            min_chr = S[i];
        }

        cout << min_chr;
        begin = min_idx + 1;
    }
    cout << endl;
}