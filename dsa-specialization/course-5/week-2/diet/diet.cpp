#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const int PRECISION = 20;
const double BIG_M = 10e9;
const double CALC_PRECISION = 1e-3;
typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

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
      if (i.size() == setSize)
          subsets.emplace_back(i);
    }

    return subsets;
    }

void PrintMatrix(const Matrix &m, vector<double> &b) {
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

static Position SelectPivotElement(const Matrix &a, int k)
{
	int v_size = a.size();

  Position pivot_element(k, 0);
  for (int row = pivot_element.row, v_size = a.size(); row < v_size; row++)
  {
    double max_a = 0;
    if (std::abs(a[row][pivot_element.column]) > std::abs(max_a))
    {
      max_a = a[row][pivot_element.column];
      pivot_element.row = row;
    }
  }
	return pivot_element;
}

static int SwapLines(Matrix &a, Column &b, Position &pivot_element)
{
	swap(a[pivot_element.column], a[pivot_element.row]);
	swap(b[pivot_element.column], b[pivot_element.row]);
	pivot_element.row = pivot_element.column;

	return 0;
}

static void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element)
{
 double pivot_value = a[pivot_element.row][pivot_element.column];
    if (pivot_value == 0) return;
    int v_size = a.size();
    for (int j = pivot_element.column; j < v_size; j++) {
      a[pivot_element.row][j] /= pivot_value;
    }
    b[pivot_element.row] /= pivot_value;
    // For all appropriate non-pivot rows...
    for (int i = 0; i < v_size; i++) {
      double targetElement = a[i][pivot_element.column];
      if (targetElement == 0 || i == pivot_element.row)
        continue;
      // Subtract row by pivot row
      for (int j = 0; j < v_size; j++)
      {
          a[i][j] += (a[pivot_element.row][j] * targetElement * -1);
      }
      b[i] += (b[pivot_element.row] * targetElement * -1);
    }
}

bool SolveEquation(Matrix &a, Column &b) {
  bool unbounded = false;
  for (int j = 0; j < a.size(); j++)
  {
    Position pivot_element = SelectPivotElement(a, j);

    if (pivot_element.row == -1) {
      unbounded = true;
      break;
    }

    if (SwapLines(a, b, pivot_element)) {
      unbounded = true;
      break;
    }

    ProcessPivotElement(a, b, pivot_element);
  }
  return unbounded;
}
pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    Matrix a, 
    vector<double> b, 
    vector<double> c) {

  // Expand for inequalities: amount[i] >= 0
  int mPlusSlack = n + m;
  Matrix a_phase1(mPlusSlack + 1, vector<double>(m, 0));
  Column b_phase1(mPlusSlack + 1);

  for (int i = 0; i < mPlusSlack; i++) {
    if (i < n) {
      a_phase1[i] = a[i];
      b_phase1[i] = b[i];
    } else {
      // Add inequalities: amount[i] >= 0
      a_phase1[i][i - n] = -1;
    }
  }

  // add final inequality to distinguish between bounded and unbounded cases
  // e.g. amount[1] + ... + amount[m] <= 10e9
  for (int i = 0; i < m; i++) {
    a_phase1[mPlusSlack][i] = 1;
  }
  b_phase1[mPlusSlack] = BIG_M;
  vector<vector<int> > subsets = PowerSet(mPlusSlack + 1, m);

	vector<double> ans_solution;
	int ans_case_type = -1;
  double z_max = (numeric_limits<double>::max() * -1);
  // Brute force all n+m subsets to find optimality
  for (int i = 0; i < subsets.size(); i++) {
    Matrix a_phase2(m, vector<double>(m, 0));
    Column b_phase2(m);
    bool unbounded = false;

    for (int j = 0; j < m; j++) {
      int index = subsets[i][j];
      a_phase2[j] = a_phase1[index];
      b_phase2[j] = b_phase1[index];

      if (b_phase2[j] == BIG_M)
      {
        // PrintMatrix(a_temp, b_temp);
        unbounded = true;
      }
    }

    bool unbounded2 = SolveEquation(a_phase2, b_phase2);
    if (unbounded2)
      continue;
    for (int j = 0; j < n + m + 1; j++) {
      double sum = 0;

      for (int k = 0; k < m; k++) {
        sum += b_phase2[k] * a_phase1[j][k];
      }
      if (sum > b_phase1[j] + CALC_PRECISION) {
        unbounded2 = true;
        break;
      }
    }
    if (unbounded2) continue;

    double z = 0;

    for (int j = 0; j < m; j++) {
      z += c[j] * b_phase2[j];
    }

    if (z > z_max) {
      z_max = z;
      ans_solution = b_phase2;
      if (unbounded) {
        ans_case_type = 1;
      } else {
        ans_case_type = 0;
      }
    }
  }

  return {ans_case_type, ans_solution};
}

int main(){
  int n, m;
  cin >> n >> m;
  Matrix a(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, a, b, c);

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
