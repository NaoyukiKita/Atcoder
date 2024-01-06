#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

class SegmentTree { // diligent
private:
    int capacity;
    vector<ll> nodes;
    
    int _leftChild(int index) { return index * 2 + 1; }
    int _rightChild(int index) { return index * 2 + 2; }
    int _parent(int index) { return (index - 1) / 2; }
    
    ll _getMaxVal(int begin, int end, int index, int left, int right) {
        // if [left, right) is out of [begin, end)
        if (end <= left || right <= begin) return -1;
        
        // if [left, right) is a subset of [begin, end)
        if (begin <= left && right <= end) return nodes[index];
        
        ll left_value = _getMaxVal(begin, end, _leftChild(index), left, (left + right) / 2);
        ll right_value = _getMaxVal(begin, end, _rightChild(index), (left + right) / 2, right);
        
        return max(left_value, right_value);
    }
    
public:
    SegmentTree(int capacity) {
        this->capacity = capacity;
        this->nodes = vector<ll>(capacity * 2 - 1, -1);
    }
    
    void update(int index, ll value) {
        int leaf = index + capacity - 1;
        
        // update leaf
        nodes[leaf] = value;
        
        // back propagation
        for (int node = _parent(leaf); ; node = _parent(node)) {
            nodes[node] = max(nodes[_leftChild(node)], nodes[_rightChild(node)]);
            if (node == 0) break;
        }
    }
    
    ll getMaxVal(int begin, int end) {
        return _getMaxVal(begin, end, 0, 0, capacity);
    }
    
    ll get(int index) {
        return nodes[index + capacity - 1];
    }
    
    void t_print() {
        for (int i = 0; i < capacity; i++) {
            cout << get(i) << " \n"[i == capacity - 1];
        }
    }
    
    ll t_getMaxVal(int begin, int end, int index, int left, int right) {
        cout << "_getMaxVal(" << begin << ", " << end << ", " << index << ", " << left << ", " << right << ")\n";
        // if [left, right) is out of [begin, end)
        if (end <= left || right <= begin) return -1;
        
        // if [left, right) is a subset of [begin, end)
        if (begin <= left && right <= end) return nodes[index];
        
        ll left_value = t_getMaxVal(begin, end, _leftChild(index), left, (left + right) / 2);
        ll right_value = t_getMaxVal(begin, end, _rightChild(index), (left + right) / 2, right);
        
        return max(left_value, right_value);
    }
};

int main() {
    int W, N, L, R, V;
    
    cin >> W >> N;
    
    int capacity;
    for (capacity = 1; capacity <= W; capacity *= 2);
    vector<SegmentTree> sts(N + 1, SegmentTree(capacity));
    sts[0].update(0, 0);
    // sts[0].t_print();
    
    ll value, local_max;
    int begin, end;
    for (int n = 1; n <= N; n++) {
        cin >> L >> R >> V;
        for (int w = 0; w <= W; w++) {
            // opt1. not select nth meal
            value = sts[n - 1].get(w);
            
            // opt2. select nth meal
            if (w >= L) {
                begin = max(0, w - R);
                end = w - L + 1;
                
                local_max = sts[n - 1].getMaxVal(begin, end);
                
                if (local_max != -1) {
                    value = max(value, local_max + V);
                }
                
            }
            
            // update
            sts[n].update(w, value);
        }
        // sts[n].t_print();
    }
    
    cout << sts[N].get(W) << endl;
    
    // cout << sts[0].t_getMaxVal(0, 2, 0, 0, capacity) << endl;
    
    // cout << sts[0].t_getMaxVal(0, 2, 7, 0, 2) << endl;
}
