#include <iostream>
#include <vector>
using namespace std;

class MyArr {
private:
    int size, begin;
    vector<int> seq;

public:
    MyArr (int size) {
        this->size = size;
        this->begin = 0;
        this->seq = vector<int>(size);
    }
    
    int get(int index) {
        return seq[(begin + index) % size];
    }
    
    void set(int index, int value) {
        seq[(begin + index) % size] = value;
    }
    
    void swap(int x, int y) {
        int tmp = get(x);
        set(x, get(y));
        set(y, tmp);
    }
    
    void shift(int v) {
        begin = (begin + size - v) % size;
    }
};

int main() {
    int N, Q, a;
    cin >> N >> Q;
    
    MyArr arr = MyArr(N);
    for (int i = 0; i < N; i++) {
        cin >> a;
        arr.set(i, a);
    }
    
    int cmd, x, y;
    while (Q--) {
        cin >> cmd >> x >> y; x--; y--;
        switch (cmd) {
        case 1:
            arr.swap(x, y);
            break;
        case 2:
            arr.shift(1);
            break;
        case 3:
            cout << arr.get(x) << endl;
            break;
        }
    }
}
