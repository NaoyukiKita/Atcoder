#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

class LazySegmentTree {
private:
    ll capacity;
    vector<ll> nodes, lazy;

    int _leftChild(int index) { return index * 2 + 1; }
    int _rightChild(int index) { return index * 2 + 2; }
    int _parent(int index) { return (index - 1) / 2; }
    bool _hasChild(int index) { return index < capacity; }
    
    void _propagate(int index) {
        nodes[_leftChild(index)] = nodes[index];
        lazy[_leftChild(index)] = nodes[index];
        
        nodes[_rightChild(index)] = nodes[index];
        lazy[_rightChild(index)] = nodes[index];
        
        lazy[index] = 0;
    }

    ll _getMaxVal(int begin, int end, int index, int left, int right) {
        // get max value of [begin, end)
        // for now it looks at [left, right)
        // nodes[index] denotes the max value of [left, right)

        // if [left, right) is out of [begin, end)
        if (right <= begin || end <= left) return 0;
        
        // if [left, right) is a subset of [begin, end)
        if (begin <= left && right <= end) return nodes[index];

        // if [begin, end) is a subset of [left, right)
        // or [left, right) includes a subset of [begin, end),
        // then [left, right) needs to be narrowed.

        // lazy propagation
        if (_hasChild(index) && lazy[index] != 0) _propagate(index);

        // nodes[index] must have children
        int left_value = _getMaxVal(begin, end, _leftChild(index), left, (left + right) / 2);
        int right_value = _getMaxVal(begin, end, _rightChild(index), (left + right) / 2, right);

        return max(left_value, right_value);
    }

    void _rangeUpdate(int begin, int end, int value, int index, int left, int right) {
        // set values of [begin, end) to `value`
        // for now it looks at [left, right) 
        // nodes[index] denotes the max value of [left, right)

        // if [left, right) is out of [begin, end)
        if (right <= begin || end <= left) return;

        // if [left, right) is a subset of [begin, end)
        // stashed update `lazy[index]` which covers [left, right) can be erased.
        if (begin <= left && right <= end) {
            nodes[index] = value; // update
            if (_hasChild(index)) lazy[index] = value; // halt propagation
            return;
        }
        
        // if [begin, end) is a subset of [left, right)
        // or [left, right) includes a subset of [begin, end),
        // then [left, right) needs to be narrowed.
        
        // lazy propagation
        if (_hasChild(index) && lazy[index] != 0) _propagate(index);

        if (nodes[index] < value) nodes[index] = value; // update
        
        // nodes[index] must have children
        _rangeUpdate(begin, end, value, _leftChild(index), left, (left + right) / 2);
        _rangeUpdate(begin, end, value, _rightChild(index), (left + right) / 2, right);
    }

public:
    LazySegmentTree(ll capacity) {
        this->capacity = capacity;
        this->nodes = vector<ll>(2 * capacity - 1);
        this->lazy = vector<ll>(2 * capacity - 1);
    }

    ll getMaxVal(int begin, int end) {
        return _getMaxVal(begin, end, 0, 0, this->capacity);
    }

    void rangeUpdate(int begin, int end, int value) {
        _rangeUpdate(begin, end, value, 0, 0, this->capacity);
    }
    
    void update(int index, int value) {
        _rangeUpdate(index, index + 1, value, 0, 0, this->capacity);
    }
};

int main() {
    int W, N, L, R, tmp;
    cin >> W >> N;

    int capacity;
    for (capacity = 1; capacity < W; capacity *= 2);
    LazySegmentTree lst = LazySegmentTree(capacity);

    for (int n = 0; n < N; n++) {
        cin >> L >> R;
        tmp = lst.getMaxVal(L - 1, R);
        cout << (tmp + 1) << endl;
        lst.rangeUpdate(L - 1, R, tmp + 1);
    }
}