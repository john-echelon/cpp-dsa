// Good job! (Max time used: 0.01/1.00, max memory used: 13119488/2147483648.)
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

struct Clause {
  int firstVar;
  int secondVar;
};

struct SatFormula {
  int numVars;
  vector<Clause> clauses;
};

struct ConvertGSMNetworkProblemToSat
{
  int numVertices;
  string colors;
  ConvertGSMNetworkProblemToSat(int n, string c) : numVertices(n), colors(c)
  {}

  SatFormula printEquisatisfiableSatFormula(vector<pair<int,int>> & edges)
  {
    // This solution prints a simple satisfiable formula
    // and passes about half of the tests.
    // Change this function to solve the problem.
    SatFormula formula;
    stringstream ss;
    int numVars = numVertices * 3;
    formula.numVars= numVars;

    /*
    enforce the following constraints:
    1. every node is given at least one color,
    2. every node is given at most one color, and
    3. no two adjacent nodes are given the same color.
    */

    // Encode clauses for constraint 1
    // 1. every node is given at least one color
    // ss << "C1:\n";
    for (int i = 1; i <= numVars; i += 3)
    {
      int varIdx = 0;
      if (colors[(i + 3) / 3 - 1] == 'R')
        varIdx = i;
      if (colors[(i + 3) / 3 - 1] == 'G')
        varIdx = i + 1;
      if (colors[(i + 3) / 3 - 1] == 'B')
        varIdx = i + 2;
      
      Clause c;
      c.firstVar = -varIdx;
      c.secondVar = -varIdx;
      formula.clauses.emplace_back(c);
      // ss << c.firstVar << " " << c.secondVar << " 0\n";
    }
    // Encode clauses for constraint 2
    // 2. every node is given at most one color
    // ss << "C2:\n";
    for (int i = 1; i <= numVars; i+=3) {
      Clause c;
      if (colors[(i + 3) / 3 - 1] == 'R')
      {
        c.firstVar = i + 1;
        c.secondVar = i + 2;
      }
      if (colors[(i + 3) / 3 - 1] == 'G')
      {
        c.firstVar = i;
        c.secondVar = i + 2;
      }
      if (colors[(i + 3) / 3 - 1] == 'B')
      {
        c.firstVar = i;
        c.secondVar = i + 1;
      }
      formula.clauses.emplace_back(c);
      ss << c.firstVar << " " << c.secondVar << " 0\n";
      c.firstVar *= -1;
      c.secondVar *= -1;
      formula.clauses.emplace_back(c);
      ss << c.firstVar << " " << c.secondVar << " 0\n";
    }
    // ss << "edges\n";
    // Encode clauses for constraint 3
    // 3. no two adjacent nodes are given the same color.
    // ss << "C3:\n";
    for (auto edge : edges)
    {
      // ss << "edge " << edge.first << ", " << edge.second << endl;
      int from = 1 + edge.first * 3 - 3;
      int to = 1 + edge.second * 3 - 3;
      Clause c;
      c.firstVar = -from;
      c.secondVar = -to;
      formula.clauses.emplace_back(c);
      // ss << c.firstVar << " " << c.secondVar << " 0\n";

      c.firstVar = -(from + 1);
      c.secondVar = -(to + 1);
      formula.clauses.emplace_back(c);
      // ss << c.firstVar << " " << c.secondVar << " 0\n";

      c.firstVar = -(from + 2);
      c.secondVar = -(to + 2);
      formula.clauses.emplace_back(c);
      // ss << c.firstVar << " " << c.secondVar << " 0\n";
    }
    // cout << ss.str();
    return formula;
  }
};

struct TwoSatisfiability {
  int numVars;

  TwoSatisfiability(int n) :
      numVars(n)
  {  }

  struct VertexInfo {
    bool visited = false;
    int pre = 0;
    int post = 0;
    int ccNum = 1; //connected component number
    int originalIdx = 0;
  };

  int clock_for_digraph = 1;
  bool isCycle = false;

  void reset_clock_for_digraph() {
    clock_for_digraph = 1;
  }
  void pre_visit(int v, vector<VertexInfo> & info) {
    info[v].pre = clock_for_digraph++;
  }
  void post_visit(int v, vector<VertexInfo> & info) {
    info[v].post = clock_for_digraph++;
  }
  void explore(int v, vector<vector<int>> & adj, vector<VertexInfo> & info, int cc, vector<int> & order) {
    stack<int> stack;
    stack.push(v);
    while (!stack.empty()) {
      int i = stack.top();
      VertexInfo &current = info[i];
      if (!current.visited) {
        info[i].originalIdx = i;
        current.visited = true;
        pre_visit(i, info);
        current.ccNum = cc;
      }
      vector<int> neighbors = adj[i];
      bool hasPushed = false;
      for (size_t j = 0; j < neighbors.size(); j++)
      {
        if (!info[neighbors[j]].visited)
        {
          stack.push(neighbors[j]);
          hasPushed = true;
          break;
        }
        // Detect cycle if post is greater than neighbor or has not been posted yet.
        else if(info[i].post > info[neighbors[j]].post || info[neighbors[j]].post == 0) {
          // cout << "\n cycle on " << v + 1 << " " << neighbors[i] + 1 << "\n"; 
          isCycle = true;
        }
      }
      if (!hasPushed) {
        stack.pop();
        post_visit(i, info);
        // cout << "\nvisited " << i;
        // The code prev code listed here was the bottle neck for TC17
        // vector<int>::iterator iter = order.begin();
        // order.insert(iter, i);
        order.emplace_back(i);
      }
    }
  }

  void dfs(vector<vector<int>> &adj, vector<VertexInfo> & info, vector<int> & order) {
    int cc = 1;
    for (size_t i = 0; i < adj.size(); i++) {
      if (!info[i].visited) {
        explore(i, adj, info, cc, order);
        cc++;
      }
    }
  }

  int dfs_custom_order(vector<vector<int>> &adj, vector<VertexInfo> & info, vector<int> & traverse_order, vector<int> & order) {
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
  int number_of_strongly_connected_components(vector<vector<int>> adj, vector<vector<int> > reverse_adj, 
    vector<VertexInfo> & info, vector<int> & order) {
    vector<VertexInfo> reverse_info(reverse_adj.size(), VertexInfo());
    vector<int> reverse_order;
    dfs(reverse_adj, reverse_info, reverse_order);
    reverse(reverse_order.begin(), reverse_order.end());
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
    reset_clock_for_digraph();
    int result = dfs_custom_order(adj, info, reverse_order, order);
    reverse(order.begin(), order.end());
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
    return result;
  }
  int toCnfVarIdx(int i) {
    if (i % 2)
      return -(((i-1) / 2) + 1);
    return i / 2 + 1;
  }

  int toVertexIdx(int i) {
    if (i < 0)
      return (2 * (abs(i)-1)) + 1;
    return 2 * (abs(i)-1);
  }

  bool compareInfo(VertexInfo i1, VertexInfo i2) {
    return (i1.ccNum < i2.ccNum);
  }

  bool isSatisfiable(vector<Clause> & clauses, vector<int>& result) {
    // Construct implication graph G
    vector<vector<int> > adj(numVars*2, vector<int>());
    vector<vector<int> > reverse_adj(numVars*2, vector<int>());
    for (auto clause: clauses) {
      // ~x->y
      // e.g. clause ~1, 2 = 1 -> 2
      adj[toVertexIdx(-clause.firstVar)].push_back(toVertexIdx(clause.secondVar));
      reverse_adj[toVertexIdx(clause.secondVar)].push_back(toVertexIdx(-clause.firstVar));
      // ~y->x
      // e.g. clause ~2, 1 = 3 -> 0
      adj[toVertexIdx(-clause.secondVar)].push_back(toVertexIdx(clause.firstVar));
      reverse_adj[toVertexIdx(clause.firstVar)].push_back(toVertexIdx(-clause.secondVar));
      // cout << "clause " << clause.firstVar << " " << clause.secondVar << ": " << toVertexIdx(clause.firstVar) << "->" << toVertexIdx(clause.secondVar) << endl;
      // cout << "clause " << -clause.secondVar << " " << clause.firstVar << ": " << toVertexIdx(-clause.secondVar) << "->" << toVertexIdx(clause.firstVar) << endl;
      // cout << "cnf " << toCnfVarIdx(toVertexIdx(clause.firstVar)) << " " << toCnfVarIdx(toVertexIdx(clause.secondVar)) << endl;
      // cout << "cnf " << toCnfVarIdx(toVertexIdx(-clause.secondVar)) << " " << toCnfVarIdx(toVertexIdx(clause.firstVar)) << endl;
    }

    // Find SCC's of G
    vector<VertexInfo> info(adj.size(), VertexInfo());
    vector<int> order;
    int ccNum = number_of_strongly_connected_components(adj, reverse_adj, info, order);
    // cout << "order\n";
    // for (auto i : order)
    // {
    //   cout << i << " ";
    // }
    // cout << endl;
    for (int i = 0; i < info.size(); i+=2)
    {
      // return unsatisfiable if x and ~x lie in the same SCC of G
      if(info[i].ccNum == info[i+1].ccNum) {
        return false;
      }
    }

    // For all SCC's in C in reverse order:
    // if literals of C are not assigned yet:
    //   set all of them to 1
    //   set their negations to 0
    vector<bool> assignedLiterals(numVars, false);
    int assignedCount = 0;
    for (int j = order.size() - 1; j >= 0; j--)
    {
      int i = order[j];
      // cout << "vertex " << info[i].originalIdx << " cnf " << toCnfVarIdx(info[i].originalIdx) << " " << info[i].pre << " " << info[i].post << " " << info[i].ccNum << "\n";
      int varIdx = toCnfVarIdx(info[i].originalIdx);
      if (!assignedLiterals[abs(varIdx) - 1])
      {
        // cout << "assigned " << abs(varIdx) - 1 << " " << varIdx << endl;
        result[abs(varIdx) - 1] = varIdx < 0 ? 0 : 1;
        assignedLiterals[abs(varIdx) - 1] = true;
        assignedCount++;
      }
      if (assignedCount == assignedLiterals.size())
        break;
    }
    return true;
  }
};
/*
  Arguments:
    * `n` - the number of vertices.
    * `edges` - list of edges, each edge is a pair (u, v), 1 <= u, v <= n.
    * `colors` - string consisting of `n` characters, each belonging to the set {'R', 'G', 'B'}.
  Return value:
    * If there exists a proper recoloring, return value is a string containing new colors, similar to the `colors` argument.
    * Otherwise, return value is an empty string.
*/
string assign_new_colors(int n, vector<pair<int, int>> edges, string colors) {
  ConvertGSMNetworkProblemToSat converter(n, colors);

  SatFormula formula = converter.printEquisatisfiableSatFormula(edges);

  TwoSatisfiability twoSat(formula.numVars);
  vector<int> result(formula.numVars);

  if (twoSat.isSatisfiable(formula.clauses, result)) {
    // cout << "SATISFIABLE" << endl;
    string new_colors;
    for (int i = 1; i <= formula.numVars; ++i) {
      if (result[i-1]) {
        new_colors.push_back("BRG"[(i % 3)]);
      }
    }
    return new_colors;
  }
  else
  {
    return "";
  }
  return "";
}

int main() {
  int n, m;
  cin >> n >> m;
  string colors;
  cin >> colors;
  vector<pair<int, int> > edges;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    edges.push_back(make_pair(u, v));
  }
  string new_colors = assign_new_colors(n, edges, colors);
  if (new_colors.empty()) {
    cout << "Impossible";
  } else {
    cout << new_colors << endl;
  }
}
