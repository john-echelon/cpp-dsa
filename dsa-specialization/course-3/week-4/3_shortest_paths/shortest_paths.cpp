#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void bfs(vector<vector<int>> &adj, int s, vector<int> &shortest) {
  int n = adj.size();
  vector<long long> dist(n, std::numeric_limits<long long>::max());
  dist[s] = 0;
  queue<int> bfs_queue;
  bfs_queue.push(s);
  while(!bfs_queue.empty()) {
    int u = bfs_queue.front();
    bfs_queue.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (dist[v] == std::numeric_limits<long long>::max()) {
        bfs_queue.push(v);
        dist[v] = dist[u] + 1;
        shortest[v] = 0;
      }
    }
  }
}
// embellished bellman ford
void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &dist, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  int n = adj.size();
  dist[s] = 0;
  vector<int> prev(n, -1);
  // for all vertices
  reachable[s] = 1;

  std::set<int> a;
  // run bellman_ford |V| times
  for (int i = 0; i <= n; i++) {
    for (int u = 0; u < n; u++) {
      for (size_t j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        if (dist[u] == std::numeric_limits<long long>::max()) {
          continue;
        }
        reachable[v] = 1;
        long long distUV = dist[u] + cost[u][j];
        if (dist[v] > distUV) {
          dist[v] = distUV;
          prev[v] = u;
          // add all nodes relaxed on V-th iteration to set A. Put all nodes from A in queue Q
          if (i >= n && reachable[v] == 1) {
            a.insert(v);
          }
        }
      }
    }
  }
  // do breadth first search with queue Q and find all nodes reachable from A. All those nodes and only those can have infinite arbitrage. 
  for (auto it = a.begin(); it != a.end(); it++) {
    shortest[*it] = 0;
    bfs(adj, *it, shortest);
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
/*
Input:
6 7
1 2 10
2 3 5
1 3 100
3 5 7
5 4 10
4 3 -18
6 1 -1
1
Output:
0
10
-
-
-
*

Input:
5 4
1 2 1
4 1 2
2 3 2
3 1 -5
4
Output:
-
-
-
0
*
 */
