#include <iostream>
#include <vector>

using std::vector;
using namespace std;
void merge(vector<int> &arr, int first, int last, long long & number_of_inversions)
{
	int * temp = new int[last - first + 1];
	int mid =first + (last - first) / 2;
	int i1 = 0, i2 = first, i3 = mid + 1;
	while (i2 <= mid && i3 <= last) { //while both left and right subarrays of arr contain elements
		if (arr[i2] <= arr[i3]){
			temp[i1++] = arr[i2++];
		}
		else{
			number_of_inversions += mid+1-i2; 
		  temp[i1++] = arr[i3++];
		}
			
	}
	//load into temp the remaining elements
	while (i2 <= mid) {
		temp[i1++] = arr[i2++];
	}
	while (i3 <= last) {
		temp[i1++] = arr[i3++];
	}
	i1 = 0;
	//load to arr the content of temp
	for (int i = first; i <= last; i++) {
		arr[i] = temp[i1++];
	}
	delete[] temp;
	
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right < left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave+1, right);
  //write your code here
  merge(a, left, right, number_of_inversions);
  return number_of_inversions;
}


int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()-1) << '\n';
  // for (size_t i = 0; i < a.size(); i++) {
  //   cout << a[i] << ' '	;
  // }
}