#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::vector;

using namespace std;

int const NA = -1;
struct Node {
  int suffixPos;
  int suffixLength;
  Node * parent = NULL;
  int startPos = NA;
  vector<Node *> children;
};
// typedef map<char, int> edges;
typedef Node trie;

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
  trie t = { NA, NA, NULL, NA };
  Node * firstNode = new Node { 0, length, &t, 0 };
  t.children.push_back(firstNode);
  trie * current = &t;
  int k;
  bool contSearch = false;
  int i = 1;
  while (i < length) {
    if (!contSearch)
      k = i; // current index of subtext
    contSearch = false;
    bool foundMatch = false;
    for (int childIndex = 0; childIndex < current->children.size(); childIndex++) {
      Node * sib = current->children[childIndex];
      int j;
      for (j = sib->suffixPos; (j < sib->suffixPos + sib->suffixLength) && k < length && text[k] == text[j]; j++, k++);
      
      int numSuffixMatch = j - sib->suffixPos;
      if (numSuffixMatch == 0) {
        continue;
      }
      foundMatch = true;
      if (numSuffixMatch < sib->suffixLength) {
        // partial suffix match; we split nodes
        Node * parent = current;
        // split node under root
        Node * tNode = new Node { sib->suffixPos, numSuffixMatch, parent };

        //update sibling
        sib->suffixPos += numSuffixMatch;
        sib->suffixLength -= numSuffixMatch;
        sib->parent = tNode;

        // attach as child under new suffix node
        tNode->children.push_back(sib);
        // remove current sib
        parent->children.erase(current->children.begin() + childIndex);

        // new suffix node under parent
        parent->children.push_back(tNode);

        // foundMatch = true;
        Node * tNode2 = new Node { k, length - k, tNode, i };
        tNode->children.push_back(tNode2);
        current = &t;
        i++;
        break;
      } else {
        // update currentSubText position;
        current = sib;
        contSearch = true;
        break;
      }
    }
    if (!foundMatch) {
      // No match found
      Node * tNode = new Node { k, length - k, current, i };
      current->children.push_back(tNode);
      current = &t;
      i++;
    } 
  }
  return t;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  queue<Node *> _queue;
  trie t = build_trie(text);
  for (auto i : t.children) {
    _queue.push(i);
    while (!_queue.empty()) {
      Node * n = _queue.front();
      result.push_back(text.substr(n->suffixPos, n->suffixLength));
      _queue.pop();
      for (auto j : n->children) {
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

/*
Input:
AAA$

Your output:
A
A$
$
A

$

Correct output:
$
$
$
A
A
A$
*/