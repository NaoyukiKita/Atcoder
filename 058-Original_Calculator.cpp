#include<iostream>
#include<map>
using namespace std;
using ll = long long int;

int ketasum(int a){
    int sum = a;
    for (; a; a /= 10) sum += a % 10;
    return sum % 100000;
}

int main(){
    int N;
    ll K;
    cin >> N >> K;
    
    map<int, ll> memo;
    ll cycle = 0;
    
    for (ll count = 0; count < K; count++) {
        if (memo[N] != 0) {
            cycle = count - memo[N];
            K = (K - memo[N]) % cycle + count;
            for (; count < K; count++) {
                N = ketasum(N);
            }
            break;
        }
        memo[N] = count;
        N = ketasum(N);
    }

    // the loop below seems to have somthing wrong. idk why.
    // bool first = true;
    // for (ll count = 0; count < K; count++) {
    //     if (first && memo[N] != 0) {
    //         cycle = count - memo[N];
    //         K = (K - memo[N]) % cycle + count;
    //         first = false;
    //     } else if (first) memo[N] = count;
    //     N = ketasum(N);
    // }
    
    cout << N << endl;
}