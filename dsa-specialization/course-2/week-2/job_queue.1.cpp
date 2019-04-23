#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <queue>
using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
		std::clock_t start;
		start = std::clock();

		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());

		auto pair_comp = [](const std::pair<int, int>& e1, const std::pair<int, int>& e2)
		{ 
			if (e1.first == e2.first){
				return e1.second > e2.second;
			}
			else{
				return e1.first > e2.first;
			}
		};

		auto greater_comp = [](const int& e1, const int& e2)
		{
			return e1 > e2;
		};

		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(pair_comp)> queue;
		std::priority_queue<int, std::vector<int>, decltype(greater_comp)> availThread;

		for (int i = 0; i < num_workers_; ++i){
			availThread.push(i);
		}

		int duration = 0;

		for (int i = 0; i < jobs_.size(); ++i) {
			int thread;
			if (availThread.size() > 0){
				thread = availThread.top();
				availThread.pop();
				std::pair<int, int> item = std::make_pair(duration + jobs_[i], thread);
				queue.push(item);
			}
			else{
				std::pair<int, int> next = queue.top();
				queue.pop();
				duration = next.first;
				thread = next.second;
				std::pair<int, int> item = std::make_pair(duration + jobs_[i], thread);
				queue.push(item);
			}

			assigned_workers_[i] = thread;
			start_times_[i] = duration;
		}


		std::cout << "printf: " << (double) ((std::clock() - start) / (double)CLOCKS_PER_SEC) << '\n';
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