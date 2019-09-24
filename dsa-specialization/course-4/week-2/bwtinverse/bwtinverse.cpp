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
unsigned char buffer3[sizeof(int) * 5000 * 4];
unsigned char buffer4[sizeof(int) * 4 * 5000];

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
  // cout << "length " << length << endl;
  char * result;
  result = new(buffer) char[length + 1];
  int unique_symbols = 4;
  // vector<char *> matrix = vector<char *>(length);
  int count[unique_symbols] = {0}; // [A, C, G, T]
  int count2[unique_symbols] = {0}; // [A, C, G, T]

  int * occurrence = new(buffer3) int [length * unique_symbols];
  int * lastToFirst = new(buffer4) int [unique_symbols * length];
  char * bwt_copy = new(buffer2) char[length + 1];

  strcpy(bwt_copy, bwt.c_str());
  sort(bwt_copy, bwt_copy + length);
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < unique_symbols; ++j) {
      int a1 = count[j];
      int a2 = i + unique_symbols * j;
      occurrence[i * unique_symbols + j] = count[j];
    }
    int idx = getCountIndex(bwt[i]);
    if (idx != -1)
      ++count[idx];
  }
  // for (int i = 0; i < length; i++) {
  //   for (int j = 0; j < unique_symbols; ++j) {
  //     cout << occurrence[i + unique_symbols * j] << " ";
  //   }
  //   cout << endl;
  // }
  for (int i = 1; i < length; i++) {
    int idx = getCountIndex(bwt_copy[i]);
    lastToFirst[idx * length + count2[idx]] = i;
    ++count2[idx];
  }
  int i = 0;
  int resultIdx = length - 1;
  result[resultIdx--] = '$';
  while (bwt[i] != '$') {
    char lastColSymbol = bwt[i];
    if (lastColSymbol == '$') {
      i = 0;
      result[resultIdx--] = bwt_copy[i];
      continue;
    }
    int symbolIdx = getCountIndex(lastColSymbol);
    int oIdx = occurrence[i * unique_symbols + symbolIdx];
    i = lastToFirst[symbolIdx * length + oIdx];
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
