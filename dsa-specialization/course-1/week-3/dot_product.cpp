#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using namespace std;
long long min_dot_product(vector<int> a, vector<int> b) {
  // write your code here
  long long result = 0;

  std::sort(b.begin(), b.end());
  std::sort(a.begin(), a.end());
  std::reverse(a.begin(), a.end());
  for (size_t i = 0; i < a.size(); i++) {
    result += (long long) a[i] * b[i];
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << min_dot_product(a, b) << std::endl;
}
