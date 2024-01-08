#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Graph {
private:
    #define INFTY 2147483647
    #define UP 0
    #define DOWN 1
    #define RIGHT 2
    #define LEFT 3
    #define N_DIRECTIONS 4
    const int directions[N_DIRECTIONS] = {UP, DOWN, RIGHT, LEFT};
    
    int height, width;
    vector<vector <char> > grid;
    vector<vector <vector <int> > > costs;
    
    typedef struct {
        int x, y, direction;
    } Point;
    
    Point _move(Point& point, int direction) {
        switch (direction) {
        case UP:
            return {point.x-1, point.y, UP};
        case DOWN:
            return {point.x+1, point.y, DOWN};
        case RIGHT:
            return {point.x, point.y+1, RIGHT};
        case LEFT:
            return {point.x, point.y-1, LEFT};
        }
        return {-1, -1, -1};
    }
    
    bool _reachable(Point& point) {
        if (point.x < 0 || height <= point.x) return false;
        if (point.y < 0 || width <= point.y) return false;
        return grid[point.x][point.y] == '.';
    }
    
    int _getCost(Point& point) { 
        return costs[point.x][point.y][point.direction];
    }
    
    void _setCost(Point& point, int cost) {
        costs[point.x][point.y][point.direction] = cost;
    }
    
    void _push(deque<Point>& deq, Point& point, bool front) {
        if (front) deq.push_front(point);
        else deq.push_back(point);
    }
    
public:
    Graph(int H, int W) {
        this->height = H;
        this->width = W;
        this->grid = vector<vector <char> >(H, vector<char>(W));
        this->costs = vector<vector <vector <int> > >(H,
                        vector <vector <int> >(W,
                        vector<int>(N_DIRECTIONS, INFTY)));
    }
    
    void setGrid(int h, int w, char value) {
        grid[h][w] = value;
    }
    
    int getAns(int start_x, int start_y, int goal_x, int goal_y) {
        deque<Point> deq;
        
        for (int direction : directions) {
            Point current = {start_x, start_y, direction};
            deq.push_back(current);
            _setCost(current, 0);
        }
        
        int current_cost, next_cost;
        bool turn;
        while (!deq.empty()) {
            Point current = deq.front(); deq.pop_front();
            current_cost = _getCost(current);
            
            for (int direction : directions) {
                Point next = _move(current, direction);
                if (!_reachable(next)) continue;
                
                turn = next.direction != current.direction;
                next_cost = current_cost + int(turn);
                
                if (next_cost >= _getCost(next)) continue;
                _setCost(next, next_cost);
                _push(deq, next, !turn);
            }
        }
        
        int ans = INFTY;
        for (int direction : directions) {
            Point point = {goal_x, goal_y, direction};
            ans = min(ans, _getCost(point));
        }
        
        return ans;
    }
    
    #undef INFTY
    #undef UP
    #undef DOWN
    #undef RIGHT
    #undef LEFT
    #undef N_DIRECTIONS
};

int main() {
    int H, W, start_x, start_y, goal_x, goal_y;
    cin >> H >> W;
    
    cin >> start_x >> start_y; start_x--; start_y--;
    cin >> goal_x >> goal_y; goal_x--; goal_y--;
    
    Graph graph = Graph(H, W);
    
    char s;
    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) {
            cin >> s;
            graph.setGrid(h, w, s);
        }
    }
    
    cout << graph.getAns(start_x, start_y, goal_x, goal_y) << endl;
}
