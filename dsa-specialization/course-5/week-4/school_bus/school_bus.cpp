// Good job! (Max time used: 0.03/1.00, max memory used: 12677120/2147483648.)
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<vector<int>> Matrix;

const int INF = 1e9;

Matrix read_data() {
  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;
  Matrix graph(vertex_count, vector<int>(vertex_count, INF));
  for (int i = 0; i < edge_count; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;
    --from, --to;
    graph[from][to] = graph[to][from] = weight;
  }
  return graph;
}

inline pair<int, vector<int>> get_mask(const vector<bool> &p, int s) {
  int mask = 0;
  int n = p.size();
  vector<int> subset(s);
  for (size_t i = 0; i < n; i++)
  {
    if (p[i]) {
      mask += (1 << n - 1 - i);
      subset[--s] = n - i;
    }
  }
  return {mask, subset};
}

std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
  // This solution tries all the possible sequences of stops.
  // It is too slow to pass the problem.
  // Implement a more efficient algorithm here.
  size_t n = graph.size();
  int maskSize = 1 << n;
  int memo[maskSize][n + 1];
  for (int i = 0; i < maskSize; i++)
  for (int j = 0; j <= n; j++)
    memo[i][j] = INF;
  memo[1][1] = 0;
  vector<bool> p(n, 0);
  p[n - 1] = 1;
  for (size_t s = 2; s <= n; ++s)
  {
    // generate permutations of subsets of size s
    for (size_t i = 0; i < s - 1; ++i)
      p[i] = true;
    // cout << "s " << s << endl;
    do
    {
      // cout << "mask(2) ";
      // for (size_t i = 0; i < p.size(); ++i)
      //   cout << p[i];
      // cout << endl;
      pair<int, vector<int>> info = get_mask(p, s);
      int mask = info.first;
      vector<int> subset = info.second;
      // cout << "mask(10) " << mask << endl;

      // cout << "subset: ";
      // for (size_t i = 0; i < subset.size(); ++i)
      //   cout << subset[i] << " ";
      // cout << endl;
      for (int i = 0; i < subset.size(); i++)
        for (int j = 0; j < subset.size(); j++)
        {
          if (subset[i] == 1 || subset[j] == subset[i])
            continue;
          int v = subset[i];
          int w = subset[j];
          // cout << "mask " << mask << " (" << v << "," << w << ")" << endl;
          memo[mask][v] = min(memo[mask][v], memo[mask & ~(1 << v - 1)][w] + graph[v - 1][w - 1]);
        }
    } while (std::prev_permutation(p.begin(), p.end() - 1));
  }

  vector<int> best_path;
  int best_ans = INF;
  int next_ans = INF;
  int next = 1;

  for (size_t i = 2; i <= n; i++) {
    best_ans = min(memo[maskSize - 1][i] + graph[i - 1][0], best_ans);
  }
  // for (size_t i = 1; i <= n; i++)
  //   cout << i << " " << memo[maskSize - 1][i] << " w " << graph[i - 1][0] << endl;
  if (best_ans == INF)
    return {-1, best_path};
  next_ans = best_ans;
  int nextMask = maskSize - 1;
  do
  {
    for (size_t i = 1; i <= n; i++)
    {
      if (i == next)
        continue;
      int dist = memo[nextMask][i] + graph[i - 1][next - 1];
      if (dist == next_ans)
      {
        next = i;
        next_ans = memo[nextMask][i];
        best_path.emplace_back(next);
        nextMask &= ~(1 << next - 1);
        break;
      }
    }
  } while (next != 1);

  std::reverse(best_path.begin(), best_path.end());
  return std::make_pair(best_ans, best_path);
}

void print_answer(const std::pair<int, vector<int> >& answer) {
  std::cout << answer.first << "\n";
  if (answer.first == -1)
    return;
  const vector<int>& path = answer.second;
  for (size_t i = 0; i < path.size(); ++i)
    std::cout << path[i] << " ";
  std::cout << "\n";
}

int main() {
  print_answer(optimal_path(read_data()));
  return 0;
}
