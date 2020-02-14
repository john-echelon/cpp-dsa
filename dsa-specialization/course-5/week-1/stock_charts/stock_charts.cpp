#include <algorithm>
#include <bits/stdc++.h> 
#include <iostream>
#include <vector>
#include <memory>
#include <queue>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

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
    explicit FlowGraph(size_t n): graph(n) {}
    void add_edge(int from, int to, int capacity) {
        // cout << "add_edge " << from << ": " << to << "\n";
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
      // const vector<size_t> & adj = get_ids(0);
      // for (int id: adj) {
      //   const Edge & e = get_edge(id);
      //   cout << "from: " << e.from << " to: " << e.to << " cap " << e.capacity << " flow " << e.flow << "\n";
      // }
      return flow;
    }
};

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }
  
  int convertRight(int leftId, int num_stocks) {
    return leftId + num_stocks;
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    // Replace this incorrect greedy algorithm with an
    // algorithm that correctly finds the minimum number
    // of charts on which we can put all the stock data
    // without intersections of graphs on one chart.

    int num_stocks = stock_data.size();
    // Vector of charts; each chart is a vector of indices of individual stocks.
    size_t t = num_stocks * 2 + 2;
    FlowGraph graph(t);
    for (int i = 1; i <= num_stocks; ++i) {
      graph.add_edge(0, i, 1);
      graph.add_edge(convertRight(i, num_stocks), t -1, 1);
    }

    vector<vector<int>> charts;
    for (int i = 0; i < stock_data.size(); ++i) {
      bool added = false;
      for (int j = 0; j < stock_data.size(); ++j) {
        if (compare(stock_data[i], stock_data[j])) {
          graph.add_edge(i + 1, convertRight(j + 1, num_stocks), 1);
        }
      }
    }
    int from = 0, to = graph.size() - 1;
    int maxFlow = graph.max_flow(from, to);
    // cout << "maxFlow " << maxFlow << "\n";
    return num_stocks - maxFlow;
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] <= stock2[i])
        return false;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
