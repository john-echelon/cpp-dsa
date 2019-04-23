#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

void min_and_max(const string &exp, int i, int j, vector<vector<long long>> &minLookup, vector<vector<long long>> &maxLookup){
  long long minNum = std::numeric_limits<long long>::max();
  long long maxNum = std::numeric_limits<long long>::min();
  for(int k = i; k < j; k++){
    long long a = eval(maxLookup[i][k], maxLookup[k+1][j], exp[k+ k-1]);
    long long b = eval(maxLookup[i][k], minLookup[k+1][j], exp[k+ k-1]);
    long long c = eval(minLookup[i][k], maxLookup[k+1][j], exp[k+ k-1]);
    long long d = eval(minLookup[i][k], minLookup[k+1][j], exp[k+ k-1]);
    minNum = min(minNum, min(min(a, b), min(c, d)));
    maxNum = max(maxNum, max(max(a, b), max(c, d)));
  }
  minLookup[i][j] = minNum;
  maxLookup[i][j] = maxNum;
}

long long get_maximum_value(const string &exp) {
  const int asciiZero = 48;
  int n = exp.length() - (exp.length()-1) / 2;
  vector<vector<long long>> minLookup (n+1, vector<long long> (n+1));
  vector<vector<long long>> maxLookup (n+1, vector<long long> (n+1));
  for(int i = 1, j = 0; i<=n; i++, j+=2){
    minLookup[i][i] = exp[j] - asciiZero;
    maxLookup[i][i] = exp[j] - asciiZero;
  }
  for(int s =1; s <= n-1; s++){
    for(int i = 1; i <= n-s; i++){
      int j = i + s;
      min_and_max(exp, i, j, minLookup, maxLookup);
    }
  }
  return maxLookup[1][n];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
