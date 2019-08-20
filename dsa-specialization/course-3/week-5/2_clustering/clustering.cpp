#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using std::pair;
using std::priority_queue;



class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const pair<double, pair<int, int>> &lhs, const pair<double, pair<int, int>> &rhs) const
  {
    if (reverse) return (lhs.first > rhs.first);
    else return (lhs.first < rhs.first);
  }
};
typedef std::priority_queue<pair< double, pair<int,int>>, std::vector<pair<double, pair<int,int>>>, mycomparison> heap;

double calc_distance(pair<int, int> p1, pair<int, int> p2) {
  double x = p1.first - p2.first;
  double y = p1.second - p2.second;
  return sqrt(pow(x, 2) + pow(y, 2));
}
void make_set(int i, int parents[]) {
  parents[i] = i;
}
// path compression
int find_set(int i, int parents[]) {
  if(parents[i] != i) {
    parents[i] = find_set(parents[i], parents);
  }
  return parents[i];
}
void union_set (int x, int y, int parents[]) {
  int setX = find_set(x, parents);
  int setY = find_set(y, parents);
  if (setX != setY) {
    parents[setX] = setY; 
  }
}
double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
  int n = x.size();
  int parents[n];
  for (size_t i = 0; i < n; i++) {
    make_set(i, parents);
  }
  heap plots(mycomparison(true));
  heap result_plots(mycomparison(false));
  for (size_t i = 0; i < n-1; i++) {
    for (size_t j = i+1; j < n; j++) {
      pair<int, int> p1(x[i], y[i]); pair<int, int> p2(x[j], y[j]);
      double minDist = calc_distance(p1, p2);
      plots.push(pair<double, pair<int, int>>(minDist, pair<int, int>(i, j)));
    }
  }
  int num_unions = 0;
  while (!plots.empty() && num_unions < n-1)
  {
    pair< double, pair<int,int>> plot = plots.top();
    plots.pop();
    int u = find_set(plot.second.first, parents);
    int v = find_set(plot.second.second, parents);
    if (u != v) {
      union_set(u, v, parents);
      num_unions++;
      result_plots.push(plot);
    }
  }
  for (int i = 1; i < k-1 && !result_plots.empty(); i++) {
    result_plots.pop();
  }
  pair< double, pair<int,int>> largestPlot = result_plots.top();
  return largestPlot.first;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
