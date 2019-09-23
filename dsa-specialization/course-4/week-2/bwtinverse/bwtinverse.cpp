#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::memset;
using std::sort;
using std::string;
using std::vector;

bool comparisonFunc(const char *c1, const char *c2)
{
    return strcmp(c1, c2) < 0;
}

string InverseBWT(const string& bwt) {
  string result = "";
  int length = bwt.length();
  vector<char *> matrix = vector<char *>(length);
  for (int i = 0; i < length; i++) {
    matrix[i] = new char [length + 1];
    memset(matrix[i], 0, length + 1);
    matrix[i][0] = bwt[i]; 
    // matrix[i][length] = '\0';
  }
  for (int i = 1; i <= length ; i++) {
    sort(matrix.begin(), matrix.end(), comparisonFunc);
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
      // cout << str << endl;
    // }
  }
  result = string(matrix[0]).substr(1, length-1) + '$';
  // write your code here
  for (auto & str : matrix) {
    delete [] str;
  }

  return result;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
