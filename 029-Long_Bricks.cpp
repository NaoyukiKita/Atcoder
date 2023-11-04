#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

const ll INFTY = 9223372036854775807;

class LazySegmentTree {
private:
    ll size, depth, capacity;
    vector<ll> nodes, lazy;

    int _leftChild(int index) { return index * 2 + 1; }
    int _rightChild(int index) { return index * 2 + 2; }
    int _parent(int index) { return (index - 1) / 2; }

    ll _getMaxVal(int begin, int end, int index, int left, int right) {
        // get max value of [begin, end)
        // nodes[index] denotes the max value of [left, right)

        if (index > nodes.size()) return -INFTY;

        // out of range
        if (right <= begin || end <= left) return -INFTY;

        // lazy propagation
        if (lazy[index] != 0) {
            nodes[_leftChild(index)] = lazy[index];
            nodes[_rightChild(index)] = lazy[index];
            lazy[index] = 0;
        }

        // [left, right) is a subset of [begin, end)
        if (begin <= left && right <= end) return nodes[index];

        int left_value = _getMaxVal(begin, end, _leftChild(index), left, right / 2);
        int right_value = _getMaxVal(begin, end, _rightChild(index), (left + right) / 2, right);

        return max(left_value, right_value);
    }

    void _rangeUpdate(int begin, int end, int value, int index, int left, int right) {
        // update values of [begin, end) to value
        // nodes[index] denotes the max value of [left, right)

        // out of range
        if (right <= begin || end <= left) return;

        // [left, right) is a subset of [begin, end)
        if (begin <= left && right <= end) {
            lazy[index] = value;
            return;
        }

        _rangeUpdate(begin, end, value, _leftChild(index), left, right / 2);
        _rangeUpdate(begin, end, value, _rightChild(index), (left + right) / 2, right);
    }

public:
    LazySegmentTree(ll size) {
        this->size = size;
        for (this->depth = 0; (1 << this->depth) <= size; this->depth += 1);
        this->capacity = 1 << (this->depth - 1);
        this->nodes = vector<ll>((1 << this->depth) - 1);
        this->lazy = vector<ll>((1 << this->depth) - 1);
    }

    ll getMaxVal(int begin, int end) {
        return _getMaxVal(begin, end, 0, 0, this->capacity);
    }

    void rangeUpdate(int begin, int end, int value) {
        return _rangeUpdate(begin, end, value, 0, 0, this->capacity);
    }
};

int main() {
    int W, N, L, R, tmp;
    cin >> W >> N;

    LazySegmentTree lst = LazySegmentTree(W);

    for (int n = 0; n < N; n++) {
        cin >> L >> R;
        tmp = lst.getMaxVal(L, R + 1);
        lst.rangeUpdate(L, R + 1, tmp + 1);
    }

    for (int left = 1; left <= W; left++) {
        cout << lst.getMaxVal(left, left + 1) << endl;
    }
}