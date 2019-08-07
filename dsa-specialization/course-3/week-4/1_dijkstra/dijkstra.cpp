#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;


class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const pair<int, int> &lhs, const pair<int, int> &rhs) const
  {
    if (reverse) return (lhs.second>rhs.second);
    else return (lhs.second<rhs.second);
  }
};
bool isReachable(int s, int u, vector<int> &dist, vector<int> &prev) {
  while (u != s && u != -1) {
    u = prev[u];
  }
  return u == s;
}
int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code here
  int n = adj.size();
  vector<int> dist(n, std::numeric_limits<int>::max());
  dist[s] = 0;
  vector<int> prev(n, -1);
  typedef std::priority_queue<pair<int,int>, std::vector<pair<int,int>>, mycomparison> minheap;
  minheap mypq(mycomparison(true)); 
  mypq.push(pair<int,int>(s, dist[s]));
  while (!mypq.empty())
  {
    pair<int,int> pairU = mypq.top();
    mypq.pop();
    int u = pairU.first;
    for (size_t i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      int distUV = dist[u] + cost[u][i];
      if (dist[v] > distUV) {
        dist[v] = distUV;
        prev[v] = u;
        mypq.push(pair<int,int>(v, dist[v]));
      }
    }
  }
  if (!isReachable(s, t, dist, prev))
    return -1;
  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
