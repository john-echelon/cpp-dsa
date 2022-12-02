// Good job! (Max time used: 0.01/2.00, max memory used: 16236544/2147483648.)
#include <ios>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


vector<vector<int> > PowerSet(int n, int setSize)
{
  vector<vector<int>> subset;
  subset.push_back(vector<int>());
  for (long i = 0; i < n; i++)
  {
    vector< vector<int> > temp = subset;  //making a copy of given 2-d vector.
    for (int j = 0; j < temp.size(); j++)
        temp[j].push_back(i);   // adding set[i] element to each subset of subsetTemp. like adding {2}(in 2nd iteration  to {{},{1}} which gives {{2},{1,2}}.

    for (int j = 0; j < temp.size(); j++)
        subset.push_back( temp[j] ); 
  }
  vector<vector<int>> subsets;
  for (auto i : subset)
  {
    if (i.size() <= setSize)
        subsets.emplace_back(i);
  }

  return subsets;
}
struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {}

    void printEquisatisfiableSatFormula() {
      stringstream ss;
      int numVars = A[0].size();
      int numClauses = 0;
      for (int i = 0; i < A.size(); i++)
      {
        int numConstraintClauses = 0;
        // Find non-zero coefficients together with their indices
        vector<int> nzCoefficientIdxs;
        for (int j = 0; j < A[i].size(); j++)
        {
          if (A[i][j] != 0)
            nzCoefficientIdxs.emplace_back(j);
        }

        // Build truth table via powerset to find an assignment that violates the constraint
        vector<vector<int>> pset = PowerSet(nzCoefficientIdxs.size(), 3);
        for (auto set : pset) {
          vector<int> temp(A[i].size(), 0);
          for (int k = 0; k < set.size(); k++)
            temp[nzCoefficientIdxs[set[k]]] = 1;
          int sum = 0;
          for (int j = 0; j < A[i].size(); j++)
          {
            if (temp[j] == 1)
              sum += A[i][j];
          }
          // if constraint is violated then negate indices, add to clause
          if (sum > b[i]) {
            bool addClause = false;
            for (int j = 0; j < A[i].size(); j++)
            {
              if (A[i][j] == 0){
                continue;
              }
              else if (temp[j] == 1)
                ss << -(j + 1) << " ";
              else 
                ss << (j + 1) << " ";
              addClause = true;
            }
            if (addClause) {
              ss << "0\n";
              numClauses++;
            }
          }
        }
      }

      if (numClauses == 0) {
        ss << "1 -1 0\n";
        numClauses++;
      }
      cout << numClauses << " " << numVars << endl;
      cout << ss.str();
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
