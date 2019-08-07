#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cout;

struct VertexInfo {
  bool visited = false;
  int pre = 0;
  int post = 0;
  int ccNum = 1; //connected component number
};
int clock_for_digraph = 1;
static bool isCycle = false;
void pre_visit(int v, VertexInfo info[]) {
  info[v].pre = clock_for_digraph++;
}
void post_visit(int v, VertexInfo info[]) {
  info[v].post = clock_for_digraph++;
}
void explore(int v, vector<vector<int>> & adj, VertexInfo info[], int cc) {
  VertexInfo & current = info[v];
  current.visited = true;
  pre_visit(v, info);
  current.ccNum = cc;
  vector<int> neighbors = adj[v];
  for (size_t i = 0; i < neighbors.size(); i++) {
    if (!info[neighbors[i]].visited) {
      explore(neighbors[i], adj, info, cc);
    }
    // Detect cycle if post for neighbor is less than post for v, or has not been posted yet.
    else if(info[neighbors[i]].post == 0) {
      // cout << "\n cycle on " << v + 1 << " " << neighbors[i] + 1 << "\n"; 
      isCycle = true;
    }
  }
  post_visit(v, info);
  // cout << "\nvisited " << v + 1; 
}

void dfs(vector<vector<int>> &adj, VertexInfo info[]) {
  int cc = 1;
  for (size_t i = 0; i < adj.size(); i++) {
    if (!info[i].visited) {
      explore(i, adj, info, cc);
      cc++;
    }
  }
}
int acyclic(vector<vector<int> > &adj) {
  //write your code here
  struct VertexInfo info[adj.size()];
  dfs(adj, info);
  // cout << std::endl;
  // for (size_t i = 0; i < adj.size(); i++) {
  //   cout << i+1 << " " << info[i].pre << " " << info[i].post << " " << info[i].ccNum << "\n";
  // }
  return isCycle;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
