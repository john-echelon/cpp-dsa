#include <iostream>
#include <bits/stdc++.h> 
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct VertexInfo {
  int dist = INT_MAX;
  int prev = -1;
};
void bfs(vector<vector<int>> &adj, int s, VertexInfo info[]) {
  info[s].dist = 0;
  queue<int> bfs_queue;
  bfs_queue.push(s);
  while(!bfs_queue.empty()) {
    int u = bfs_queue.front();
    bfs_queue.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (info[v].dist == INT_MAX) {
        bfs_queue.push(v);
        info[v].dist = info[u].dist + 1;
        info[v].prev = u;
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
int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  struct VertexInfo info[adj.size()];
  bfs(adj, s, info);
  vector<int> path = reconstruct_path(s, t, info);
  // console debug
  // for (int i = 0; i < path.size(); i++) {
  //   std::cout << "path[i]: " << path[i] << " \n";
  // }
  if (info[path.front()].prev != s) {
    return -1;
  }
  return path.size();
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
