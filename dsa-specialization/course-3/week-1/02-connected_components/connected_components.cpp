#include <iostream>
#include <vector>

using std::vector;
using std::pair;
void explore(int v, vector<vector<int> > &adj, bool visited[], int ccNum[], int cc) {
  visited[v] = true;
  ccNum[v] = cc;
  vector<int> neighbors = adj[v];  
  for (size_t i = 0; i < neighbors.size(); i++) {
    if (!visited[neighbors[i]]) {
      explore(neighbors[i], adj, visited, ccNum, cc);
    }
  }
}

int dfs(vector<vector<int> > &adj) {
  bool visited[adj.size()] = { false };
  int ccNum[adj.size()] = { 1 };
  int cc = 1;
  for (size_t i = 0; i < adj.size(); i++) {
    if (!visited[i]) {
      explore(i, adj, visited, ccNum, cc);
      cc++;
    }

  }
  return cc;
}

int number_of_components(vector<vector<int> > &adj) {
  return dfs(adj) - 1;
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
  std::cout << number_of_components(adj);
}
