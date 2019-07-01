#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h> 

using std::vector;
using std::queue;

struct VertexInfo {
  int dist = INT_MAX;
  int prev = -1;
};
void bfs(vector<vector<int>> &adj, int s, VertexInfo info[], bool & isBipartite) {
  isBipartite = true;
  info[s].dist = 0;
  queue<int> bfs_queue;
  bfs_queue.push(s);
  while(!bfs_queue.empty() && isBipartite) {
    int u = bfs_queue.front();
    bfs_queue.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (info[v].dist == INT_MAX) {
        bfs_queue.push(v);
        info[v].dist = info[u].dist + 1;
        info[v].prev = u;
      } else if (info[u].dist % 2 == info[v].dist % 2) {
        // std:: cout << "found vertices with same color; not bipartite!";
        isBipartite = false;
        break;
      }
    }
  }
}

vector<int> reconstruct_path(int s, int u, VertexInfo info[]) {
  vector<int> result;
  while (u != s && u != -1) {
    result.insert(result.begin(), u);
    u = info[u].prev;
    // if (u == -1)
    //   std::cout << "\nNo path!\n";
  }
  return result;
}
int bipartite(vector<vector<int> > &adj, int s) {
  //write your code here
  struct VertexInfo info[adj.size()];
  bool isBipartite = false;
  bfs(adj, s, info, isBipartite);
  // vector<int> path = reconstruct_path(s, t, info);
  // console debug
  // for (int i = 0; i < path.size(); i++) {
  //   std::cout << "path[i]: " << path[i] << " \n";
  // }
  // if (info[path.front()].prev != s) {
  //   return -1;
  // }
  return isBipartite;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  int x, y;
  for (int i = 0; i < m; i++) {
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj, adj[x - 1].front());
}
