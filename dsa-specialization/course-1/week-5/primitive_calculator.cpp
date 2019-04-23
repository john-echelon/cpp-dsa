#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using std::vector;
using namespace std;
vector<int> optimal_sequence(int n, vector<int> &m) {
  int original_n = n;
  std::vector<int> sequence;
  int x, y;
  while (n >= 1) {
    sequence.push_back(n);
    x = y = original_n; 
    if (n % 3 == 0) {
      x = n/3;
    } 
    else if (n % 2 == 0) {
      x = n/2;
    }
    y = n - 1;
    
    n =m[x] <=m[y] ? x : y;
  }
  reverse(sequence.begin(), sequence.end());
    return sequence;
}
vector<int> dp(int n) {
  std::vector<int> m(n+1);
  
  m[1] = 0;
  
  int x, y;
  for(int i =1; i<=n;i++){
    x = y = INT_MAX;  
    if (i % 3 == 0) {
      x = m[i/3];
    } 
    else if (i % 2 == 0) {
      x = m[i/2];
    } 
    y = m[i-1];
    
    m[i] = min(x,y)+1;
  }
  return optimal_sequence(n, m);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = dp(n);

  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
    //std::cout << i << ":" << sequence[i] << " ";
  }
}
