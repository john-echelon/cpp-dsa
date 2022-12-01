// Good job! (Max time used: 0.00/1.00, max memory used: 11366400/4294967296.)
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
};

struct ConvertGSMNetworkProblemToSat {
  int numVertices;
  vector<Edge> edges;

  ConvertGSMNetworkProblemToSat(int n, int m) :
    numVertices(n),
    edges(m)
  {  }

  void printEquisatisfiableSatFormula() {
    // This solution prints a simple satisfiable formula
    // and passes about half of the tests.
    // Change this function to solve the problem.
    stringstream ss;
    int numVars = numVertices * 3;
    int numClauses = edges.size() * 3 + (numVertices * 4);
    ss << numClauses << " " << numVars << endl;

    /*
    enforce the following constraints:
    1. every node is given at least one color,
    2. every node is given at most one color, and
    3. no two adjacent nodes are given the same color.
    */

    // Encode clauses for constraint 1
    // 1. every node is given at least one color
    for (int i = 1; i <= numVars; i+=3) {
      ss << i << " " << i + 1 << " " << i + 2 << " 0\n";
    }
    // Encode clauses for constraint 2
    // 2. every node is given at most one color
    for (int i = 1; i <= numVars; i+=3) {
      ss << -i << " " << -(i + 1) << " 0\n";
      ss << -i << " " << -(i + 2) << " 0\n";
      ss << -(i + 1) << " " << -(i + 2) << " 0\n";
    }
    // ss << "edges\n";
    // Encode clauses for constraint 3
    // 3. no two adjacent nodes are given the same color.
    for (auto edge : edges)
    {
      int from = 1 + edge.from * 3 - 3;
      int to = 1 + edge.to * 3 - 3;
      ss << -from << " " << -to << " 0\n";
      ss << -(from+1) << " " << -(to+1) << " 0\n";
      ss << -(from+2) << " " << -(to+2) << " 0\n";
    }
    cout << ss.str();
  }
};

int main() {
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  ConvertGSMNetworkProblemToSat converter(n, m);
  for (int i = 0; i < m; ++i) {
    cin >> converter.edges[i].from >> converter.edges[i].to;
  }

  converter.printEquisatisfiableSatFormula();

  return 0;
}
