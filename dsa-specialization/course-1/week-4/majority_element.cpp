#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using std::vector;
//Sub-optimal divide and conquer method: runs in O(n log n)
int get_majority_element_divide_conquer(vector<int> &a, int left, int right) {
    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    //split to 2 sub-partitions and get majority elements
    int subSize = ((right-left)/ 2); //n/2, where n is size of partition
    int mid = left + subSize;
    int lMaj = get_majority_element_divide_conquer(a, left, mid);
    int rMaj = get_majority_element_divide_conquer(a, mid, right);

    if(lMaj == rMaj)
        return lMaj;

    int lCount = 0, rCount = 0;
    for(int i =left; i< right; i++){
        if(lMaj == a[i])
            lCount++;
        if(rMaj == a[i])
            rCount++;
    }
    if(lCount > subSize)return lMaj;
    if(rCount > subSize)return rMaj;
    return -1;
}

//A more optimal method: runs in O(n)
int get_majority_element_optimal(vector<int> &a) {
    int count = 0; int maj;
    for(int i =0; i< a.size(); i++){
        if(count == 0)
            maj= a[i];
        if(a[i] == maj)
            count++;
        else count--;
    }
    count = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] == maj)
            count++;
    }
    if (count > a.size()/2)
        return maj;
  return -1;
}

int main() {
    int n;
    //while(true){
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    //std::cout << (get_majority_element_optimal(a) != -1) << '\n';
    std::cout << (get_majority_element_divide_conquer(a, 0, a.size()) != -1) << '\n';
    a.clear();

    //}
}
