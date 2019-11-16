#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

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

int GetLcpOfSuffixes(const string & text, int i, int j, int equal) {
  int lcp = std::max(0, equal);
  while (i + lcp < text.length() && j + lcp < text.length()) {
    if (text[i + lcp] == text[j + lcp])
      lcp++;
    else break;
  } 
  return lcp;
}

vector<int> InvertSuffixArray(const vector<int>& order) {
  vector<int> pos = vector<int>(order.size());
  for (int i = 0; i < pos.size(); i++)
    pos[order[i]] = i;
  return pos;
}

vector<int> ComputeLcpArray(const string& text, const vector<int> & order) {
  int textLen = text.length();
  vector<int> lcpArray = vector<int>(textLen - 1);
  int lcp = 0;
  vector<int> posInOrder = InvertSuffixArray(order);
  int suffix = order[0];
  for (int i = 0; i < textLen; i++) {
    int orderIndex = posInOrder[suffix];
    if (orderIndex == textLen - 1) {
      lcp = 0;
      suffix = (suffix + 1) % textLen;
      continue;
    }
    int nextSuffix = order[orderIndex + 1];
    lcp = GetLcpOfSuffixes(text, suffix, nextSuffix, lcp - 1);
    lcpArray[orderIndex] = lcp;
    suffix = (suffix + 1) % textLen;
  }
  return lcpArray;
}
// Data structure to store edges of a suffix tree.
struct Edge {
  // The ending node of this edge.
  int node;
  // Starting position of the substring of the text 
  // corresponding to the label of this edge.
  int start;
  // Position right after the end of the substring of the text 
  // corresponding to the label of this edge.
  int end;

  Edge(int node_, int start_, int end_) : node(node_), start(start_), end(end_) {}
  Edge(const Edge& e) : node(e.node), start(e.start), end(e.end) {}
};

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).
map<int, vector<Edge> > SuffixTreeFromSuffixArray(
    const vector<int>& suffix_array,
    const vector<int>& lcp_array,
    const string& text) {
  map<int, vector<Edge> > tree;
  // Implement this function yourself
  return tree;
}
int main() {
  char buffer[200001];
  scanf("%s", buffer);
  string text = buffer;
  vector<int> suffix_array = BuildSuffixArray(text);
  vector<int> lcp_array = ComputeLcpArray(text, suffix_array);
  for (int i = 0; i < suffix_array.size(); ++i)
    cout << suffix_array[i] << ' ';
  cout << endl;
  for (int i = 0; i < lcp_array.size(); ++i)
    cout << lcp_array[i] << ' ';
  cout << endl;
  return 0;
}
