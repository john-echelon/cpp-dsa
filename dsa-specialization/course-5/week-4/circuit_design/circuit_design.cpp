#include <bits/stdc++.h>
using namespace std;

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
struct Clause {
    int firstVar;
    int secondVar;
};

struct TwoSatisfiability {
    int numVars;
    vector<Clause> clauses;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        clauses(m)
    {  }

    bool isSatisfiable(vector<int>& result) {
        // This solution tries all possible 2^n variable assignments.
        // It is too slow to pass the problem.
        // Implement a more efficient algorithm here.
        for (int mask = 0; mask < (1 << numVars); ++mask) {
            cout << "mask " << mask << endl;
            for (int i = 0; i < numVars; ++i)
            {
                result[i] = (mask >> i) & 1;
                cout << "result[" << i << "]" << result[i] << endl;
            }

            bool formulaIsSatisfied = true;

            for (const Clause& clause: clauses) {
                bool clauseIsSatisfied = false;
                if (result[abs(clause.firstVar) - 1] == (clause.firstVar < 0)) {
                    clauseIsSatisfied = true;
                }
                if (result[abs(clause.secondVar) - 1] == (clause.secondVar < 0)) {
                    clauseIsSatisfied = true;
                }
                if (!clauseIsSatisfied) {
                    formulaIsSatisfied = false;
                    break;
                }
            }

            if (formulaIsSatisfied) {
                return true;
            }
        }
        return false;
    }
};

int toVertex(int i) {
  if (i < 0)
    return (2 * abs(i)) + 1;
  return 2 * abs(i);
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<int> > adj(n*2, vector<int>());
    vector<vector<int> > reverse_adj(n*2, vector<int>());
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
        // x->y
        adj[toVertex(twoSat.clauses[i].firstVar)].push_back(toVertex(twoSat.clauses[i].secondVar));
        reverse_adj[toVertex(twoSat.clauses[i].secondVar)].push_back(toVertex(twoSat.clauses[i].firstVar));
        adj[toVertex(twoSat.clauses[i].secondVar)].push_back(toVertex(twoSat.clauses[i].firstVar));
        reverse_adj[toVertex(twoSat.clauses[i].firstVar)].push_back(toVertex(twoSat.clauses[i].secondVar));
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
