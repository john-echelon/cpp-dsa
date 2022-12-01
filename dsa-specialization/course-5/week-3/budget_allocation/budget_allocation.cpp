/*
Failed case #10/70: Wrong answer

 (Time used: 0.00/2.00, memory used: 16314368/2147483648.)
*/
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
    int numberVars;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {
    numberVars = m;
    }

    void printEquisatisfiableSatFormula() {
      if(A.size() == 0) {
        cout << "1 " << numberVars << endl;
        cout << "1 0" << endl;
        return;
      }
      stringstream ss;
      int numVars = A[0].size();
      int numClauses = 0;
      for (int i = 0; i < A.size(); i++)
      {
        int numConstraintClauses = 0;
        // ss << "Constraint " << i + 1 << endl;
        // find non-zero coefficients together with their indices
        vector<int> nzCoefficientIdxs;
        for (int j = 0; j < A[i].size(); j++)
        {
          if (A[i][j] != 0)
            nzCoefficientIdxs.emplace_back(j);
        }

        // No solution if all coefficients are 0 and b < 0.
        if (nzCoefficientIdxs.size() == 0 && b[i] < 0) {
          numClauses = 0;
          break;
        }
        // build truth table via powerset to find an assignment that violates the constraint
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
          bool violated = (sum > b[i]);
          if (violated) {

            for (int j = 0; j < A[i].size(); j++)
            {
              if (A[i][j] == 0){
                continue;
                // ss << -(j + 1) << " ";
              }
              else if (temp[j] == 1)
                ss << -(j + 1) << " ";
              else 
                ss << (j + 1) << " ";
            }
            ss << "0\n";
            numConstraintClauses++;
          }
        }
        if (numConstraintClauses == 0) {
          for (int j = 0; j < A[i].size(); j++)
          {
            if (A[i][j] == 0)
              continue;
            // ss << -(j + 1) << " ";
            else 
              ss << (j + 1) << " ";
          }
          ss << "0\n";
          numConstraintClauses++;
        }
        numClauses += numConstraintClauses;
      }

      if (numClauses == 0) {
        cout << "1 " << numVars << endl;
        cout << "1 -1 0\n";
      }
      else {
        cout << numClauses << " " << numVars << endl;
        cout << ss.str();
      }
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
        if (converter.A[i][j] < 0)
          converter.A[i][j] = -1;
        if (converter.A[i][j] > 0)
          converter.A[i][j] = 1;
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
