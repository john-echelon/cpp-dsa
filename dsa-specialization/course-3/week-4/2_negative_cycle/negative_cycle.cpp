#include <iostream>
#include <vector>
#include <limits>

using std::vector;
struct VertexInfo {
  bool visited = false;
  int pre = 0;
  int post = 0;
  int ccNum = 1; //connected component number
};

int clock_for_digraph = 1;
static bool isCycle = false;
void reset_clock_for_digraph() {
  clock_for_digraph = 1;
}
void pre_visit(int v, VertexInfo info[]) {
  info[v].pre = clock_for_digraph++;
}
void post_visit(int v, VertexInfo info[]) {
  info[v].post = clock_for_digraph++;
}
void explore(int v, vector<vector<int>> & adj, VertexInfo info[], int cc, vector<int> & order) {
  VertexInfo & current = info[v];
  current.visited = true;
  pre_visit(v, info);
  current.ccNum = cc;
  vector<int> neighbors = adj[v];
  for (size_t i = 0; i < neighbors.size(); i++) {
    if (!info[neighbors[i]].visited) {
      explore(neighbors[i], adj, info, cc, order);
    }
    // Detect cycle if post for neighbor is greater or has not been posted yet.
    else if(info[v].post > info[neighbors[i]].post || info[neighbors[i]].post == 0) {
      // cout << "\n cycle on " << v + 1 << " " << neighbors[i] + 1 << "\n"; 
      isCycle = true;
    }
  }
  post_visit(v, info);
  // cout << "\nvisited " << v + 1;
  vector<int>::iterator iter = order.begin();
  order.insert(iter, v);
}

void dfs(vector<vector<int>> &adj, VertexInfo info[], vector<int> & order) {
  int cc = 1;
  for (size_t i = 0; i < adj.size(); i++) {
    if (!info[i].visited) {
      explore(i, adj, info, cc, order);
      cc++;
    }
  }
}

int check_negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int> &dist, vector<int> &prev) {
  // for (int u = 0; u < dist.size(); u++) {
  //   std::cout << "dist " << u+1 << " " << dist[u] << std::endl;
  // }
  //write your code here
  for (int u = 0; u < adj.size(); u++)
  {
    vector<int> edgesOfU = adj[u];
    // for all edges of v
    for (size_t j = 0; j < edgesOfU.size(); j++) {
      int v = edgesOfU[j];
      if (dist[u] == std::numeric_limits<int>::max()) {
        continue;
      }
      int distUV = dist[u] + cost[u][j];
      if (dist[v] > distUV) {
        return 1;
      }
    }
  }
  return 0;
}

void get_traverse_order(vector<vector<int>> &adj, vector<vector<int>> &reverse_adj, vector<int> &traverse_order) {
  //write your code here
  struct VertexInfo reverse_info[reverse_adj.size()];
  dfs(reverse_adj, reverse_info, traverse_order);
}
// using bellman ford
int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, VertexInfo info[], int s) {
  //write your code here
  int n = adj.size();
  vector<int> dist(n, std::numeric_limits<int>::max());
  dist[s] = 0;
  info[s].visited = true;
  vector<int> prev(n, -1);
  // for all vertices

  for (int i = 0; i < adj.size(); i++) {
    for (int u = 0; u < adj.size(); u++) {
      // for all edges of v
      for (size_t j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        info[v].visited = true;
        if (dist[u] == std::numeric_limits<int>::max()) {
          continue;
        }
        int distUV = dist[u] + cost[u][j];
        // std::cout << "u " << u+1 << " v " << v+1 << " dist[u] " << dist[u] << " cost[u][j] " << cost[u][j] << " dist[v] " << dist[v] << std::endl;
        if (dist[v] > distUV) {
          dist[v] = distUV;
          prev[v] = u;
        }
      }
    }
  }
  return check_negative_cycle(adj, cost, dist, prev);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > reverse_adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    reverse_adj[y - 1].push_back(x - 1);
    cost[x - 1].push_back(w);
  }
  vector<int> traverse_order;
  get_traverse_order(adj, reverse_adj, traverse_order);
  int cycles = 0;
  struct VertexInfo info[adj.size()];
  for (int i = 0; i < traverse_order.size(); i++) {
    if (!info[i].visited)
      cycles += negative_cycle(adj, cost, info, traverse_order[i]);
  }
  std::cout << (cycles > 0 ? 1 : 0);
}

/*
Input:
4 4
1 2 -5
4 1 2
2 3 2
3 1 1

Output:
1

Input:
10 9
1 2 1
6 7 1
8 9 1
9 10 1
3 4 1
7 8 1
4 5 1
5 6 1
2 3 1

Output:
0
*/