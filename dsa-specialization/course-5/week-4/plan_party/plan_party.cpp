// Good job! (Max time used: 0.12/1.00, max memory used: 25198592/2147483648.)
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct VertexInfo {
  int dist = numeric_limits<int>::max();
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
      if (info[v].dist == numeric_limits<int>::max()) {
        bfs_queue.push(v);
        info[v].dist = info[u].dist + 1;
        info[v].prev = u;
      }
    }
  }
}
struct Vertex
{
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree(int & s) {
    int vertices_count;
    std::cin >> vertices_count;
    vector<vector<int> > adj(vertices_count, vector<int>());
    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    if (vertices_count == 1)
        return tree;
    for (int i = 1; i < vertices_count; ++i)
    {
        int from, to, weight;
        std::cin >> from >> to;
        if (i == 1)
            s = from - 1;
        adj[from - 1].push_back(to - 1);
        adj[to - 1].push_back(from - 1);
    }

    struct VertexInfo info[adj.size()];
    // build parent-child relations via bfs
    bfs(adj, s, info);

    // Now build tree based on parent-child relations
    for (int i = 0; i < adj.size(); i++)
    {
        // cout << "i " << i + 1 << " prev " << info[i].prev << " dist " << info[i].dist << endl ;
        if (info[i].prev == -1) {
            continue;
        }
        int from = info[i].prev;
        int to = i;
        tree[from].children.push_back(to);
    }
    return tree;
}

int dfs(const Graph &tree, int v, int parent, vector<int> & buffer) {
    if (buffer[v] == numeric_limits<int>::max()) {
        if (tree[v].children.empty())
        {
            buffer[v] = tree[v].weight;
        }
        else
        {
            int m1 = tree[v].weight;
            for (int child : tree[v].children) {
                for (int grand : tree[child].children)
                    m1+= dfs(tree, grand, child, buffer);
            }
            int m0 = 0;
            for (int child : tree[v].children)
                m0+= dfs(tree, child, parent, buffer);
            buffer[v] = max(m0, m1);
        }
    }
    return buffer[v];
}

int MaxWeightIndependentTreeSubset(const Graph &tree, int s) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    if (size == 1)
        return tree[0].weight;
    vector<int> buffer(size, numeric_limits<int>::max());
    int sum = dfs(tree, s, -1, buffer);
    return sum;
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    /*
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
    */

    // Here begins the solution
    int s;
    Graph tree = ReadTree(s);
    int weight = MaxWeightIndependentTreeSubset(tree, s);
    std::cout << weight << std::endl;
    return 0;
}
