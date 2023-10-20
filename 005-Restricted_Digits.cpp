#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, B, K;
    cin >> N >> B >> K;

    vector<int> C(K);
    for (int& c : C) cin >> c;

    int len = ceil(log2((double)(N)));
}