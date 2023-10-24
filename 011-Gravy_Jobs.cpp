#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ull = unsigned long long int;

struct Task {
    int due, len, praise;

    bool operator<( const Task& right ) const {
        return due == right.due ? len < right.len : due < right.due;
    }
};

Task initTask(int due, int len, int praise) {
    Task task;
    task.due = due;
    task.len = len;
    task.praise = praise;

    return task;
}

int main() {
    int N, D, C, S;
    cin >> N;

    vector<Task> tasks(N);
    int max_len = 0;
    for (int i = 0; i < N; i++) {
        cin >> D >> C >> S;
        tasks[i] = initTask(D, C, S);
        if (D <= max_len) continue;
        max_len = D;
    }

    sort(tasks.begin(), tasks.end());

    vector<vector <ull> > dp(N + 1, vector<ull>(max_len + 1));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < max_len; j++) {
            if (j + tasks[i].len > tasks[i].due) break;
            dp[i + 1][j + tasks[i].len] += dp[i][j] + tasks[i].praise;
        }
    }

    cout << dp[N][max_len] << endl;

    // cout << "-----------------\n";
    // for (int i = 0; i <= N; i++) {
    //     for (int j = 0; j <= max_len; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
}