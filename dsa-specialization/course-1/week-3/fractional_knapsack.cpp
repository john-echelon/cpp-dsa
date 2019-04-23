#include <iostream>
#include <vector>
using namespace std;
int get_max_index(vector<int> weights, vector<int> values){
    int max_index = 0;
    for(int i = 1; i< weights.size(); i++){
        if(weights[i]==0 || values[i] ==0) continue;
        if((double)values[i]/weights[i] > (double)values[max_index]/weights[max_index])
            max_index = i;
    }
    return max_index;
}


double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double value = 0.0;
    for(int i = 0; i< weights.size(); i++){
        if (capacity == 0)
            break;
        int max_index= get_max_index(weights, values);
        if(weights[max_index]>0)
        {
            if( capacity >= weights[max_index]){
                value += values[max_index];
                capacity-= weights[max_index];
            }
            else{
                double fractional = values[max_index] *((double)capacity / weights[max_index]);
                value += fractional;
                capacity = 0;
            }
        }

        values[max_index]=0;//mark to ignore
    }
    return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
