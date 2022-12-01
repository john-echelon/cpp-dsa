// Good job! (Max time used: 0.00/1.00, max memory used: 11948032/2147483648.)
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const double EPS = 1e-6;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

void PrintColumn(const Column &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row) {
        std::cout << column[row] << " ";
    }
}

void PrintMatrix(const Matrix &m, const Column & column) {
    int size = m.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row) {
      for (int col = 0; col < size; ++col) {
        std::cout << m[row][col] << " ";
      }
      std::cout << column[row] << std::endl;
      std::cout << std::endl;
    }
}
Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

Position SelectPivotElement(
  const Matrix &a, 
  std::vector <bool> &used_rows, 
  std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row]) 
        ++pivot_element.row;
    while (used_columns[pivot_element.column])
        ++pivot_element.column;
    Position pivot_temp = pivot_element;
    int v_size = a.size() - 1;
    while (a[pivot_temp.row][pivot_temp.column] == 0 && pivot_temp.row < v_size)
        pivot_temp.row++;
    pivot_element = pivot_temp;
    return pivot_element;
}

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
    // Reduce row by pivot value;
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

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation & equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
        // cout << "Pivot Element: " << pivot_element.row << ", " << pivot_element.column << "\n";
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        // PrintMatrix(a, b);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }
    return b;
}

bool CheckSolution(Equation & equation) {
    Matrix &a = equation.a;
    int v_size = a.size();
    for (int i = 0; i < v_size; i++)
    {
        int count = 0;
        for (int j = 0; j < v_size; j++) {
            if (a[i][j] == 0)
                count++;
        }
        if (count == v_size)
            return false;
    }
    return true;
}
int main() {
    Equation equation = ReadEquation();
    SolveEquation(equation);
    Column solution = equation.b;

    // if (!CheckSolution(equation))
    //     solution.assign(solution.size(), 0);
    PrintColumn(solution);
    return 0;
}
