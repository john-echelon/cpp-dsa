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

string BWT(const string& text) {
  string result = "";
  int length = text.length();
  vector<string> matrix = vector<string>(length, text);
  for (int i = 1; i < length; i++) {
    for (int j = 0, k = i; j < length; j++, k++) {
      matrix[i][j] = text[k % length]; 
    }
  }
  sort(matrix.begin(), matrix.end());
  for (auto & str : matrix) {
    result.push_back(str[length - 1]);
    // cout << str << endl;
  }
  // write your code here

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}