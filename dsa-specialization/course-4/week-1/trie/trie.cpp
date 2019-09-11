#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges *> trie;

using namespace std;
trie build_trie(vector<string> & patterns) {
  trie t;
  edges * rootNode = new edges;
  t.push_back(rootNode);
  int nodeCount = 0;
  // write your code here
  for (string s : patterns) {
    edges * currentNode = t[0];
    for (int i = 0; i < s.size(); i++) {
      char symbol = s[i];
      // if there is an outgoing edge from currentNode with label currentSymbol:
      if ((*currentNode).find(symbol) != (*currentNode).end()) {
        int nodeIndex = (*currentNode)[symbol];
        currentNode = t[nodeIndex];
      } else {
        (*currentNode)[symbol] = t.size();
        edges * newNode = new edges;
        t.push_back(newNode);
        currentNode = newNode;
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : (*t[i])) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}