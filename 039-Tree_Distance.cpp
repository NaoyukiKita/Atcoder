#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

class Graph {
private:
    int n_nodes;
    vector<vector <int> > links;
    vector<pair<int, int> > memo;
    vector<int> dp;
    
    void _dfs(int current, int previous) {
        dp[current] = 1;
        for (int neighbor : links[current]) {
            if (neighbor == previous) continue;
            _dfs(neighbor, current);
            dp[current] += dp[neighbor];
        }
    }
    
public:
    Graph(int n_nodes) {
        this->n_nodes = n_nodes;
        this->links = vector<vector <int> >(n_nodes, vector<int>());
        this->memo = vector<pair<int, int> >();
        this->dp = vector<int>(n_nodes);
    }
    
    void link(int a, int b) {
        links[a].push_back(b);
        links[b].push_back(a);
        memo.push_back(make_pair(a, b));
    }
    
    ll getAns() {
        _dfs(0, -1);
        
        ll ans = 0;
        for (int i = 0; i < memo.size(); i++) {
            pair<int, int> edge = memo[i];
            ll a = min(dp[edge.first], dp[edge.second]);
            ans += a * (n_nodes - a);
        }
        
        return ans;
    }
};

int main() {
    int N, a, b;
    cin >> N;
    
    Graph graph = Graph(N);
    
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        graph.link(a - 1, b - 1);
    }
    
    cout << graph.getAns() << endl;
}
