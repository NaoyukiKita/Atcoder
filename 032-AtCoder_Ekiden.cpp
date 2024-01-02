#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void){
    int N, M, x, y;
    cin >> N;
    
    vector<vector <int> > A(N, vector<int>(N));
    vector<vector <bool> > bad(N, vector<bool>(N));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }
    
    cin >> M;
    for (int m = 0; m < M; m++) {
        cin >> x >> y;
        bad[x - 1][y - 1] = true;
        bad[y - 1][x - 1] = true;
    }
    
    vector<int> order(N);
    for (int i = 0; i < N; i++) order[i] = i;
    
    int min_value = 1000000, current;
    bool flag;
    do {
        flag = true;
        for (int i = 0; i < N - 1; i++) {
            if (!bad[order[i]][order[i + 1]]) continue;
            flag = false;
            break;
        }
        if (!flag) continue;
        
        current = 0;
        for (int i = 0; i < N; i++) current += A[order[i]][i];
        
        if (current >= min_value) continue;
        min_value = current;
    } while (next_permutation(order.begin(), order.end()));
    
    int ans = min_value == 1000000 ? -1 : min_value;
    cout << ans << endl;
}
