#include <bits/stdc++.h>
#include <sstream>
using namespace std;

struct Edge
{
  int from;
  int to;
};

struct ConvertHampathToSat
{
  int numVertices;
  vector<Edge> edges;

  ConvertHampathToSat(int n, int m) : 
    numVertices(n),
    edges(m)
  { }

  int toIndexVar(int x, int n) {
    return x * n - n + 1;
  }

  void printInfo(int numClauses, stringstream & ss) {
    // ss << "# " << numClauses << endl;
  }

  void printEquisatisfiableSatFormula()
  {
    stringstream ss;
    int n = numVertices;
    int numClauses = 0;
    int numVars = n * n;
    // Each vertex belongs to a path.
    // x[i][1] ... x[i][n]
    for (int i = 1; i <= numVars; i+=n)
    {
      for (int j = 0; j < n; j++)
        ss << i + j << " ";
      ss << "0\n";
      numClauses++;
      printInfo(numClauses, ss);
    }

    // Each vertex appears just once in a path.
    // -x[i][a] -x[i][b], for every combination of a,b where 1 <= a,b <= j and a != b
    for (int i = 1; i <= numVars; i+=n)
    {
      for (int j = 0; j < n - 1; j++)
      for (int k = j + 1; k < n; k++) {
        ss << -(i + j) << " " << -(i + k) << " 0\n";
        numClauses++;
        printInfo(numClauses, ss);
      }
    }

    // Each position in a path is occupied by some vertex.
    // x[1][j] ... x[n][j]
    // ss << "Each position in a path is occupied by some vertex.\n";
    for (int i = 1; i <= n; i++)
    {
      for (int j = 0; j < numVars; j+=n)
        ss << i + j << " ";
      ss << "0\n";
      numClauses++;
      printInfo(numClauses, ss);
    }

    // No two vertices occupy the same position of a path.
    // -x[a][j] -x[b][j], for every combination of a,b where 1 <= a,b <= i and a != b
    // ss << "No two vertices occupy the same position of a path.\n";
    for (int i = 1; i <= n; i++)
    {
      for (int j = i; j <= numVars - n; j+=n)
      for (int k = j + n; k <= numVars; k+=n) {
        ss << -j << " " << -(k) << " 0\n";
        numClauses++;
        printInfo(numClauses, ss);
      }
    }

    // Two successive vertices on a path must be connected by an edge.
    // (In other words, if there is no edge{i, j} in E, then for any k,
    // it cannot be the case that both x[i][k] and x[j][k+1] are True.)
    // -x[i][k] -x[j][k+1] for all (i,j) not in G and 1 <= k < n
    // ss << "edges\n";
    map<pair<int, int>, Edge> edgeMap;
    for (auto edge : edges)
    {
      int a = edge.from, b = edge.to;
      if (edge.from > edge.to)
      {
        a = edge.to;
        b = edge.from;
      }
      edgeMap[{a, b}] = edge;
    }
    for (int a = 1; a < n; a++) {
      for (int b = a+1; b <= n; b++) {
        if (edgeMap.find({a, b}) == edgeMap.end()) {
          int idx_a = toIndexVar(a, n);
          int idx_b = toIndexVar(b, n);
          for (int i = idx_a; i < idx_a + n; i++)
            for (int j = idx_b+1; j <= idx_b+n; j++) {
              ss << -i << " " << -j << " 0\n";
              numClauses++;
              printInfo(numClauses, ss);
            }
        }
      }
    }
    cout << numClauses << " " << numVars << endl;
    cout << ss.str();
  }
};

int main()
{
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  ConvertHampathToSat converter(n, m);
  for (int i = 0; i < m; ++i)
  {
    cin >> converter.edges[i].from >> converter.edges[i].to;
  }

  converter.printEquisatisfiableSatFormula();

  return 0;
}
