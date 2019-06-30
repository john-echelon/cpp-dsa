#include <algorithm>
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

int dfs_custom_order(vector<vector<int>> &adj, VertexInfo info[], vector<int> & traverse_order, vector<int> & order) {
  int cc = 1;
  for (size_t i = 0; i < traverse_order.size(); i++) {
    int currentVertex = traverse_order[i];
    if (!info[currentVertex].visited) {
      explore(currentVertex, adj, info, cc, order);
      cc++;
    }
  }
  return cc - 1;
}
int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > reverse_adj) {
  struct VertexInfo reverse_info[reverse_adj.size()];
  vector<int> reverse_order;
  dfs(reverse_adj, reverse_info, reverse_order);
  // console info: post order of reverse dfs
  // cout << "\npost order of vertices\n";
  // for (size_t i = 0; i < adj.size(); i++) {
  //   cout << i+1 << " " << reverse_info[i].pre << " " << reverse_info[i].post << " " << reverse_info[i].ccNum << "\n";
  // }
  // console info: visit order of vertices
  // cout << "\nvisit order of vertices \n";
  // for (size_t i = 0; i < reverse_order.size(); i++) {
  //   cout << reverse_order[i] + 1 << " ";
  // }
  // console info: post order of reverse dfs
  vector<int> order;
  struct VertexInfo info[adj.size()];
  reset_clock_for_digraph();
  int result = dfs_custom_order(adj, info, reverse_order, order);
  // console info: post order of dfs
  // cout << "\npost order of vertices\n";
  // for (size_t i = 0; i < adj.size(); i++) {
  //   cout << i+1 << " " << info[i].pre << " " << info[i].post << " " << info[i].ccNum << "\n";
  // }
  // console info: visit order of vertices
  // cout << "\nvisit order of vertices \n";
  // for (size_t i = 0; i < order.size(); i++) {
  //   std::cout << order[i] + 1 << " ";
  // }
  // cout << "\n";
  //write your code here
  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > reverse_adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    reverse_adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, reverse_adj);
}
