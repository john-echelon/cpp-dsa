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
        int dist = INT_MAX;
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

public:
    vector<int> edgeCount;
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        // graph[to].push_back(edges.size());
        // edges.push_back(backward_edge);
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
        // edges[id ^ 1].flow -= flow;
    }

    int bfs(int s, int t, vector<VertexInfo> & info) {
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
          if (e.from != v && s != v && info[v].dist == INT_MAX && e.capacity - e.flow > 0) {
            info[v].prev = id; // prev edge id
            info[v].dist = 1;
            int updatedFlow = std::min(flow, e.capacity - e.flow);
            if (v == t)
              return updatedFlow;
            bfs_queue.push({ v, updatedFlow });
          }
        }
      }
      return 0;
    }

    int max_flow(int from, int to) {
      int flow = 0, updatedFlow;
      vector<VertexInfo> info(graph.size(), VertexInfo());
      while(updatedFlow = bfs(from, to, info)) {
        flow += updatedFlow;
        int cur = to;
        while (cur != from) {
          int id = info[cur].prev;
          add_flow(id, updatedFlow); //needs to be edge id
          const Edge & e = get_edge(id);
          cur = e.from;
        }
      }
      return flow;
    }
    vector<int> find_matching(int from, int to) {
      int flow = 0, updatedFlow;
      vector<int> matching(get_ids(from).size(), -1);
      vector<VertexInfo> info(graph.size(), VertexInfo());
      while(updatedFlow = bfs(from, to, info)) {
        flow += updatedFlow;
        int cur = to;
        int cur_num_right;
        if (cur != from) {
          VertexInfo & vi = info[cur];
          const Edge & ei = get_edge(vi.prev);
          cur_num_right = get_edge(info[cur].prev).from;
        }
        while (cur != from) {
          int id = info[cur].prev;
          add_flow(id, updatedFlow); //needs to be edge id
          const Edge & e = get_edge(id);
          cur = e.from;
          if (cur == from)
            matching[e.to - 1] = cur_num_right - matching.size() - 1;
        }
      }
      // cout << "flow: " << flow << std::endl;
      return matching;
    }
};
class MaxMatching {
 public:
  void Solve() {
    // vector<vector<bool>> adj_matrix = ReadData();
    FlowGraph graph = ReadData();
    vector<int> matching = FindMatching(graph);
    WriteResponse(matching);
  }

 private:
  // vector<vector<bool>> ReadData() {
  FlowGraph ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    // vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    FlowGraph graph(num_left + num_right + 2);
    vector<int> edgeCount(num_left, 0);
    for (int i = 1; i <= num_left; ++i) { // 1-3
      graph.add_edge(0, i, 1);
      // cout << "from 0, " << i << std::endl;
      for (int j = num_left + 1; j <= num_left + num_right; ++j) { // 4-7
        if (i == 1) {
          graph.add_edge(j, graph.size() - 1, 1);
          // cout << "to: " << j << ", " << graph.size() - 1 << std::endl;
        }
        int bit;
        cin >> bit;
        if (bit == 1) {
          // cout << i << ", " << j << std::endl;
          graph.add_edge(i, j, 1);
          edgeCount[i-1]++;
        }
      }
    }
    graph.edgeCount = edgeCount;
    // return adj_matrix;
    return graph;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  // vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
  vector<int> FindMatching(FlowGraph& graph) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int from = 0, to = graph.size() - 1;
    vector<int> matching = graph.find_matching(from, to);
  //   int num_left = adj_matrix.size();
  //   int num_right = adj_matrix[0].size();
  //   vector<bool> busy_right(num_right, false);
  //   for (int i = 0; i < num_left; ++i)
  //     for (int j = 0; j < num_right; ++j)
  //       if (matching[i] == -1 && !busy_right[j] && adj_matrix[i][j]) {
  //         matching[i] = j;
  //         busy_right[j] = true;
  //       }
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
