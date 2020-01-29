#include <iostream>
#include <bits/stdc++.h> 
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>

using std::queue;
using std::vector;
using std::cin;
using std::cout;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

    struct VertexInfo {
      int dist = INT_MAX;
      int prev = -1;
    };
    vector<int> matching;
public:
    int num_left = 0;
    explicit FlowGraph(size_t num_left, int num_right):
      graph(num_left + num_right + 1), num_left(num_left), matching(num_left + num_right + 1, -1) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }

    int bfs(int s, vector<VertexInfo> & info, int & t) {
      std::fill(info.begin(), info.end(), VertexInfo{ INT_MAX, -1 });
      info[s].dist = 0;
      queue<std::pair<int, int>> bfs_queue;
      bfs_queue.push({ s, INT_MAX });
      while(!bfs_queue.empty()) {
        int u = bfs_queue.front().first;
        int flow = bfs_queue.front().second;
        bfs_queue.pop();
        const vector<size_t> & adj = get_ids(u);
        for (int id: adj) {
          const Edge & e = get_edge(id);
          int v = e.to;
          // cout << "from: " << e.from << " to: " << e.to << " cap " << e.capacity << " flow " << e.flow << "\n";
          if (e.from != v && s != v && info[v].dist == INT_MAX && e.capacity - e.flow > 0) {
            info[v].prev = id; // prev edge id
            info[v].dist = info[u].dist + 1;
            int updatedFlow = std::min(flow, e.capacity - e.flow);
            if (v > num_left && matching[v] == -1) {
              // cout << "v: " << v << "\n";
              t = v;
              return updatedFlow;
            }
            bfs_queue.push({ v, updatedFlow });
          }
        }
      }
      return 0;
    }

    vector<int> find_matching(int from, int to) {
      int flow = 0, updatedFlow;
      vector<VertexInfo> info(graph.size(), VertexInfo());

      while (updatedFlow = bfs(from, info, to)) {
        // cout << "updating flow: " << updatedFlow << "\n";
        flow += updatedFlow;
        int cur = to;
        while (cur != from) {
          int id = info[cur].prev;
          add_flow(id, updatedFlow); //needs to be edge id
          const Edge & e = get_edge(id);
          cur = e.from;
          if ((matching[e.from] || matching[e.to]) && e.to > num_left) {
            matching[e.from] = e.to;
            matching[e.to] = e.from;
          }
          if (cur == from)
            // cout << "e.from " << e.from << " e.to " << e.to << " to " << to << "\n";
            if (!matching[to]) {
              matching[e.to] = to;
              matching[to] = e.to;
            }
        }
      }
      // for (auto & e : edges) {
      //   cout << "e.from " << e.from << " e.to " << e.to << " e.flow " << e.flow << "\n";
      // }
      return matching;
    }
};
class MaxMatching {
 public:
  void Solve() {
    // vector<vector<bool>> adj_matrix = ReadData();
    FlowGraph graph = ReadData();
    vector<int> matching = FindMatching(graph);
    WriteResponse(matching, graph.num_left);
  }

 private:
  FlowGraph ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    FlowGraph graph(num_left, num_right);
    for (int i = 1; i <= num_left; ++i) { // num_left = 3; i 1-3
      graph.add_edge(0, i, 1);
      for (int j = num_left + 1; j <= num_left + num_right; ++j) { // num_right = 4; 4-7
        int bit;
        cin >> bit;
        if (bit == 1) {
          graph.add_edge(i, j, 1);
        }
      }
    }
    return graph;
  }

  void WriteResponse(const vector<int>& matching, int num_left) {
    for (int i = 1; i <= num_left; ++i) {
      if (i > 1)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i]- num_left);
    }
    cout << "\n";
  }

  vector<int> FindMatching(FlowGraph& graph) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int from = 0, to = graph.size() - 1;
    vector<int> matching = graph.find_matching(from, to);
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
