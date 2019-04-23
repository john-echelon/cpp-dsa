#include <iostream>
#include <vector>
using namespace std;
using std::vector;
bool contains(vector<int> items, int x){
    for(int i=0; i< items.size(); ++i){
        if(items[i]== x)
        return true;
    }
    return false;
}

vector<int> optimal_summands(int n, int i=1) {
  vector<int> summands;
  //write your code here
  if(n<=2)
        summands.push_back(n);
  else{
      int j= i;
      int temp = n;

      for(;i<=n;++i){
        if(n <= 2* i)  {
          summands.push_back(n);
                break;
        }
        else {
            summands.push_back(i);
            n-=i;
         }
//        if(!contains(summands, n-i)){
//            summands.push_back(i);
//            n-=i;
//        }
//        else{
//            summands.push_back(n);
//                break;
//        }
      }
//      int sum=0;
//      for (int n : summands)
//        sum+= n;
//       if(temp!= sum){
//         //summands.clear();
//         return optimal_summands(temp, ++j);
//       }
  }
  return summands;
}

int main() {
    int n;
    //while(true){
        std::cin >> n;
        vector<int> summands = optimal_summands(n);
        std::cout << summands.size() << '\n';
        for (size_t i = 0; i < summands.size(); ++i) {
            std::cout << summands[i] << ' ';
        }
    //    cout <<endl;
    //}
}
