#include <iostream>
#include <vector>

using std::pair;
using std::swap;
using std::vector;

pair<int, int> partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  int m1 = j, m2 = j;
  while(m1 > l && a[m1] == a[j])
    m1--;
  // Uncomment for cout debug info
  // if (m1 != m2) {
  //   std::cout << std::endl;
  //   for (int i = m1; i <= m2; i++)
  //     std::cout << i << " " << a[i] << "\n";
  //   std::cout << std::endl;
  // }
  pair<int, int> m{m1, m2};
  return m;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  pair<int, int> m = partition2(a, l, r);

  randomized_quick_sort(a, l, m.first - 1);
  randomized_quick_sort(a, m.second + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
