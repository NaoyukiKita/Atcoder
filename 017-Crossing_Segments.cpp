#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
using ll = long long;

struct Segment {
    int L, R;

    bool operator<(const Segment& right) const {
        if (R == right.R) return L < right.L;
        return R < right.R;
    }
};

class Bit {
private:
    int length;
    vector<ll> vec;

    ll _getSum(int end) {
        // sum of vec[i] s.t. i \in [0, end)
        stack<int> stk;
        for (int i = 1; i <= end; i *= 2) {
            if (!(i & end)) continue;
            stk.push(i);
        }

        int index = 0;
        ll retval = 0;
        while(!stk.empty()) {
            index += stk.top(); stk.pop();
            retval += vec[index - 1];
        }

        return retval;
    }

public:
    Bit (int length) {
        this->length = length;
        this->vec = vector<ll>(length + 1);
    }

    void add(int index, int amount) {
        index++;
        int d = 1;
        while (index <= length) {
            vec[index - 1] += amount;
            for (; index % (d * 2) == 0; d *= 2);
            index += d;
        }
    }

    ll getSum(int begin, int end) {
        // sum of vec[i] s.t. i \in [begin, end)
        return _getSum(end) - _getSum(begin);
    }
};

int main() {
    ll N, M;
	cin >> N >> M;

    vector<Segment> segs(M);
    vector<ll> Ls(N + 1), Rs(N + 1);

	for (int i = 0; i < M; i++) {
        cin >> segs[i].L >> segs[i].R;
        Ls[segs[i].L]++;
        Rs[segs[i].R]++;
    }


    ll answer1 = 0;
    ll cnt = 0;
    for (int j = 1; j <= N; j++) {
        cnt = Ls[j] + Rs[j];
        answer1 += cnt * (cnt - 1LL) / 2LL;
    }

    ll answer2 = 0;
    vector<ll> Rsum(N + 1);
    for (int j = 1; j <= N; j++) {
        Rsum[j] = Rs[j - 1] + Rsum[j - 1];
    }
    for (int i = 0; i < M; i++) {
        answer2 += Rsum[segs[i].L];
    }

    sort(segs.begin(), segs.end());

	ll answer3 = 0;
	Bit bit = Bit(N);
    for (int i = 0; i < M; i++) {
        ll cl = segs[i].L, cr = segs[i].R;
        ll ret = bit.getSum(cl + 1, cr + 1);
        
        answer3 += ret;
        bit.add(cl, 1);
    }

	ll total = M * (M - 1) / 2LL;
	ll sum_ans = answer1 + answer2 + answer3;
	cout << total - sum_ans << endl;
	return 0;
}