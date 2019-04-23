#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  vector<vector<int>> matrix (W+1, vector<int> (w.size()+1));
  
  for(int i=1; i<=w.size();i++)
    matrix[0][i] = 0;
  for(int i=1; i<=W;i++)
    matrix[i][0] = 0;
    
  int val;
  for (size_t i = 1; i <= w.size(); ++i) {
    for(int j=1; j<=W; j++){
      matrix[j][i] = matrix[j][i-1];
      if(w[i] <= j){
        val = matrix[j-w[i]][i-1] + w[i];
        if(matrix[j][i] < val)
          matrix[j][i] = val;
      } 
    }
  }
  return matrix[W][w.size()];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n+1);
  w[0] = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
