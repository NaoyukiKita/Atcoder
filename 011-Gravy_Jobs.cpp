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

    vector<Task> tasks(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> D >> C >> S;
        tasks[i] = initTask(D, C, S);
    }

    sort(tasks.begin(), tasks.end());

    int max_due = tasks[N].due;
    vector<vector <ull> > dp(N + 1, vector<ull>(max_due + 1));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= max_due; j++) {
            if (j < tasks[i].len || tasks[i].due < j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - tasks[i].len] + tasks[i].praise);
            }
        }
    }

    ull max_val = 0;
    for (int j = 0; j <= max_due; j++) max_val = max_val > dp[N][j] ? max_val : dp[N][j];
    cout << max_val << endl;
}