// stupid solution: use array to express integer
// bool[128] can express 0 ~ 340282366920938463463374607431768211455(2^128 - 1)

#include <iostream>
using namespace std;
using ull = unsigned long long int;

const int MAX_DIGIT = 128;

ull gcd(ull X, ull Y) {
    if (Y == 0) return X;
    return gcd(Y, X % Y);
}

void cast(ull value, bool arr[]) {
    for (int d = 0; d < MAX_DIGIT; d++) {
        arr[d] = (value % 2 == 1);
        value /= 2;
        // if (value == 0) break;
        // cout << arr[d] << " \n"[d == MAX_DIGIT - 1];
    }
}

void inv_cast(ull& value, bool arr[]) {
    value = 0;
    ull c = 1;
    for (int d = 0; d < MAX_DIGIT; d++) {
        value += c * arr[d];
        c *= 2;
    }
}

bool bigger(bool left[], bool right[]) {
    for (int d = MAX_DIGIT - 1; d >= 0; d--) {
        if (left[d] == right[d]) continue;
        return left[d];
    }
    return false;
}

void mult(bool left[], bool right[], bool res[]) {
    bool c, d;
    for (int rd = 0; rd < MAX_DIGIT; rd++) {
        if (!right[rd]) continue;
        for (int ld = 0; ld < MAX_DIGIT; ld++) {
            if (ld + rd == MAX_DIGIT) break; // overflow
            
            if (ld == 0) { // half-add
                c = res[ld + rd] && left[ld];
                
                res[ld + rd] = (res[ld + rd] && !left[ld]) ||
                                (!res[ld + rd] && left[ld]);
                                
            } else { // full-add
                d = (c && res[ld + rd]) || 
                    (res[ld + rd] && left[ld]) || 
                    (left[ld] && c);
                
                res[ld + rd] = (c && !res[ld + rd] && !left[ld]) ||
                                    (!c && res[ld + rd] && !left[ld]) ||
                                    (!c && !res[ld + rd] && left[ld]) ||
                                    (c && res[ld + rd] && left[ld]);
                
                c = d; // update
            }
        }
    }
}

int main() {
    ull A, B;
    cin >> A >> B;
    ull G = gcd(A, B);
    
    A /= G;
    B /= G;
    
    bool A_arr[MAX_DIGIT], B_arr[MAX_DIGIT], G_arr[MAX_DIGIT];
    
    cast(A, A_arr);
    cast(B, B_arr);
    cast(G, G_arr);
    
    bool AB_arr[MAX_DIGIT];
    mult(A_arr, B_arr, AB_arr);
    
    bool ABG_arr[MAX_DIGIT];
    mult(AB_arr, G_arr, ABG_arr);
    
    ull thred = 1000000000000000000;
    bool thred_arr[MAX_DIGIT];
    cast(thred, thred_arr);
    if (bigger(ABG_arr, thred_arr)) cout << "Larger\n";
    else {
        ull res;
        inv_cast(res, ABG_arr);
        cout << res << endl;
    }
}