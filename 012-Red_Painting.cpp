#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
private:
    int H, W;
    vector<bool> is_red;
    vector<int> roots;
    int dir[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    bool _isInRange(int r, int c) {
        if (r < 1 || H < r) return false;
        if (c < 1 || W < c) return false;

        return true;
    }

    int _hash(int r, int c) {
        return W * (r - 1) + c - 1;
    } 

    int _getRoot(int h) {
        if (roots[h] == h) return h;
        return roots[h] = _getRoot(roots[h]);
    }

public:
    UnionFind(int H, int W) {
        int len = H * W;
        this->H = H;
        this->W = W;
        this->is_red = vector<bool>(len);
        this->roots = vector<int>(len, -1);
    }

    bool isRed(int r, int c) {
        int h = _hash(r, c);
        return is_red[h];
    }

    void printRed(int r, int c) {
        int h = _hash(r, c);
        if (is_red[h]) return;

        is_red[h] = true;
        roots[h] = h;

        int ch;
        for (int i = 0; i < 4; i++) {
            if (!_isInRange(r + dir[i][0], c + dir[i][1])) continue;

            ch = _hash(r + dir[i][0], c + dir[i][1]);
            if (!is_red[ch]) continue;

            roots[_getRoot(ch)] = h;
        }
    }

    bool hasSameRoot(int ra, int ca, int rb, int cb) {
        int ar = _getRoot(_hash(ra, ca));
        int br = _getRoot(_hash(rb, cb));

        return ar == br;
    }
};

int main() {
    int H, W, Q;
    cin >> H >> W >> Q;

    UnionFind uf = UnionFind(H, W);

    int cmd, ra, ca, rb, cb;
    while (Q--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> ra >> ca;
            uf.printRed(ra, ca);
        } else {
            cin >> ra >> ca >> rb >> cb;
            if (!uf.isRed(ra, ca) || !uf.isRed(rb, cb)) {
                cout << "No\n";
            } else if (!uf.hasSameRoot(ra, ca, rb, cb)) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        }
    }
}