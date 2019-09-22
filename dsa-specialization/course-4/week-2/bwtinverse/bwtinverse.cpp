#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::string;
using std::vector;

string InverseBWT(const string& bwt) {
  string result = "";
  int length = bwt.length();
  vector<string> matrix = vector<string>(length, string(length, ' '));
  vector<string> matrix2 = vector<string>(length, string(length, ' '));
  for (int i = 0; i < length; i++) {
    matrix[i][0] = bwt[i]; 
    matrix2[i][0] = bwt[i]; 
  }
  for (int i = 1; i <= length ; i++) {
    sort(matrix.begin(), matrix.end());
    for (int j = 0; j < length; j++) {
      matrix2[j][i] = matrix[j][i-1];
        // matrix[j] = matrix2[j];
      if (i < length) {
        for (int k = 0; k <= i; k++) {
          matrix[j][k] = matrix2[j][k];
        }
      }
    }
  }
  // cout << "matrix1\n";
  // for (auto & str : matrix) {
  //   cout << str << endl;
  // }
  // cout << "matrix2\n";
  // for (auto & str : matrix2) {
  //   cout << str << endl;
  // }
  result = matrix[0].substr(1, length-1) + '$';
  // write your code here

  return result;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
