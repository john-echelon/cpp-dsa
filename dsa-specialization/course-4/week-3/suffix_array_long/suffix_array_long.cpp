#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;

map<int, int> BuildCharMap(const string& text) {
  string textSorted = text;
  sort(textSorted.begin(), textSorted.end());
  map<int, int> charMap;
  int uniqueCount = 0;
  for (const auto& c : textSorted) {
    if (charMap.find(c) == charMap.end()) {
      charMap[c] = uniqueCount++;
    }
  }
  return charMap;
}
vector<int> SortCharacters(const string& text, map<int, int>& charMap) {
  int textLength = text.length();
  int sizeOfAlphabet = charMap.size();
  vector<int> order = vector<int>(textLength, 0);
  vector<int> count = vector<int>(sizeOfAlphabet, 0);
  for (int i = 0; i < textLength; ++i) {
    ++count[charMap[text[i]]];
  }
  for (int j = 1; j < sizeOfAlphabet; ++j) {
    count[j]+= count[j - 1];
  }
  for (int i = textLength - 1; i >= 0; --i) {
    int c = charMap[text[i]];
    --count[c];
    order[count[c]] = i;
  }
  return order;
}
vector<int> ComputerCharClasses(const string& text, vector<int>& order) {
  int textLength = text.length();
  vector<int> charClass = vector<int>(textLength, 0);
  charClass[order[0]] = 0;
  for (int i = 1; i < textLength; ++i) {
    if (text[order[i]] != text[order[i - 1]]) {
      charClass[order[i]] = charClass[order[i - 1]] + 1;
    } else {
      charClass[order[i]] = charClass[order[i - 1]];
    }
  }
  return charClass;
}

vector<int> SortDoubled(const string& text, int length, vector<int>& order, vector<int>& charClass) {
  int textLength = text.length();
  vector<int> count = vector<int>(textLength, 0);
  vector<int> newOrder = vector<int>(textLength, 0);
  for (int i = 0; i < textLength; ++i) {
    ++count[charClass[i]];
  }
  for (int j = 1; j < textLength; ++j) {
    count[j] = count[j] + count[j - 1];
  }
  for (int i = textLength - 1; i >= 0; --i) {
    int start = (order[i] - length + textLength) % textLength;
    int cl = charClass[start];
    --count[cl];
    newOrder[count[cl]] = start;
  }
  return newOrder;
}
vector<int> UpdateClasses(int length, vector<int>& order, vector<int>& charClass) {
  int n = order.size();
  vector<int> newClass = vector<int>(n);
  newClass[order[0]] = 0;
  for (int i = 1; i < n; ++i) {
    int cur = order[i], prev = order[i - 1];
    int mid = (cur + length) % n, midPrev = (prev + length) % n;
    if (charClass[cur] != charClass[prev] || charClass[mid] != charClass[midPrev]) {
      newClass[cur] = newClass[prev] + 1;
    } else {
      newClass[cur] = newClass[prev];
    }
  }
  return newClass;
}
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  map<int, int> charMap = BuildCharMap(text);
  vector<int> order = SortCharacters(text, charMap);
  vector<int> charClass = ComputerCharClasses(text, order);
  int length = 1;
  int textLength = text.length();
  while (length < textLength) {
    order = SortDoubled(text, length, order, charClass);
    // cout << "L = " << length << endl;
    // for (auto i : order) {
    //   cout << i << " ";
    // }
    // cout << endl;
    charClass = UpdateClasses(length, order, charClass);
    length *= 2;
  }
  // Implement this function yourself
  return order;
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
