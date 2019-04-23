#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;
using std::vector;

struct Segment {
  int start, end;
  bool operator < (const Segment& seg) const { return end < seg.end; }
};
bool contains(vector<int> points, int x){
    for(int i=0; i< points.size(); ++i){
        if(points[i]== x)
        return true;
    }
    return false;
}

vector<int> optimal_points(vector<Segment> &segments) {

  vector<int> points;
  std::sort(segments.begin(), segments.end());

    int min_index = segments[0].end;
    points.push_back(min_index);
  //write your code here
  for (size_t i = 1; i < segments.size(); ++i) {
    if(segments[i].start <= min_index && min_index <= segments[i].end ){
        if(!contains(points, min_index))
            points.push_back(min_index);
    }
    else
    {
        min_index = segments[i].end;
        if(!contains(points, min_index))
            points.push_back(min_index);
    }
  }
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
