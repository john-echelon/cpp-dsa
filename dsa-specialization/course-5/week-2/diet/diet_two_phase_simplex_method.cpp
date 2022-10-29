#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int PRECISION = 10;
typedef vector<vector<double>> matrix;
const double CALC_PRECISION = 0.000000001;

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

void PrintColumn(const vector<double> &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << "\t";
}

void PrintMatrix(const matrix &m, vector<double> &b) {
    int rSize = m.size();
    int cSize = m[0].size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < rSize; ++row) {
      for (int col = 0; col < cSize; ++col) {
        std::cout << m[row][col] << "\t";
      }
      std::cout << b[row] << "\t";
      std::cout << std::endl;
    }
}
void PrintTableau(matrix &a, vector<double> &b, vector<double> &c, double &z) {
  PrintMatrix(a, b);
  PrintColumn(c);
  cout << z << "\n";
  cout << "--------------------------------\n";
}
void ProcessPivotElement(matrix &a, vector<double> &b, vector<double> &c, double &z, const Position &pivot) {
    // Write your code here
    // Row reduce pivot row by pivot value;
    double pivot_value = a[pivot.row][pivot.column];
    if (pivot_value == 0) return;
    int v_size = a.size();
    int cSize = a[0].size();
    double ctargetElement = c[pivot.column];
    for (int j = 0; j < cSize; j++) {
      a[pivot.row][j] /= pivot_value;
      // Also while were at it: Row reduce bottom row, based on pivot column of source element scaled by target element
      c[j] += (a[pivot.row][j] * ctargetElement * -1);
    }
    b[pivot.row] /= pivot_value;
    z += (b[pivot.row] * ctargetElement * -1);
    // For all appropriate non-pivot rows...
    for (int i = 0; i < v_size; i++) {
      double targetElement = a[i][pivot.column];
      if (targetElement == 0 || i == pivot.row)
        continue;
      // Subtract row by pivot row
      for (int j = 0; j < cSize; j++) {
        a[i][j] += (a[pivot.row][j] * targetElement * -1);
      }
      b[i] += (b[pivot.row] * targetElement * -1);
    }

}

bool hasPivotColumn(vector<double> &c) {
  return c[std::min_element(c.begin(), c.end()) - c.begin()] < 0;
}

int getPivotRow(matrix &a, vector<double> &b, int pivotColumn) {
  int rSize = a.size();
  double enteringRatios = numeric_limits<double>::max();
  int pivotRow = -1;
  for (int i = 0; i < rSize; ++i) {
    // cout << "values: " << b[i] << "/" << a[i][pivotColumn] << "\n";
    if (a[i][pivotColumn] == 0)
      continue;
    double val = b[i] / a[i][pivotColumn];
    // cout << "pivot " << i << ", " << pivotColumn << endl;
    // cout << "entering ratio " << enteringRatios << endl;
    // cout << "calc ratio: " << b[i] << "/" << a[i][pivotColumn] << ": " << val << endl;
    if (val < enteringRatios && val >= 0)
    {
      // if (std::abs(val - enteringRatios) < CALC_PRECISION)
      //   continue;
      enteringRatios = val;
      pivotRow = i;
      // cout << "update pivot " << i << ", " << pivotColumn << endl;
    }
  }
  return pivotRow;
}

vector<double> getSolution(int numVars, vector<double> & trace, vector<double> &b) {
  vector<double> solution = vector<double>(numVars, 0);
  // cout << "numVars " << numVars << " trace " << trace.size() << " b " << b.size() << endl;
  // get solutions
  for (int row = 0; row < b.size(); row++) {
    int col = trace[row];
    solution[col] = b[row];
  }
  return solution;
}
bool checkConstraints(int n, int m, matrix &A_original, vector<double> &b_original, vector<double> &solutions) {
  for (int i = 0; i < n; i++) {
    double lhsEq = 0;
    for (int j = 0; j < m; j++) {
      lhsEq += (A_original[i][j] * solutions[j]);
    }
    if (lhsEq < b_original[i] && b_original[i] <0)
      return false;
  }
  return true;
}
Position getPivotElement(matrix &a, vector<double> &b, vector<double> &c) {
  Position pivot(-1, 0);
  double minValue = c[std::min_element(c.begin(), c.end()) - c.begin()];
  // cout << "minValue " << minValue << "\n";
  if (minValue > 0) {
    pivot.column = 0;
    pivot.row = getPivotRow(a, b, pivot.column);
  }
  else {
    for(int i = 0; i < c.size(); i++) {
      if (c[i] == minValue) {
        pivot.column = i;
        pivot.row = getPivotRow(a, b, pivot.column);
        if (pivot.row != -1)
          break;
      }
    }
  }
  return pivot;
}
pair<int, vector<double>> solve_diet_problem(
    int n,
    int m,
    matrix &a,
    vector<double> &b,
    vector<double> c,
    vector<double> b_original,
    vector<double> &non_basic_vars,
    double z = 0
    ) {

  // Write your code here
  int mPlusSlack = n + m;
  matrix A_original(n, vector<double>(mPlusSlack, 0));
  for (int i = 0; i < n; i++) {
    A_original[i]= vector<double>(a[i]);
  }
  vector<double> pivot_trace(c.size(), -1);
  // Uncomment to view tableau
  // PrintTableau(a, b, c, z);
  Position pivot(0,0);
  vector<double> solutions = getSolution(c.size(), non_basic_vars, b);
  while (hasPivotColumn(c)) {
    pivot = getPivotElement(a, b, c);
    // cout << "pivot: (" << pivot.row << ", " << pivot.column << ")\n";
    if (pivot.row == -1)
      return { 1, solutions };
    non_basic_vars[pivot.row] = pivot.column;
    pivot_trace[pivot.column] = pivot.row;
    ProcessPivotElement(a, b, c, z, pivot);
    // Uncomment to view tableau
    // PrintTableau(a, b, c, z);

    // check constraints
    solutions = getSolution(c.size(), non_basic_vars, b);
    // if (!checkConstraints(n, m, A_original, b_original, solutions))
    //   return { -1, solutions };
  }
  // get solutions
  solutions = getSolution(c.size(), non_basic_vars, b);
  return { 0, solutions};
}
/**
 * Simplex Method
 1. Convert matrix to tableau
  // this step may not be necessary as input has it already combined: combine constraints c subject to linear inequalities
  (e.g. for each row i of m, c[i]a[i][0] + ... + c[i]a[i][m-1] <= c[i]b[i])
  a. append n slack variables to rows: (a[i][0] ... a[i][m-1] + s[i][1] + ... + s[i][n-1])
 2. Apply Simplex Tableau Method to Gaussian elimination
  a. Choose pivot based on 
    Entering variable: the smallest (the most negative) entry in the bottom row of the tableau
    Departing variable: corresponding to smallest nonnegative ratio of b[i]/a[i][b] 
    Pivot is the entry of the entering variable's column, and the departing variable's row
  b. Finally apply Gaussian elimination to the column that contains the pivot
    Notes: the method may not require row swaps upon processing of a pivot as in the prior assignment on Gaussian elimination
    due to the selection process of the pivot row via departing variable
  c. When there are no negative elements in the bottom row, we can then determine the optimal solution if there is one

  * Two Phase Method
  Phase 1
  1. For mixed constraints append column vectors artificial and slack variable . Ensure slack vars are set to -1
    a. In the case of a negative rhs; Multiply both sides of inequality by -1 reversing the direction of the inequality.
  2. Max Z = -A1 -A2 etc
  3. Eliminate the basic variables A1, A2, etc using elementary row operations from the relevant rows to get -Z + A1 + A2 = 0 
  4. Apply Simplex Method
    a. If at least 1 artificial var yields grater than zero then no feasible solution.
  5. In final tableau phase, drop artificial vars
  6. Subsitute phase 2 objective function
  7. Restore proper form from Gaussian elimination
  Phase 2
  1. Apply Simplex Method
 **/
int main(){
  int n, m;
  cin >> n >> m;
  int mPlusSlack = m + n;
  matrix A(n, vector<double>(mPlusSlack, 0));

  // Each index corresponds to the non basic vars in the tableau (row index), where each element holds the non basic var (column index)
  vector<double> non_basic_vars(n, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
    A[i][m + i] = 1;
    // initially slack vars are set as non basic
    non_basic_vars[i] = m + i;
  }
  vector<double> b(n);
  vector<double> b_original(n);
  bool hasMixedConstraints = false;
  int mixConstraintsCount = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
    b_original[i] = b[i];
    if (b[i]< 0) {
      ++mixConstraintsCount;
      // Negative rhs; Multiply both sides of inequality by -1 reversing the direction of the inequality.
      A[i][m + i] = -1;
      b[i] *= -1;
      for (int j = 0; j < m; j++) {
        A[i][j] *= -1;
      }
      // Append new column to tableau introducing artificial var
      for (int k = 0; k < n; k++) {
        A[k].push_back(0);
      }
      int col = A[i].size() - 1;
      A[i][col] =  1;
      // replace initial slack var with artificial var
      non_basic_vars[i] = col;
      hasMixedConstraints = true;
    }
  }
  int cSize = A[0].size();
  vector<double> c_original(cSize, 0);
  vector<double> c_phase1(cSize, 0);
  vector<double> c_phase2(cSize, 0);
  for (int i = 0; i < m; i++) {
    cin >> c_original[i];
    c_original[i] *= -1;
  }
  double z = 0;
  pair<int, vector<double>> ans;
  c_phase2 = c_original;

  if (hasMixedConstraints) {
    // 3. Eliminate the basic variables A1, A2, etc using elementary row operations from the relevant rows to get -Z + A1 + A2 = 0 
    for (int i = 0; i < n; i++) {
      if (b_original[i]> 0)
        continue;
      // Subtract row by pivot row
      for (int j = 0; j < m; j++) {
        c_phase1[j] -= A[i][j];
      }
      c_phase1[m + i] = 1;
      z -= b[i];
    }
    ans = solve_diet_problem(n, m, A, b, c_phase1, b_original, non_basic_vars, z);
    // Step 4a Check if any artificial var appears in the basis with a positive value
    // cout << "mixConstraintsCount " << mixConstraintsCount << endl;
    vector<double> results = ans.second;
    // cout << "results\n";
    // for (int i = 0; i < results.size(); i++)
    // {
    //   cout << i << " " << results[i] << endl;
    // }
    for (int i = mPlusSlack; i < results.size(); ++i)
    {
      if (std::abs(results[i]) > CALC_PRECISION)
      {
        printf("No solution\n");
        return 0;
      }
    }

    // Steps 5-7: Setup tableau for Phase 2

    // Remove artifical var columns
    // for (int row = 0; row < n; ++row)
    // {
    //   A[row].erase(A[row].end() - mixConstraintsCount);
    // }
    // c_original.erase(c_original.end() - mixConstraintsCount);
    // c_phase1.erase(c_phase1.end() - mixConstraintsCount);
    // c_phase2.erase(c_phase2.end() - mixConstraintsCount);
    for (int row = 0; row < n; ++row)
    {
      for (int col = mPlusSlack; col < A[row].size(); ++col)
        A[row][col] = 0;
    }
    for (int col = mPlusSlack; col < c_original.size(); ++col) {
      c_original[col] = 0;
      c_phase1[col] = 0;
      c_phase2[col] = 0;
    }

    // cout << "size:  " << c_original.size() << " " << c_phase1.size() << " " << c_phase2.size() << endl;
    z = 0;
    vector<Position> pivots;
    for (int j = 0; j < A[0].size() - mixConstraintsCount; j++)
    {
      Position pivot(0,0);
      int count1 = 0;
      int count0 = 0;
      for (int i = 0; i < n; i++)
      {
        if (A[i][j] == 0)
          count0++;
        if (A[i][j] == 1) {
          count1++;
          pivot.row = i;
          pivot.column = j;
        }
      }
      if (count1 == 1 && count0 == n-1)
        pivots.push_back(pivot);
    }
    // Restore proper form from Gaussian Elimination via pivots (basic variables)
    for (auto pivot: pivots) {
      int row = pivot.row;
      int col = pivot.column;
      for (int j = 0; j < c_phase2.size() - mixConstraintsCount; j++)
      {
        // cout << c_phase2[j] << " -= " << A[row][j] << " * " << c_original[col] << endl;
        c_phase2[j] -= (A[row][j] * c_original[col]);
      }
      z -= (b[row] * c_original[col]);
    }
  }
  // Phase 2
  // printf("Phase 2\n");
  ans = solve_diet_problem(n, m, A, b, c_phase2, b_original, non_basic_vars, z);
  vector<double> results = ans.second;
  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;
  }
  return 0;
}
