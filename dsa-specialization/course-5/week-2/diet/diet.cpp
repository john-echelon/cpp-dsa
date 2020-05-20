#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int PRECISION = 20;
typedef vector<vector<double>> matrix;

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
void PrintTableau(matrix &a, vector<double> &b, vector<double> &c, double &z, const Position &pivot) {
  // cout << "pivot: (" << pivot.row << " ," << pivot.column << "): " << a[pivot.row][pivot.column] << "\n";
  PrintMatrix(a, b);
  PrintColumn(c);
  cout << z << "\n";
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
      if (i == pivot.row)
        continue;
      // Subtract row by pivot row
      for (int j = 0; j < cSize; j++) {
        a[i][j] += (a[pivot.row][j] * targetElement * -1);
      }
      b[i] += (b[pivot.row] * targetElement * -1);
    }

}

int getPivotColumn(vector<double> &c) {
  return std::min_element(c.begin(), c.end()) - c.begin();
}

int getPivotRow(matrix &a, vector<double> &b, int pivotColumn, bool useNegative = false) {
  int rSize = a.size();
  double enteringRatios = INT_MAX;
  int pivotRow = -1;
  for (int i = 0; i < rSize; ++i) {
    if (a[i][pivotColumn] == 0)
      continue;
    double val = b[i] / a[i][pivotColumn];
    cout << "ratio: " << b[i] << "/" << a[i][pivotColumn] << ": " << val << "\n";
    if (val < enteringRatios && (val >= 0 || useNegative)) {
    // if (val < enteringRatios) {
      cout << "*ratio: " << b[i] << "/" << a[i][pivotColumn] << ": " << val << "\n";
      enteringRatios = val;
      pivotRow = i;
    }
  }
  cout << "getPivotRow: (" << pivotRow << ", " << pivotColumn << ")\n";
  return pivotRow;
}

Position getPivotElement(matrix &a, vector<double> &b, vector<double> &c, int useNegative = false) {
  Position pivot(0,0);
  pivot.column = getPivotColumn(c);
  pivot.row = getPivotRow(a, b, pivot.column, useNegative);
  return pivot;
}

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix a, 
    vector<double> b, 
    vector<double> c) {

  // Write your code here
  vector<int> visited(c.size(), 0);
  Position pivot = getPivotElement(a, b, c);
  double z = 0;
  cout << "pivot: (" << pivot.row << ", " << pivot.column << ")\n";
  PrintTableau(a, b, c, z, pivot);
  if (pivot.row == -1 ) {
    return {-1, c};
  }
  if (c[getPivotColumn(c)] >= 0) {
    return {1, c};
  }
  do {
    ProcessPivotElement(a, b, c, z, pivot);
    // visited[pivot.column] = true;
    ++visited[pivot.column];
    pivot = getPivotElement(a, b, c);
    cout << "pivot: (" << pivot.row << ", " << pivot.column << ")\n";
    PrintTableau(a, b, c, z, pivot);
    // if (c[getPivotColumn(c)] >= 0 && visited[pivot.column] > 0) {
    //   break;
    // }
    if (pivot.row == -1 ) {
      return {-1, c};
    }
  // } while(visited[pivot.column] <1);
  } while (c[getPivotColumn(c)] < 0);
  cout << "pivot: (" << pivot.row << ", " << pivot.column << ")\n";
  PrintTableau(a, b, c, z, pivot);
  return {0, c};
}
/**
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
 **/
int main(){
  int n, m;
  cin >> n >> m;
  int mPlusSlack = m + n;
  // int mPlusSlack = m;
  matrix A(n, vector<double>(mPlusSlack, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
      // A[i][j] *= -1;
    }
    // A[i][m + i] = 1;
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    // b[i] *= -1;
  }
  vector<double> c(mPlusSlack, 0);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
    // c[i] *= -1;
  }
  // Pivot A for duality setup
  int mSlack_pivot = mPlusSlack + 1;
  // int mSlack_pivot = mPlusSlack;
  matrix A_pivot(m, vector<double>(mSlack_pivot, 0));
  vector<double> b_pivot(m);
  vector<double> c_pivot(mSlack_pivot, 0);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      A_pivot[i][j] = A[j][i];
      // A_pivot[i][j] = A[j][i] * -1;
    }
    A_pivot[i][n + i] = 1;
  }
  for (int i = 0; i < m; i++) {
    // b_pivot[i] = c[i];
    b_pivot[i] = c[i] * -1;
  }
  for (int i = 0; i < n; i++) {
    c_pivot[i] = b[i];
    // c_pivot[i] = b[i] * -1;
  }
  c_pivot[c_pivot.size() - 1] = 1;

  // pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);
  pair<int, vector<double>> ans = solve_diet_problem(n, m, A_pivot, b_pivot, c_pivot);
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
