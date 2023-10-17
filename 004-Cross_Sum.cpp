#include <iostream>
#include <vector>
using namespace std;

int main() {
    int H, W;
    cin >> H >> W;
    
    vector<vector <int>> A(H + 1, vector<int>(W + 1));
    
    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) cin >> A[h][w];
    }
    
    int sum;
    for (int h = 0; h < H; h++) {
        sum = 0;
        for (int w = 0; w < W; w++) sum += A[h][w];
        A[h][W] = sum;
    }
    
    for (int w = 0; w < W; w++) {
        sum = 0;
        for (int h = 0; h < H; h++) sum += A[h][w];
        A[H][w] = sum;
    }
    
    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) cout << (A[H][w] + A[h][W] - A[h][w]) << " \n"[w == W - 1];
    }
}