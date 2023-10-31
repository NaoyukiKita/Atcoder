#include <iostream>
#include <vector>
#include <stack>
using namespace std;
using ull = unsigned long long int;

class Graph {
private:
    int node_num;
    vector<vector <int> > links, rev_links;

    void _dfs(int index, int& label, vector<int>& label2idx, vector<bool>& visited) {
        visited[index] = true;
        for (int neighbor : links[index]) {
            if(visited[neighbor]) continue;
            _dfs(neighbor, label, label2idx, visited);
        }
        label2idx[label++] = index;
    }

    void _labelNodes(vector<int>& label2idx) {
        vector<bool> visited(this->node_num + 1);
        int label = 0;
        for (int start = 1; start <= this->node_num; start++) {
            if (visited[start]) continue;
            _dfs(start, label, label2idx, visited);
        }
        
    }

    void _rev_dfs(int index, ull& counter, vector<bool>& visited) {
        visited[index] = true;
        for (int neighbor : rev_links[index]) {
            if (visited[neighbor]) continue;
            _rev_dfs(neighbor, counter, visited);
        }
        counter++;
    }

public:
    Graph(int N) {
        this->node_num = N;
        this->links = vector<vector <int> >(node_num + 1, vector<int>());
        this->rev_links = vector<vector <int> >(node_num + 1, vector<int>());
    }

    void link(int from, int to) {
        this->links[from].push_back(to);
        this->rev_links[to].push_back(from);
    }

    ull ans() {
        vector<int> label2idx(this->node_num + 1);
        _labelNodes(label2idx);

        vector<bool> visited(this->node_num + 1);
        ull ans = 0;
        for (int label = this->node_num; label >= 0; label--) {
            int start = label2idx[label];
            if (visited[start]) continue;
            ull counter = 0;
            _rev_dfs(start, counter, visited);
            ans += (counter * (counter - 1)) / 2;
        }

        return ans;
    }


};

int main() {
    int N, M, A, B;
    cin >> N >> M;

    Graph graph = Graph(N);

    while (M--) {
        cin >> A >> B;
        graph.link(A, B);
    }

    cout << graph.ans() << endl;
}