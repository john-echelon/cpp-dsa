#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<vector<int> > &adj, bool visited[]) {
  visited[v] = true;
  vector<int> neighbors = adj[v];  
  for (size_t i = 0; i < neighbors.size(); i++) {
    if (!visited[neighbors[i]]) {
      explore(neighbors[i], adj, visited);
    }
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  bool visited[adj.size()] = { false };
  explore(x, adj, visited);
  return (visited[x] && visited[y]);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
