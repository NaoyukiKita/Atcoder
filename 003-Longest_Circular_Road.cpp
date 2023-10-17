#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
    int node_num;
    vector<vector <int>> links;
    vector<int> dis;
    
    void _dfs(int start) {
        stack<int> stk;
        stk.push(start);
        dis[start] = 0;
        
        while(!stk.empty()) {
            int node = stk.top(); stk.pop();
            
            for (int neighbor : links[node]) {
                if (dis[neighbor] != -1) continue;
                stk.push(neighbor);
                dis[neighbor] = dis[node] + 1;
            }
        }
    }
    
    pair<int, int> _get_farest(int start) {
        _dfs(start);
        
        int farest, current = 0;
        for (int node = 1; node <= node_num; node++) {
            if (current > dis[node]) continue;
            farest = node;
            current = dis[node];
        }
        
        return make_pair(farest, current);
    }
    
public:
    Graph(int node_num) :
        node_num(node_num),
        links(vector<vector <int>>(node_num + 1, vector<int>())),
        dis(vector<int>(node_num + 1, -1))
    {}
    
    void link(int from, int to, bool bidirectional) {
        links[from].push_back(to);
        if (bidirectional) links[to].push_back(from);
    }
    
    int get_radius(){
        int start = 1;
        start = _get_farest(start).first;
        dis = vector<int>(node_num + 1, -1);

        return _get_farest(start).second;
    }
};

int main() {
    int N, A, B;
    cin >> N;
    
    Graph graph = Graph(N);
    
    for (int n = 0; n < N; n++) {
        cin >> A >> B;
        graph.link(A, B, true);
    }
    
    cout << graph.get_radius() + 1 << endl;
}