#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges *> trie;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

trie build_trie(const vector<string> & patterns) {
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
        // cout << "adding " << symbol << " at node " << t.size() << endl;
        edges * newNode = new edges;
        t.push_back(newNode);
        currentNode = newNode;
      }
      if (i == s.size() - 1) {
        // indicate we arrived at a leaf
        (*currentNode)['$'] = NA;
        // cout << "marking as leaf\n";
      }
    }
  }
  return t;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

	// write your code here
  trie t = build_trie(patterns);
  // for (size_t i = 0; i < t.size(); ++i) {
  //   for (const auto & j : (*t[i])) {
  //     std::cout << i << "->" << j.second << ":" << j.first << "\n";
  //   }
  // }
  for (int i = 0; i < text.size(); i++) {
    int j = i;
    // cout << "next i " << i << endl;
    char symbol = text[j];
    edges * v = t[0];
    bool cont = true;
    while (cont) {
      if ((*v).find('$') != (*v).end()) {
        result.push_back(i);
        // cout << "$ at " << i << endl;
      }
      if ((*v).find(symbol) != (*v).end()) {
        int nodeIndex = (*v)[symbol];
        // cout << "symbol " << symbol << "->" << nodeIndex << "\n";
        v = t[nodeIndex];
        if (j < text.size() - 1) {
          symbol = text[++j];
          // cout << "next symbol " << symbol << endl;
        }
        else {
          cont = false;
          if ((*v).find('$') != (*v).end()) {
            result.push_back(i);
            // cout << "$ at " << i << endl;
          }
          // cout << "j boundary\n";
        }
      } else {
        cont = false;
        // cout << "no match\n";
      }
      // cout << "loop";
    }
  }
  sort( result.begin(), result.end() );
  result.erase( unique(result.begin(), result.end() ), result.end() );
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}

/*
Sample Inputs
Input:
AATCGGGTTCAATCGGGGT
2
ATCG
GGGT
Output:
1 4 11 15
*/