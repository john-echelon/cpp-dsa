#include <iostream>
#include <vector>
#include <stdlib.h>
using std::vector;
using std::swap;
using namespace std;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}


int partition3(vector<int> &a, int l, int r, int & low) {
  int x = a[l];
  int j = l;
  low = -1;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      if(a[i] == x) low++;
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  int left = l, right = j-1;
  while (left< right){
    while(a[right] == x) right--;
    while(a[left] != x) left++;
    if(left< right)
        swap(a[left++],a[right++]);
  }
  if(low == -1) low=0;
  return j;
}


void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  //int m = partition2(a, l, r);
  int low=0;
  int m = partition3(a, l, r, low);
  randomized_quick_sort(a, l, m - low - 1);
  randomized_quick_sort(a, m + 1, r);
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
