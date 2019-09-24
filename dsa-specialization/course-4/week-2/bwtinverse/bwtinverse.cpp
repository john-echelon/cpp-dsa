#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <new>

using std::cin;
using std::cout;
using std::endl;
using std::memset;
using std::sort;
using std::string;
using std::vector;

char buffer[5000];
char buffer2[5000];
// char buffer3[5000 * 4];
char b1[5000];
char b2[5000];
char b3[5000];
char b4[5000];

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
  // vector<char> result;
  int length = bwt.length();
  // char result[length + 1] = {0};
  char * result;
  result = new(buffer) char[length + 1];
  int n_mer = 2;
  int unique_symbols = 4;
  // vector<char *> matrix = vector<char *>(length);
  int count[unique_symbols] = {0}; // [A, C, G, T]
  int count2[unique_symbols] = {0}; // [A, C, G, T]

  int occurrence[length][unique_symbols] = {0};
  // vector<vector<int>> lastToFirst = vector<vector<int>>(unique_symbols, vector<int>());
  vector<int *> lastToFirst = vector<int *>(unique_symbols);
  // char bwt_copy[length] = {0};
  char * bwt_copy = new(buffer2) char[length + 1];

  strcpy(bwt_copy, bwt.c_str());
  sort(bwt_copy, bwt_copy + length);
  for (int i = 0; i < length; i++) {
    // matrix[i] = new char [n_mer + 1];
    // memset(matrix[i], 0, n_mer + 1);
    // matrix[i][1] = bwt[i];
    // matrix[i][2] = '\0';
    for (int j = 0; j < unique_symbols; ++j) {
      occurrence[i][j] = count[j];
      // allocating buffer memory to lastToFirst
      // lastToFirst[j] = new(buffer3 + j * 5000) int [length];
      if (j == 0) {
        lastToFirst[j] = new(b1) int [length];
      }
      if (j == 1) {
        lastToFirst[j] = new(b2) int [length];
      }
      if (j == 2) {
        lastToFirst[j] = new(b3) int [length];
      }
      if (j == 3) {
        lastToFirst[j] = new(b4) int [length];
      }
    }
    int idx = getCountIndex(bwt[i]);
    if (idx != -1)
      ++count[idx];
  }
  // for (int i = 0; i < length; i++) {
  //   matrix[i][0] = bwt_copy[i]; 
  // }
  // cout << "matrix\n";
  // for (auto & str : matrix) {
  //   cout << str << endl;
  // }
  for (int i = 1; i < length; i++) {
    int idx = 0;
    if (i != 2339)
      idx = getCountIndex(bwt_copy[i]);
    if (i == 2339) {
      idx = getCountIndex(bwt_copy[i]);
      int c1 = count2[idx];
      int l1 = lastToFirst[idx][c1];
      int l2 = lastToFirst[idx][c1 + 1];
    }
    lastToFirst[idx][count2[idx]++] = i;
  }
  int i = 0;
  int resultIdx = length - 1;
  result[resultIdx--] = '$';
  // result.push_back('$');
  while (bwt[i] != '$') {
    // cout << "firstCol " << matrix[i][0] << " lastCol " << matrix[i][1];
    int lastColSymbol = bwt[i];
    if (lastColSymbol == '$') {
      i = 0;
      // cout << " lastToFirst 0\n";
      // result.push_back(bwt_copy[i]);
      result[resultIdx--] = bwt_copy[i];
      continue;
    }
    int symbolIdx = getCountIndex(lastColSymbol);
    int oIdx = occurrence[i][symbolIdx];
    // cout << " lastToFirst " <<  lastToFirst[symbolIdx][oIdx] << endl;
    i = lastToFirst[symbolIdx][oIdx];
    // result.push_back(bwt_copy[i]);
    result[resultIdx--] = bwt_copy[i];
  }
  return string(result);
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
