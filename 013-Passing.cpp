#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    struct Node {
        int index, cost;
        bool operator<(const Node& right) const {
            return cost == right.cost ? index > right.index : cost > right.cost;
        }
    };

    Node _initNode(int index, int cost) {
        Node node;
        node.index = index;
        node.cost = cost;

        return node;
    }

    int node_num;
    vector<vector <Node> > links;
    vector<bool> fixed;
public:
    Graph(int node_num) {
        this->node_num = node_num;
        this->links = vector<vector <Node> > (node_num + 1, vector<Node>());
    }

    void link(int a, int b, int c) {
        this->links[a].push_back(_initNode(b, c));
        this->links[b].push_back(_initNode(a, c));
    }

    void calcCosts(vector<int>& res, int from) { // Dijkstra
        if (res.size() != this->node_num + 1) {
            cout << "size unmatch: expected " << this->node_num + 1 << ", got " << res.size() << endl;
            return;
        }

        this->fixed = vector<bool>(this->node_num + 1);

        priority_queue<Node> pque; // stores node index and distance from `from`
        pque.push(_initNode(from, 0));

        while(!pque.empty()) {
            Node node = pque.top(); pque.pop(); // has the smallest cost
            if (fixed[node.index]) continue;

            fixed[node.index] = true;
            res[node.index] = node.cost;

            for (Node neighbor : this->links[node.index]) {
                if (fixed[neighbor.index]) continue;
                pque.push(_initNode(neighbor.index, (node.cost + neighbor.cost)));
            }
        }
    }
};

int main() {
    int N, M, a, b, c;
    cin >> N >> M;
    Graph graph = Graph(N);

    while (M--) {
        cin >> a >> b >> c;
        graph.link(a, b, c);
    }

    vector<int> cost_from_1(N + 1), cost_from_N(N + 1);
    graph.calcCosts(cost_from_1, 1);
    graph.calcCosts(cost_from_N, N);

    int cost;
    for (int k = 1; k <= N; k++) {
        cost = cost_from_1[k] + cost_from_N[k];
        cout << cost << endl;
    }
}