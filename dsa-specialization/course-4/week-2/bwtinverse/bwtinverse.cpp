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
  for (int i = 0; i < length; i++) {
    matrix[i][0] = bwt[i]; 
  }
  for (int i = 1; i <= length ; i++) {
    sort(matrix.begin(), matrix.end());
    // cout << "sorted matrix\n";
    // for (auto & str : matrix) {
    //   cout << str << endl;
    // }
    if (i < length) {
    for (int j = 0; j < length; j++) {
      for (int k = i; k >= 1; --k) {
        matrix[j][k] = matrix[j][k-1];
      }
    }
      for (int i = 0; i < length; i++) {
        matrix[i][0] = bwt[i]; 
      }
    }
    // cout << "matrix\n";
    // for (auto & str : matrix) {
    //   cout << str << endl;
    // }
  }
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
