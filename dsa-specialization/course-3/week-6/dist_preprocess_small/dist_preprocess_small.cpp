#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

const int INFINITY = numeric_limits<int>::max() / 2;
class Graph
{
    typedef int Distance;
    typedef int Vertex;

    // Number of nodes
    int N;
    // Source and target
    int s, t;
    // Estimate of the distance from s to t
    int estimate = INFINITY;
    // Lists of edges outgoing from each node
    vector<vector<pair<int, int>>> outgoing_edges;
    // Lists of edges incoming to each node
    vector<vector<pair<int, int>>> incoming_edges;

    // Levels of nodes for node ordering
    vector<int> level;
    // Ranks of nodes - positions in the node ordering
    vector<int> rank;
    // Track which nodes were contracted
    vector<bool> contracted;
    // Track neighbors of nodes that were contracted
    vector<int> contracted_neighbors;
    // Witness path variables
    vector<int> witness_path_workset;
    vector<int> witness_path_distance;
    vector<bool> witness_path_visited;
    vector<int> witness_path_hops;

    // Distance to node v, bidistance[0][v] - from source in the forward search,
    // bidistance[1][v] - from target in the backward search.
    vector<vector<Distance>> bidistance;
    // Stores all the nodes visited either by forward or backward search.
    vector<vector<int>> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<vector<bool>> visited_;
    // Wrapper around STL priority_queue
    class StlHeap
    {
        public:
        using T = pair<Distance, Vertex>;
        using Queue = priority_queue<T, vector<T>, greater<T>>;

        StlHeap() {
            queue.reset(new Queue());
        }

        bool empty() const {
            return queue->empty();
        }

        void push(Vertex v, Distance d) {
            queue->push(make_pair(d,v));
        }

        void clear() {
            queue.reset(new Queue());
        }

        pair<Distance, Vertex> pop() {
            pair<Distance, Vertex> top = queue->top();
            queue->pop();
            return top;
        }

        private:
        unique_ptr<Queue> queue;
    };

    // Priority queues for forward and backward searches
    StlHeap diqueue[2];
    public:
    Graph() {
        read_stdin();
        witness_path_workset.reserve(N);
        witness_path_distance.assign(N, INFINITY);
        witness_path_hops.assign(N, 0);
        witness_path_visited.assign(N, false);

        workset_.resize(2, vector<int>(0));
        bidistance.assign(2, vector<Distance>(N, INFINITY));
        visited_.assign(2, vector<bool>(N, false));
    }

    void print_edges() {
        cout << "incoming\n";
        for (int i = 0; i < incoming_edges.size(); i++)
        for (int j = 0; j < incoming_edges[i].size(); j++)
        {
            int v, c;
            tie(v, c) = incoming_edges[i][j];
            cout << i + 1 << "-" << v + 1 << ": " << c << endl;
        }
        cout << "outgoing\n";
        for (int i = 0; i < outgoing_edges.size(); i++)
        for (int j = 0; j < outgoing_edges[i].size(); j++)
        {
            int v, c;
            tie(v, c) = outgoing_edges[i][j];
            cout << i + 1 << "-" << v + 1 << ": " << c << endl;
        }

        for (int i = 0; i < rank.size(); i++) {
            cout << "rank " << i + 1 << " " << rank[i] << endl;
        }
    }
    int get_n() { return N;}

    vector<pair<int, int>>& get_adjacent(int v, bool forward = true) {
        if (forward) {
            return outgoing_edges[v];
        } else {
            return incoming_edges[v];
        }
    }

    void preprocess() {
        // Priority queue will store pairs of (importance, node) with the least important node in the head
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> preproc_queue;

        // Implement the rest of the algorithm yourself
        // vector<vector<Shortcut>> shortcuts(N, vector<Shortcut>(0));
        level.assign(N, 0);
        rank.assign(N, 0);
        contracted.assign(N, 0);
        contracted_neighbors.assign(N, 0);
        int order = 1;
        for (int i = 0; i < N; i++) {
            preproc_queue.push({compute_importance(i), i});
        }
        while (!preproc_queue.empty()) {
            int v = preproc_queue.top().second;
            preproc_queue.pop();

            // recompute importance
            int prev_imp = compute_importance(v);
            int next_imp = preproc_queue.top().first;
            // if it's still minimal (compare with the top of the priority queue), contract the node
            // otherwise, put it back into priority queue with new priority 
            if (prev_imp <= next_imp) {
                contract_node(v);
                rank[v] = order++;
            } else {
                preproc_queue.push({prev_imp, v});
            } 
        }
    }

    // Returns distance from s to t in the graph
    int query(int u, int w) {
        // update(u, 0, true);
        // update(w, 0, false);
        // s = u; 
        // t = w;
        // Implement the rest of the algorithm yourself

        // return -1;
        return compute_distance(u, w);
    }

    private:
    // Try to relax the node v using distance d either in the forward or in the backward search
    void update(int v, int d, bool forward) {
        // Implement this method yourself
    }

    class VertexSet
    {
        public:
        VertexSet(int n = 0) : visited(n) {}
        void resize(int n) {
            visited.resize(n);
        }
        void add(int v) {
            if (!visited[v]) {
                vertices.push_back(v);
                visited[v] = true;
            }
        }
        const vector<int>& get() const {
            return vertices;
        }
        const bool has(int v) {
            return visited[v];
        }
        void clear() {
            for (int v : vertices) {
                visited[v] = false;
            }
            vertices.clear();
        }

        private:
        vector<int> visited;
        vector<int> vertices;
    };
    VertexSet visited;

    // QEntry = (distance, vertex)
    typedef pair<int,int> QEntry;
    priority_queue<QEntry, vector<QEntry>, greater<QEntry>> queue;

    struct Shortcut {
        int from;
        int to;
        int cost;
    };

    // Adds all the shortcuts for the case when node v is contracted, and returns the importance of node v
    // in this case
    int do_shortcut(int v, vector<Shortcut>& shortcuts, int& mylevel) {
        // Implement this method yourself

        // Add neighbors and shortcut cover heuristics
        return (shortcuts.size() - outgoing_edges[v].size() - incoming_edges[v].size()) + mylevel;
    }

    void set_n(int n) {
        N = n;
        outgoing_edges.resize(n);
        incoming_edges.resize(n);
    }


    void add_edge_to_list(vector<pair<int,int>>& list, int w, int c) {
        for (int i = 0; i < list.size(); ++i) {
            pair<int, int>& p = list[i];
            if (p.first == w) {
                if (p.second > c) {
                    p.second = c;
                }
                return;
            }
        }
        list.push_back({ w, c });
    }

    void add_directed_edge(int u, int v, int c) {
        add_edge_to_list(outgoing_edges[u], v, c);
        add_edge_to_list(incoming_edges[v], u, c);
    }

    void add_edge(int u, int v, int c) {
        add_directed_edge(u, v, c);
    }

    void finalize() {
        // Remove unnecessary edges
    }

    bool read_stdin() {
        int u,v,c,n,m;
        assert(scanf("%d %d", &n, &m) == 2);
        set_n(n);
        for (int i = 0; i < m; ++i) {
            assert(scanf("%d %d %d", &u, &v, &c) == 3);
            add_edge(u-1, v-1, c);
        }
        finalize();
        return true;
    }

    int compute_importance(int v) {
        int shortcuts = 0;
        int total_edges = 0;
        for (auto pair_u: incoming_edges[v]) {
            int u = pair_u.first;
            if (!contracted[u])
                total_edges++;
        }
        for (auto pair_w: outgoing_edges[v]) {
            int w = pair_w.first;
            if (!contracted[w])
                total_edges++;
        }
        for (auto pair_u: incoming_edges[v]) 
        for (auto pair_w: outgoing_edges[v]) {
            int u = pair_u.first;
            int w = pair_w.first;
            if (!contracted[u] && !contracted[w]) {
                shortcuts++;
            }
        }
        return shortcuts - total_edges + contracted_neighbors[v];
    }

    void contract_node(int v) {
        contracted[v] = true;
        // Limit the search distance by max(l(u,v) + l(v,w))
        int dist_limit = 0;
        for (auto pair_u: incoming_edges[v])
        for (auto pair_w: outgoing_edges[v]) {
            int u = pair_u.first;
            int w = pair_w.first;
            if (!contracted[u] && !contracted[w])
                dist_limit = max(pair_u.second + pair_w.second, dist_limit);
        }

        for (auto pair_u: incoming_edges[v]) {
            int u = pair_u.first;
            if (contracted[u])
                continue;
            check_witness_path(u, dist_limit);
            for (auto pair_w: outgoing_edges[v]) {
                int w = pair_w.first;
                if (contracted[w])
                    continue;
                int new_weight = pair_u.second + pair_w.second;
                if (witness_path_distance[u] > new_weight) {
                    add_directed_edge(u, w, new_weight);
                    // TODO: log shortcut data here
                }
            }
        }
        tally_neighbors(v);
        tally_neighbors(v, false);
    }
    void tally_neighbors(int v, bool forward =  true) {
        for (auto pair_u: get_adjacent(v, forward)) {
            int u = pair_u.first;
            contracted_neighbors[u]++;
            level[u] = max(level[u], level[v] + 1);
        }
    }

    void witness_path_clear() {
        for (auto i: witness_path_workset) {
            witness_path_distance[i] = INFINITY;
            witness_path_hops[i] = 0;
            witness_path_visited[i] = false;
        }
        witness_path_workset.clear();
    }
    void check_witness_path(int u, int dist_limit, int max_hops = 5) {
        witness_path_clear();
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> witness_path_queue;
        witness_path_distance[u] = 0;
        witness_path_hops[u] = 0;
        witness_path_visited[u] = true;
        witness_path_queue.push({0, u});
        witness_path_workset.push_back(u);
        while(!witness_path_queue.empty()) {
            int costV, v;
            tie(costV, v) = witness_path_queue.top();
            witness_path_queue.pop();
            witness_path_visited[v] = true;
            witness_path_workset.push_back(v);

            if (witness_path_distance[v] > dist_limit)
                break;
            if (witness_path_hops[v] > max_hops)
                continue;
            // visit & relax edges
            for (auto pair: outgoing_edges[v]) {
                int w = pair.first;
                int costW = pair.second;
                if (contracted[w] || witness_path_visited[w])
                    continue;
                if (witness_path_distance[w] > witness_path_distance[v] + costW)
                {
                    witness_path_distance[w] = witness_path_distance[v] + costW;
                    witness_path_queue.push({witness_path_distance[w], w});
                    witness_path_workset.push_back(w);
                    witness_path_hops[w] = witness_path_hops[v] + 1;
                }
            }
        }
    }

    void clear_workset(int side = 0) {
        for (auto f: workset_[side]) {
            bidistance[side][f] = INFINITY;
            visited_[side][f] = false;
        }
        workset_[side].clear();
    }

    void visit(int v, int side) {
        int w, dist;
        for (auto & p: get_adjacent(v, side == 0)) {
            tie(w, dist) = p;
            if (visited_[side][w])
                continue;
            if ((bidistance[side][w] > dist + bidistance[side][v]) && rank[w] >= rank[v]) {
                bidistance[side][w] = dist + bidistance[side][v];
                diqueue[side].push(w, bidistance[side][w]);
                workset_[side].push_back(w);
            }
        }
    }
    int compute_distance(int s, int t) {
        clear_workset(0);
        clear_workset(1);
        int estimate = INFINITY;
        bidistance[0][s] = bidistance[1][t] = 0;
        visited_[0][s] = visited_[1][t] = true;
        diqueue[0].push(s, 0);
        diqueue[1].push(t, 0);
        workset_[0].push_back(s);
        workset_[1].push_back(t);

        int v, dist;
        while (!diqueue[0].empty() || !diqueue[1].empty()){
            if (!diqueue[0].empty()) {
                tie(dist, v) = diqueue[0].pop();
                visited_[0][v] = true;
                if (bidistance[0][v] <= estimate)
                    visit(v, 0);
                estimate = min(estimate, bidistance[0][v] + bidistance[1][v]);
            }
            if (!diqueue[1].empty()) {
                tie(dist, v) = diqueue[1].pop();
                visited_[1][v] = true;
                if (bidistance[1][v] <= estimate)
                    visit(v, 1);
                estimate = min(estimate, bidistance[0][v] + bidistance[1][v]);
            }
        }
        if (estimate == INFINITY)
            return -1;
        return estimate;
    }

};

int main() {
    Graph g;
    // g.print_edges();
    g.preprocess();
    // g.print_edges();
    cout << "Ready" << endl;

    int t;
    assert(scanf("%d", &t) == 1);
    for (int i = 0; i < t; ++i) {
        int u, v;
        assert(scanf("%d %d", &u, &v) == 2);
        printf("%d\n", g.query(u-1, v-1));
    }
}
