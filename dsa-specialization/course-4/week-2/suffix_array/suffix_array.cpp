#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

bool compare(const pair<string, int>&i, const pair<string, int>&j)
{
    return i.first < j.first;
}
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  vector<pair<string, int>> suffixes;
  // Implement this function yourself
  for (int i = text.length() - 1; i >= 0; --i) {
    // cout << i << " " << text.substr(i, text.length() - i) << endl;
    suffixes.push_back(make_pair(text.substr(i, text.length() - i), i));
  }
  sort(suffixes.begin(), suffixes.end(), compare);
  for (auto & p : suffixes) {
    result.push_back(p.second);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
