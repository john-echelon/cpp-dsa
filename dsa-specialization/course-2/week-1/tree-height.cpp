#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class TreeHeight {
  int n;             
  std::vector<int> parent;

public:
  void read() {
    std::cin >> n;
    parent.resize(n);
    for (int i = 0; i < n; i++)
      std::cin >> parent[i];
  }
  
  int compute_height2() {
    int maxHeight = 0;
    int root;
    vector<vector<int>> tree (n);
    //find root index and children
    for(int i =0; i < n; i++){
      if(parent[i] == -1)
        root = i;
      else {
        tree[parent[i]].push_back(i);
      }
    }
    vector<int> subheights;
    for(int j = 0; j< tree[root].size();++j){
      subheights.push_back ( 1 + height(tree[root][j], tree));  
    }
    /*
    for(int j=0; j< n; j++){
      if(parent[j] == root){
        subheights.push_back(1 + height(j));
      }
    }
    */
    //for(auto k : subheights)
    //cout << "values:" << k << endl;
    if(subheights.size() == 0)
      return 1;
    return *std::max_element(subheights.begin(), subheights.end());
  }
  
  int height(int i, vector<vector<int>> & tree){
    vector<int> subheights;
    
    for(int j=0; j< tree[i].size(); ++j){
      /*if(parent[j] == childIndex){
        subheights.push_back(1 + height(j));
      }*/
      subheights.push_back(1 + height(tree[i][j], tree));
    }
    if(subheights.size() == 0)
      return 1;
    return *std::max_element(subheights.begin(), subheights.end());
  }
  
  int compute_height() {
    // Replace this code with a faster implementation
    int maxHeight = 0;
    for (int vertex = 0; vertex < n; vertex++) {
      int height = 0;
      for (int i = vertex; i != -1; i = parent[i])
        height++;
      maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
  }
};

int main() {
  //while(true){
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height2() << std::endl;
  //}
}
