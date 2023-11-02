#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
private:
    int node_num;
    vector<vector <int> > links;
    vector<bool> visited;

    void _dfs(int node, vector<bool>& colors, bool isWhite) {
        visited[node] = true;
        colors[node] = isWhite;
        for (int neighbor : links[node]) {
            if (visited[neighbor]) continue;
            _dfs(neighbor, colors, !isWhite);
        }
    }
    
public:
    Graph(int N) {
        this->node_num = N;
        this->links = vector<vector <int> >(N, vector<int>());
    }

    void link(int A, int B) {
        links[A - 1].push_back(B - 1);
        links[B - 1].push_back(A - 1);
    }

    void binaryColor(vector<bool>& colors) {
        this->visited = vector<bool>(this->node_num);
        _dfs(0, colors, true);
    }
};

int main() {
    int N, A, B;
    cin >> N;

    Graph graph = Graph(N);

    for (int n = 0; n < N - 1; n++) {
        cin >> A >> B;
        graph.link(A, B);
    }

    vector<bool> colors(N);
    graph.binaryColor(colors);

    int white_counter = 0;
    for (int n = 0; n < N; n++) {
        if (colors[n]) white_counter++;
    }

    int target_color = white_counter >= (N / 2);

    int counter = 0;
    for (int n = 0; n < N; n++) {
        if (colors[n] != target_color) continue;
        cout << (n + 1) << ' ';
        if (++counter == (N / 2)) break;
    }
    cout << endl;
}