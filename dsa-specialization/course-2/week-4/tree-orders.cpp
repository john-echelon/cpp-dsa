#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

  void traverse_pre_order(int vertex, vector<int> & result){
    result.push_back(key[vertex]);
    if(left[vertex] != -1)
      traverse_pre_order(left[vertex], result);
    if(right[vertex] != -1)
      traverse_pre_order(right[vertex], result);
  }
  
  void traverse_in_order(int vertex, vector<int> & result){
    if(left[vertex] != -1)
      traverse_in_order(left[vertex], result);
    result.push_back(key[vertex]);
    if(right[vertex] != -1)
      traverse_in_order(right[vertex], result);
  }
  
  void traverse_post_order(int vertex, vector<int> & result){
    if(left[vertex] != -1)
      traverse_post_order(left[vertex], result);
    if(right[vertex] != -1)
      traverse_post_order(right[vertex], result);
    result.push_back(key[vertex]);
  }
public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    traverse_in_order(0, result);
    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    traverse_pre_order(0, result);
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    traverse_post_order(0, result);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}
