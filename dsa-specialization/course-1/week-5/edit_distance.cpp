#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using namespace std;
int edit_distance(const string &str1, const string &str2) {
  int n = str1.length();
  int m = str2.length();
  vector<vector<int>> lookup(n+1, vector<int>(m+1));
  
  for(int j=0; j<=m;j++)
    lookup[0][j] = j;
  for(int i=0; i<=n;i++)
    lookup[i][0] = i;
      
  for(int j=1; j<=m; ++j){
    for(int i=1; i<=n; ++i){
      int ins = lookup[i][j-1] +1;
      int del = lookup[i-1][j] +1;
      int mat = lookup[i-1][j-1];
      int mis = lookup[i-1][j-1] +1;
      
      if(str1[i-1] == str2[j-1])
        lookup[i][j] = min(min(ins, del), mat);
      else
        lookup[i][j] = min(min(ins, del), mis);
    }
  }
  /*
  for(int i=0; i<=n; ++i){ 
    for(int j=0; j<=m; ++j){
      cout << lookup[i][j] << " ";
    }
  cout << endl;
  
  }*/
  return lookup[n][m];
}

int main() {
  string str1;
  string str2;
  while(true){
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
  }
  return 0;
}