#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::queue;
using std::vector;

using namespace std;
struct Node {
  int suffixPos;
  int suffixLength;
  vector<Node> children;
};

// typedef map<char, int> edges;
typedef vector<Node> trie;

/*
  For current node = root
  foreach child of current node, find substr of suffix that matches symbol
    if match (we break the existing edge in the middle)
      update current node suffix to new matching substring of symbol
      current node = matched suffix node
      symbol = substring with updated starting pos to be offset by previous suffix match position
    else 
      create new child under current with symbol
      store suffix value = pos and length of symbol
      break;
*/
trie build_trie(const string & text) {
  int length = (int) text.size();
  trie t;
  Node firstNode = { 0, length };
  t.push_back(firstNode);
  for (int i = 1; i < length; i++) {
    Node n = { i, length - i };
    t.push_back(n);
  }
  // int nodeCount = 0;
  // for (string s : patterns) {
  //   edges * currentNode = t[0];
  //   for (int i = 0; i < s.size(); i++) {
  //     char symbol = s[i];
  //     // if there is an outgoing edge from currentNode with label currentSymbol:
  //     if ((*currentNode).find(symbol) != (*currentNode).end()) {
  //       int nodeIndex = (*currentNode)[symbol];
  //       currentNode = t[nodeIndex];
  //     } else {
  //       (*currentNode)[symbol] = t.size();
  //       edges * newNode = new edges;
  //       t.push_back(newNode);
  //       currentNode = newNode;
  //     }
  //   }
  // }
  return t;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  queue<Node> _queue;
  trie t = build_trie(text);
  for (auto i : t) {
    _queue.push(i);
    while (!_queue.empty()) {
      Node n = _queue.front();
      result.push_back(text.substr(n.suffixPos, n.suffixLength));
      _queue.pop();
      for (auto j : n.children) {
        _queue.push(j);
      }
    }
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
