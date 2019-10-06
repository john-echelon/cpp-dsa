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
    current->lr|= left_suffix;
    // current->parent->lr|= left_suffix;
  }
  if (actualStart >= pLen) {
    current->lr |= right_suffix;
    // current->parent->lr|= right_suffix;
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
        sib->depth = parent->depth + 1;

        // attach as child under new suffix node
        tNode->children.push_back(sib);
        update_lr(sib, text.length(), pLen); 
        // remove current sib
        parent->children.erase(current->children.begin() + childIndex);

        // new suffix node under parent
        parent->children.push_back(tNode);

        // foundMatch = true;
        Node * tNode2 = new Node { k, length - k, tNode, i };
        tNode->children.push_back(tNode2);
        tNode2->depth = parent->depth + 1;
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

bool EvaluateSuffixTree(Node * t, const string & p) {
  queue<Node *> _queue;
  _queue.push(t);
  while (!_queue.empty()) {
    Node * n = _queue.front();
    Node * current = n;
    cout << "evaluating.. " << &(*n) << endl;
    cout << "current: " << &(*current) << " parent " << &(*current->parent) << " startPos" << current->startPos
      << " suffixPos " << current->suffixPos << " suffixLength " << current->suffixLength << " depth " << current->depth
      << " left " << (current->lr & left_suffix) <<" right " << (current->lr & right_suffix) << endl;
    if (n->startPos != NA && n->startPos > p.length()) 
      return true;
    _queue.pop();
    for (auto j : n->children) {
      int startingPos = j->startPos != NA ? j->startPos : j->suffixPos; 
      if (j->startPos != NA || j->startPos == NA && startingPos < p.length()) {
        _queue.push(j);
      }
    }
  }
  return false;
}
auto cmp = [] (Node * left, Node * right) { 
if (left->depth == right->depth) {
  int lStart = left->startPos != NA ? left->startPos : left->suffixPos;
  int rStart = right->startPos != NA ? right->startPos : right->suffixPos;
  return lStart > rStart;
}
return left->depth > right->depth;
};
// Optimization: Remove internal nodes that whose suffix does not contain p text (text1)
void PruneSuffixTree(Node * t, string & text, int pLength, priority_queue<Node *, vector<Node *>, decltype(cmp)> & patterns) {
  int textLength = text.length();
  queue<Node *> _queue;
  int result = 1;
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
      cout << "current: " << &(*current) << " parent " << &(*current->parent) << ": "<< text.substr(actualStart, actualLen) << " startPos" << current->startPos
        << " suffixPos " << current->suffixPos << " suffixLength " << current->suffixLength << " depth " << current->depth
        << " left " << (current->lr & left_suffix) <<" right " << (current->lr & right_suffix) << endl;
      if (((current->lr & left_suffix) == left_suffix) && ((current->lr & right_suffix) != right_suffix) ||
      ((current->lr & left_suffix) != left_suffix) && ((current->lr & right_suffix) != right_suffix)
      ) {
        cout << "Added\n";
        patterns.push(current);
      }
      // if (!prune) {
      //   ++result;
      //   _queue.push(child);
      // }
      // else if ((child->startPos != NA || (child->startPos == NA && child->suffixPos < pLength))) {
      //   ++result;
      //   _queue.push(child);
      // }
      // else 
      //   n->children.erase(it + i, it + i + 1);
    }
  }
  // return result;
}
int reduce(string p, string q) {
  int dupes = 1, prev = 1;
  for (int i = 1; i < p.length() && i < q.length(); i++) {
    if (p[i] == p[i - 1] && p[i-1] == q[i-1]) {
      ++dupes;
    }
    else {
      return 1;
    }
  }
  return dupes;
}

bool allCharactersSame(string s) 
{ 
  return (s.find_first_not_of(s[0]) == string::npos); 
} 
string solve (string p, string q)
{
  string text = p + "#" + q + "$"; 
  // int dupes = reduce(p, q);
  // // cout << "dupes " << dupes << endl;
  // string q2 = q;
  // reverse(q2.begin(), q2.end());
  // dupes = max(dupes, reduce(p, q2));
  // // cout << "dupes " << dupes << endl;
  // cout << "p length " << p.length() << endl;
  trie t = build_trie(text);
  Node * parent = &t;
  priority_queue<Node *, vector<Node *>, decltype(cmp)> patterns(cmp);

  bool allSame = allCharactersSame(p);
  if (allSame) {
    Node * tNode = new Node{ 0, (int) p.length() };
    patterns.push(tNode);
  } else {
    PruneSuffixTree(parent, text, p.length(), patterns);
  }
  // cout << "size " << PruneSuffixTree(parent, text, p.length())<< endl;
  // cout << "prune size " << PruneSuffixTree(parent, p.length(), true) << endl;
  stack<Node *> _stack;
  vector<Node *> leaves;
  map<int, int> cache;
  map<string, int> pattern_cache;
  int i = 0;
  int numEvaluations = 0;
  int numEvaluationsAvoided = 0;
  int numTraversalsAvoided = 0;
  // while(!patterns.empty()) {
  //   auto * pattern = patterns.top();
  //   patterns.pop(); 
  //   int actualStart = pattern->startPos != NA ? pattern->startPos : pattern->suffixPos;
  //   i = actualStart;
  //   int actualLen = pattern->startPos != NA ? text.length() - actualStart : pattern->suffixLength;
  //   cout << "pattern: " << &(*pattern) << " parent " << &(*pattern->parent) << ": "<< text.substr(actualStart, actualLen) << " startPos" << pattern->startPos
  //     << " suffixPos " << pattern->suffixPos << " suffixLength " << pattern->suffixLength << " depth " << pattern->depth
  //     << " left " << (pattern->lr & left_suffix) <<" right " << (pattern->lr & right_suffix) << endl;
  // }
  while(!patterns.empty()) {
    auto * pattern = patterns.top();
    patterns.pop(); 
    int actualStart = pattern->startPos != NA ? pattern->startPos : pattern->suffixPos;
    i = actualStart;
    int actualLen = pattern->startPos != NA ? text.length() - actualStart : pattern->suffixLength;
    cout << "pattern: " << &(*pattern) << " parent " << &(*pattern->parent) << ": "<< text.substr(actualStart, actualLen) << " startPos" << pattern->startPos
      << " suffixPos " << pattern->suffixPos << " suffixLength " << pattern->suffixLength << " depth " << pattern->depth
      << " left " << (pattern->lr & left_suffix) <<" right " << (pattern->lr & right_suffix) << endl;
    for (int j = 1; i + j <= p.length(); j++, i = actualStart) {
    for (; i + j <= p.length();++i) {
      cout << text.substr(i, j) << "( " << i << ", " << j << " )" << endl;
      int currentPos = i;
      int currentLength = j;
      // Optimization: Avoid previously matched substrings from repeated traversal.
      string key = text.substr(i, j);
      if (pattern_cache.find(key) != pattern_cache.end()) {
        pattern_cache[key] = pattern_cache[key]++;
        numEvaluationsAvoided++;
        // cout << "skipped! \n";
        continue;
      } else {
        pattern_cache[key] = 1;
        numEvaluations++;
      }
      vector<Node *> & children = parent->children;
      for (int h = 0; h < children.size(); h++) {
        _stack.push(children[h]);
        while(!_stack.empty()) {
          Node * current = _stack.top();
          _stack.pop();
          int startingPos = current->startPos != NA ? current->startPos : current->suffixPos; 
          if (startingPos >= p.length()) {
            numTraversalsAvoided++;
            continue;
          }
          if (current->startPos != NA) {
            // cout << "found a leaf\n";
            if (current->suffixLength -1 >= j && text.substr(i, j) == text.substr(current->startPos, j)) {
              // found a match at a leaf; evaluate leaf
              // cout << "found a leaf match\n";
              if (current->startPos < p.length()) {
                // cout << "leaf.numEvaluations: " << numEvaluations << endl;
                // cout << "numEvaluationsAvoided: " << numEvaluationsAvoided << endl;
                // cout << "numTraversalsAvoided: " << numTraversalsAvoided << endl;
                return text.substr(i, j);
              }
            }
          } else {
            int delta = currentLength - current->suffixLength;
            int minLength = min(current->suffixLength, currentLength);
            if (text.substr(currentPos, minLength) == text.substr(current->suffixPos, minLength)) {
              if (delta <= 0) {
                // found a match at internal node, evaluate its leaves
                // cout << "found a internal node match, evaluate leaves ... \n";
                // cout << "current: " << &(*current) << " " << (int)&(*current) << " startPos" << current->startPos
                //   << " suffixPos " << current->suffixPos << " suffixLength " << current->suffixLength << endl;
                // bool matchFoundAfterHash = EvaluateSuffixTree(current, p);
                // cout << "matchFound " << matchFoundAfterHash << " left " << (current->lr & left_suffix) <<" right " << (current->lr & right_suffix) << endl;
                // if (!matchFoundAfterHash) {
                if (((current->lr & left_suffix) == left_suffix) && ((current->lr & right_suffix) != right_suffix) ||
                  ((current->lr & left_suffix) != left_suffix) && ((current->lr & right_suffix) != right_suffix)) {
                  // cout << "internal.numEvaluations: " << numEvaluations << endl;
                  // cout << "numEvaluationsAvoided: " << numEvaluationsAvoided << endl;
                  // cout << "numTraversalsAvoided: " << numTraversalsAvoided << endl;
                  return text.substr(i, j);
                }
                // move to next node in stack
              } else {
                // partial match at internal node, continue search with children
                // cout << "found a partial match, cont searching\n";
                currentLength = delta;
                currentPos += current->suffixLength;
                for (auto * child : current->children) {
                    _stack.push(child);
                }
              }
            }
          }
        }
      }
      if (allSame) {
        break;
      }
    }
  }
  }

	string result = p;
  // cout << "none.numEvaluations: " << numEvaluations << endl;
  // cout << "numEvaluationsAvoided: " << numEvaluationsAvoided << endl;
  // cout << "numTraversalsAvoided: " << numTraversalsAvoided << endl;
	return result;
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