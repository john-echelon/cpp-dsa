#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  int size;
  int Parent(int i){ return i/2; }
  
  int LeftChild(int i){ return (2*(i+1))-1; }//2*i for 1 based-index
  
  int RightChild(int i){ return 2*(i+1); }//2*i+1 for 1 based-index
  
  void SiftDown(int i){
    int maxIndex = i;
    
    int l = LeftChild(i);
    if(l <= size && data_[l] < data_[maxIndex])
      maxIndex = l;
    int r = RightChild(i);
    if(r <=size && data_[r] < data_[maxIndex])
      maxIndex = r;
    if(i != maxIndex)
    {
      std::swap(data_[i], data_[maxIndex]);
      swaps_.push_back(make_pair(i, maxIndex));
      SiftDown(maxIndex);
    }
  }
  
  void BuildHeap(){
    size =data_.size()-1;
    for(int i= (data_.size()-1)/2; i>=0; --i) {
      SiftDown(i);
    }
  }

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }
  
  void HeapSort(){
    int tmp = size;
    for(int i=1; i<=tmp; ++i){
      swap(data_[0], data_[size--]);
      SiftDown(0);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    BuildHeap();
    return;
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
