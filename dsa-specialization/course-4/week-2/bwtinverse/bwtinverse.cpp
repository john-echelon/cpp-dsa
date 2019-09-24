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

/*
  build countArray based on # occurrences of each symbol for each i position 
  given pos i,  last count array stores the occurence count (lastColumn) at pos i, for each symbol.
  the occurence count maps to the index i of firstOccurrenceArray
  firstOccurrence is a matrix where each row stores the lastToFirst pos for a given symbol, where index determines occurence count of that symbol 
  */
int getCountIndex(const char & c) {
  if (c == 'A')
    return 0;
  else if (c == 'C')
    return 1;
  else if (c == 'G')
    return 2;
  else if (c == 'T')
    return 3;
  return -1;
}
// TODO: Try char[] instead of vector<char> result, and or use buffers, consider mappers, convert bwt to char array for sort
string InverseBWT(const string& bwt) {
  vector<char> result;
  int length = bwt.length();
  int n_mer = 2;
  int unique_symbols = 4;
  vector<char *> matrix = vector<char *>(length);
  int count[unique_symbols] = {0}; // [A, C, G, T]
  int occurrence[length][unique_symbols] = {0};
  vector<vector<int>> lastToFirst = vector<vector<int>>(unique_symbols, vector<int>());
  for (int i = 0; i < length; i++) {
    matrix[i] = new char [n_mer + 1];
    memset(matrix[i], 0, n_mer + 1);
    matrix[i][1] = bwt[i];
    matrix[i][2] = '\0';
    for (int j = 0; j < unique_symbols; ++j) {
      occurrence[i][j] = count[j];
    }
    int idx = getCountIndex(bwt[i]);
    if (idx != -1)
      ++count[idx];
  }
  string bwt_copy = bwt;
  sort(bwt_copy.begin(), bwt_copy.end());
  for (int i = 0; i < length; i++) {
    matrix[i][0] = bwt_copy[i]; 
  }
  // cout << "matrix\n";
  // for (auto & str : matrix) {
  //   cout << str << endl;
  // }
  for (int i = 1; i < length; i++) {
    int idx = getCountIndex(matrix[i][0]);
    lastToFirst[idx].push_back(i);
  }
  int i = 0;
  result.push_back('$');
  while (matrix[i][1] != '$') {
    // cout << "firstCol " << matrix[i][0] << " lastCol " << matrix[i][1];
    int lastColSymbol = matrix[i][1];
    if (lastColSymbol == '$') {
      i = 0;
      // cout << " lastToFirst 0\n";
      result.push_back(matrix[i][0]);
      // result.insert(0, 1, matrix[i][0]);
      continue;
    }
    int symbolIdx = getCountIndex(lastColSymbol);
    int oIdx = occurrence[i][symbolIdx];
    // cout << " lastToFirst " <<  lastToFirst[symbolIdx][oIdx] << endl;
    i = lastToFirst[symbolIdx][oIdx];
    result.push_back(matrix[i][0]);
    // result.insert(0, 1, matrix[i][0]);
  }
  // result = string(matrix[0]).substr(1, length-1) + '$';
  // write your code here
  for (auto & str : matrix) {
    delete [] str;
  }

  return string(result.rbegin(), result.rend());
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
