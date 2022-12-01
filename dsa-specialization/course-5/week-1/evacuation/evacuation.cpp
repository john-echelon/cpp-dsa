// Good job! (Max time used: 0.00/1.00, max memory used: 9232384/536870912.)
#include <algorithm>
#include <bits/stdc++.h> 
#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

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

public:
    explicit FlowGraph(size_t n): graph(n) {}

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
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    flow = graph.max_flow(from, to);
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
