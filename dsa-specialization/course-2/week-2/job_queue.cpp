#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;

class JobQueue {
 private:
  long long num_workers_;
  vector<long long> jobs_;

  vector<long long> assigned_workers_;
  vector<long long> start_times_;

  vector<pair<long long, long long> > data_;

  long long size;
  
  // void BuildHeap(){
  //   size = num_workers_-1;
  //   for(long long i = 0; i < num_workers_; ++i)
  //   {
  //   data_.push_back(make_pair(i, 0));
  //   }
  // }
  
  long long Parent(long long i){ return ((i+1)/2)-1; }
  
  long long LeftChild(long long i){ return (2*(i+1))-1; }//2*i for 1 based-index
  
  long long RightChild(long long i){ return 2*(i+1); }//2*i+1 for 1 based-index
  
  void SiftDown(long long i){
    long long maxIndex = i;
    long long l = LeftChild(i);
    long long r = RightChild(i);
    if(l <= size && r <= size && data_[l].second == data_[r].second &&
    data_[l].second <= data_[maxIndex].second){
      if(data_[l].first < data_[r].first)
          maxIndex = l;
      else maxIndex = r;
    }
    else {
      if(l <= size && (data_[l].second < data_[maxIndex].second ||
        (data_[l].second == data_[maxIndex].second && data_[l].first < data_[maxIndex].first)))
        maxIndex = l;
  
      if(r <=size && (data_[r].second < data_[maxIndex].second ||
        (data_[r].second == data_[maxIndex].second && data_[r].first < data_[maxIndex].first)))
        maxIndex = r;
    }
    if(i != maxIndex)
    {
      std::swap(data_[i], data_[maxIndex]);
      SiftDown(maxIndex);
    }
  }
  
  void SiftUp(long long i){
    while(i >0 && ( data_[Parent(i)].second > data_[i].second || 
      (data_[Parent(i)].second == data_[i].second && data_[Parent(i)].first > data_[i].first )))
    {
      std::swap(data_[Parent(i)], data_[i]);
      i = Parent(i);
    }
  }
  
  void Insert(long long p){
    if(size == num_workers_-1)
    {
      std::cerr << "cannot insert; max size reached!";
      return;
    }
    data_.push_back(make_pair(++size, p));
    SiftUp(size);
  }
  void ChangePriority(long long i, long long p){
    long long oldp = data_[i].second;
    data_[i].second = p;
    if(p < oldp)
      SiftUp(i);
    else
      SiftDown(i);
  }
  
  void WriteResponse() const {
    for (long long i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    long long m;
    cin >> num_workers_ >> m;
    //BuildHeap();
    size= -1;
    jobs_.resize(m);
    for(long long i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    long long i;
    int min = (num_workers_ < jobs_.size())? num_workers_ : jobs_.size();
    for(i =0; size<min-1; i++){
      assigned_workers_[i] = i;
      start_times_[i] = 0;
      Insert(jobs_[i]);
    }
    for (; i < jobs_.size(); ++i) {
      assigned_workers_[i] = data_[0].first;
      start_times_[i] = data_[0].second;
      ChangePriority(0, data_[0].second + jobs_[i]);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
