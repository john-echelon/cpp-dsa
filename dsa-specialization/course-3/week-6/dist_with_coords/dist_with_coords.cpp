#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <iostream>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INF_LEN = numeric_limits<Len>::max() / 4;

class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<vector<Len>> dist_actual_;
    vector<vector<double>> potential_;
    vector<int> workset_;
    vector<vector<bool>> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;

public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
        : n_(n), adj_(adj), cost_(cost), 
        distance_(2, vector<Len>(n_, INF_LEN)),
        dist_actual_(2, vector<Len>(n_, INF_LEN)),
        potential_(2, vector<double>(n_, 0)),
        visited_(2, vector<bool>(n)),
        xy_(xy)
    { 
        workset_.reserve(n);
    }

    // See the description of this method in the starter for friend_suggestion
    void clear() {

        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INF_LEN;
            visited_[0][v] = false; visited_[1][v] = false;
            potential_[0][v] = potential_[1][v] = 0;
            dist_actual_[0][v] = dist_actual_[1][v] = INF_LEN;
        }
        workset_.clear();
    }

    void compute_potentials(int side, int t) {
        for (int i = 0; i < n_; i++) {
            double x = (xy_[t].first - xy_[i].first);
            double y = (xy_[t].second - xy_[i].second);
            potential_[side][i] = sqrt(x * x + y * y);
        }
    }
    void balance_potentials() {
        for (int i = 0; i < n_; i++) {
            potential_[0][i] = (potential_[0][i] - potential_[1][i]) / 2;
            potential_[1][i] = potential_[0][i] * -1;
        }
    }
    Len shortest_path() {
        Len best_distance = INF_LEN;
        for(int u : workset_) {
            if (dist_actual_[0][u] + dist_actual_[1][u] < best_distance) {
                best_distance = dist_actual_[0][u] + dist_actual_[1][u];
            }
        }
        return best_distance;
    }

    // Processes visit of either forward or backward search 
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue& q, int side, int v, Len dist) {
        // Implement this method yourself
        Len total = 0;
        for (int i = 0; i < adj_[side][v].size(); i++) {
            // Relax()
            int w = adj_[side][v][i];
            int cost = cost_[side][v][i];

            if (distance_[side][w] > dist_actual_[side][v] + cost + potential_[side][w])
            {
                dist_actual_[side][w] = dist_actual_[side][v] + cost;
                distance_[side][w] = dist_actual_[side][v] + cost + potential_[side][w];
                q[side].push({ distance_[side][w], w });
                workset_.push_back(w);
            }
        }
    }
    // Returns the distance from s to t in the graph
    Len query(int s, int t) {
        clear();
        Queue q(2);
        // Implement the rest of the algorithm yourself
        compute_potentials(0, t);
        compute_potentials(1, s);
        balance_potentials();
        distance_[0][s] = potential_[0][s] + 0;
        distance_[1][t] = potential_[1][t] + 0;
        dist_actual_[0][s] = 0;
        dist_actual_[1][t] = 0;
        q[0].push(pair<Len, int>(distance_[0][s], s));
        q[1].push(pair<Len, int>(distance_[1][t], t));

        workset_.push_back(s);
        workset_.push_back(t);
        while(true) {
            if (q[0].empty() == true || q[1].empty() == true) {
                break;
            }
            pair<Len, int> v = q[0].top();
            q[0].pop();
            if (visited_[1][v.second] == true) {
                return shortest_path();
            }
            visit(q, 0, v.second, v.first);
            visited_[0][v.second] = true;

            v = q[1].top();
            q[1].pop();
            if (visited_[0][v.second] == true) {
                return shortest_path();
            }
            visit(q, 1, v.second, v.first);
            visited_[1][v.second] = true;
        }

        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
