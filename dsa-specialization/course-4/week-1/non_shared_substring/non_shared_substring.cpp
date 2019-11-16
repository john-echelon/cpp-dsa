#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::string;
using std::queue;
using std::vector;

using namespace std;

int const NA = -1;
const unsigned char left_suffix = 0x1;
const unsigned char right_suffix = 0x2;
struct Node {
  int suffixPos;
  int suffixLength;
  Node * parent = NULL;
  int startPos = NA;
  vector<Node *> children;
  unsigned char lr = 0;
  int depth = 0;
};
typedef Node trie;

void update_parent_lr(Node * current) {
  while(current->parent != NULL) {
    current->parent->lr |= current->lr;
    current = current->parent;
  }
}
void update_lr(Node * current, int textLength, int pLen) {
  int actualStart = current->startPos != NA ? current->startPos : current->suffixPos;
  int actualLen = current->startPos != NA ? textLength - actualStart : current->suffixLength;
  int endPos = actualStart + actualLen - 1;
  if (actualStart < pLen) {
    current->lr |= left_suffix;
  }
  if (actualStart >= pLen) {
    current->lr |= right_suffix;
  }
  update_parent_lr(current); 
}
trie build_trie(const string & text) {
  int length = (int) text.size();
  int pLen = text.find('#');
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
        tNode->depth = parent->depth + 1;
        update_lr(tNode, text.length(), pLen); 
        //update sibling
        sib->suffixPos += numSuffixMatch;
        sib->suffixLength -= numSuffixMatch;
        sib->parent = tNode;
        sib->depth = tNode->depth + 1;

        // attach as child under new suffix node
        tNode->children.push_back(sib);
        update_lr(sib, text.length(), pLen); 
        // remove current sib
        parent->children.erase(current->children.begin() + childIndex);

        // new suffix node under parent
        parent->children.push_back(tNode);

        foundMatch = true;
        Node * tNode2 = new Node { k, length - k, tNode, i };
        tNode->children.push_back(tNode2);
        tNode2->depth = tNode->depth + 1;
        update_lr(tNode2, text.length(), pLen); 
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
      tNode->depth = tNode->parent->depth + 1;
      current->children.push_back(tNode);
      update_lr(tNode, text.length(), pLen); 
      current = &t;
      i++;
    } 
  }
  return t;
}

auto cmp = [] (Node * left, Node * right) { 
  int leftLen, rightLen;
  if (left->startPos == NA) {
    Node * leftAnc = left;
    Node * leftPrevAnc;
    Node * leftLen = 0;
    // get top level node to get substring length
    do {
      leftPrevAnc = leftAnc;
      // leftLen += leftAnc->suffixPos - leftAnc->suffixLength;
      leftLen += leftAnc->suffixLength;
      leftAnc = leftAnc->parent;
    } while (leftAnc != NULL);
  } else {
    leftLen = left->suffixPos - left->startPos + 1;
  }
  if (right->startPos == NA) {
    Node * rightAnc = right;
    Node * rightPrevAnc;
    Node * rightLen = 0;
    // get top level node to get substring length
    do {
      rightPrevAnc = rightAnc;
      // rightLen += rightAnc->suffixPos - rightAnc->suffixLength;
      rightLen += rightAnc->suffixLength;
      rightAnc = rightAnc->parent;
    } while (rightAnc != NULL);
  } else {
    rightLen = right->suffixPos - right->startPos + 1;
  }
  if (leftLen == rightLen) {
    return left->depth < right->depth;
  }
  return leftLen > rightLen;
};
void PruneSuffixTree(Node * t, string & text, int pLength, priority_queue<Node *, vector<Node *>, decltype(cmp)> & patterns) {
  int textLength = text.length();
  queue<Node *> _queue;
  _queue.push(t);
  while (!_queue.empty()) {
    Node * n = _queue.front();
    _queue.pop();
    int i = n->children.size() - 1;
    vector<Node *>::iterator it = n->children.begin();
    for (vector<Node *>::reverse_iterator rit = n->children.rbegin(); rit != n->children.rend(); ++rit, --i) {
      Node * child = *rit;
      Node * current = child;
      _queue.push(child);
      int actualStart = current->startPos != NA ? current->startPos : current->suffixPos;
      int actualLen = current->startPos != NA ? textLength - actualStart : current->suffixLength;
      if (current->depth < 5) {
      cout << "current: " << &(*current) << " parent " << &(*current->parent) << ": "<< text.substr(actualStart, actualLen) << " startPos " << current->startPos
        << " suffixPos " << current->suffixPos << " suffixLength " << current->suffixLength << " depth " << current->depth
        << " left " << (current->lr & left_suffix) <<" right " << (current->lr & right_suffix) << endl;
      }
      bool isLeftQualified =
        ((current->lr & left_suffix) == left_suffix) && ((current->lr & right_suffix) != right_suffix)
        ||
        ((current->lr & left_suffix) != left_suffix) && ((current->lr & right_suffix) != right_suffix);
      // if (isLeftQualified && current->startPos < pLength && current->suffixPos < pLength) 
      if (isLeftQualified && current->startPos < pLength)
      {
        if (current->depth < 5)
        cout << "Added\n";
        patterns.push(current);
      }
    }
  }
}
string solve (string p, string q, bool runOnce = false)
{
  string text = p + "#" + q + "$"; 
  // cout << "p length " << p.length() << endl;
  trie t = build_trie(text);
  Node * parent = &t;
  priority_queue<Node *, vector<Node *>, decltype(cmp)> patterns(cmp);
  PruneSuffixTree(parent, text, p.length(), patterns);
  while (!patterns.empty()) {
  auto * pattern = patterns.top();
  Node * top = patterns.top();
  patterns.pop();
  int substrPos = top->startPos != NA ? top->startPos : top->suffixPos;
  cout << "top " << top << " " << text.substr(substrPos, p.length() - substrPos)<< endl;
  if (pattern->startPos == NA) {
    // cout << "startPos " << pattern->startPos << " subLen " << pattern->suffixLength << endl;
    // string result = text.substr(pattern->suffixPos, pattern->suffixLength);
    string result = text.substr(pattern->suffixPos, 1);
    while (pattern->parent != parent) {
      pattern = pattern->parent;
      result = text.substr(pattern->suffixPos, pattern->suffixLength) + result;
    }
    string nextResult = result;
    return nextResult;
  } else if (pattern->startPos != NA && pattern->suffixPos != p.length()) {
    cout << "!!!!!NA!!!\n";
    int subLen = pattern->suffixPos - pattern->startPos + 1;
    return text.substr(pattern->startPos, subLen); 
  }
  }
  return p;
  // return "unknown";
}

int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);

	cout << ans << endl;

	return 0;
}
/*
Pseudo code solution for problem 5:

build suffix tree based on text1#text2

Pattern match using a breadth first traverse of suffix tree nodes
  based pattern as a length i from 1 to text1.length
    increment i for each complete breadth first traverse
    match is positive if traversal finds a node whose children matches pattern of length i,
      where a substring pos matches pattern before the # but not after # position
*/
/*
Test Cases
Input:
AAAAC
AAACA

Correct output:
AAAA
*/