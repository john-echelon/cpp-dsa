#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define ll long long
#define pb push_back
#define mp make_pair
 
 
int main()
{
  int n, k;
  cin>>n>>k;
  int a[n];
  // memset(a, 0, sizeof(a));
  int e = 0, p; //excess, previous
  cin>>p;
  int ans = 0;
  for (int i = 0; i < n-1; ++i){
    int h;
    cin>>h; //current
    int x = h + p - e; //x = total
     cout << "hpe " << h << " " << p << " " << e << endl;
     cout << "min " << x-k << endl;
    e = 0;
    p = h;
    if (x > k){
      ans += x-k;
      e = min(x-k, h);
     
    }
   
  }
  cout<<ans;
    return 0;
}
