#include <iostream>
#include <vector>
using ull = unsigned long long int;
using namespace std;

void int2arr(ull i, vector<bool>& arr, int N) {
    for (int n = N - 1; n >= 0; n--) {
        arr[n] = i % 2;
        i /= 2;
    }
}

bool check(vector<bool>& arr, int N) {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        cnt += (arr[i] ? -1 : 1);
        
        if (cnt < 0) return false;
    }
    
    return cnt == 0;
}

void printArr(vector<bool>& arr, int N) {
    for (int i = 0; i < N; i++) {
        cout << (arr[i] ? ')' : '(');
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;
    if (N % 2) return 0;
    vector<bool> arr(N);
    
    for (ull i = (1 << (N / 2)) - 1 ; i < (1 << N); i += 2) {
        int2arr(i, arr, N);
        if (!check(arr, N)) continue;

        printArr(arr, N);
    }
}