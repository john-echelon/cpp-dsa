#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using namespace std;

void output_alignment(int i, int j, vector<vector<int>> &lookup, vector<int> &a, vector<int> &b, vector<int> &track){
  if(i == 0 && j == 0)
    return;
  
  if(i >0 && lookup[i][j] == (lookup[i-1][j] +1)){
    output_alignment(i-1, j, lookup, a, b, track);
    //cout << a[i-1] << " | -" << endl;
  }
  else if (j > 0 && lookup[i][j] == (lookup[i][j-1] +1)){
    output_alignment(i, j-1, lookup, a, b, track);
    //cout  <<"- | " << b[j-1] << endl;
  }
  else { //(lookup[i][j] == lookup[i-1][j-1])
    output_alignment(i-1, j-1, lookup, a, b, track);
    //cout << a[i-1] << " | " << b[j-1] << endl;
    if(a[i-1] == b[j-1])
      track.push_back(a[i-1]);
  }
}

int edit_distance(vector<int> &a, vector<int> &b, vector<int> & track) {
  int n = a.size();
  int m = b.size();
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
      
      if(a[i-1] == b[j-1])
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
  }
  */
  //cout << "outputting alignment:\n";
  output_alignment(n, m, lookup, a, b, track);
  return lookup[n][m];
}

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  vector<int> track_ab, track_ac, track_bc;
  int ab = edit_distance(a, b, track_ab);
  int ac = edit_distance(a, c, track_ac);
  int bc = edit_distance(b, c, track_bc);
  /*int minSize = std::min(std::min(a.size(), b.size()), c.size());
  if(ab == minSize || ac == minSize)
    return 0;*/
  int minSize = std::min(track_ab.size(), track_ac.size());
  if(minSize == 0)
    return 0;
  
  int lcs3_ab_ac = 0, lcs3_ac_bc = 0;
  for(int i =0;i< minSize;i++){
    if(track_ab[i]== track_ac[i])
      ++lcs3_ab_ac;
    if(track_ac[i]== track_bc[i])
      ++lcs3_ac_bc;
  }
  
  return max(lcs3_ab_ac, lcs3_ac_bc);
  //return std::min(ab, ac);
}

int main() {
  size_t an;
  //while(true){
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
  //}
}
