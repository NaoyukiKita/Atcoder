#include <iostream>
#include <vector>
#include <stack>
using namespace std;
using ll = long long int;

int main() {
    int N, S;
    cin >> N >> S;
    
    vector<vector <int> > prices(N+1, vector<int>(2));
    for (int n = 1; n <= N; n++) cin >> prices[n][0] >> prices[n][1];
    
    vector<vector <int> > dp(N+1, vector<int>(S+1, -1));
    dp[0][0] = 2;
    
    for (int n = 1; n <= N; n++) {
        for (int p = 0; p <= S; p++) {
            for (int t = 0; t < 2; t++) {
                if (p < prices[n][t]) continue;
                if (dp[n-1][p-prices[n][t]] == -1) continue;
                dp[n][p] = t;
            }
        }
    }
    
    if (dp[N][S] == -1) {
        cout << "Impossible\n";
        return 0;
    } else {
        stack<char> stk;
        int current = S, t;
        for (int n = N; n > 0; n--) {
            t = dp[n][current];
            stk.push(t ? 'B' : 'A');
            current -= prices[n][t];
        }
        
        while (!stk.empty()) {
            cout << stk.top(); stk.pop();
        }
        cout << endl;
    }
}
