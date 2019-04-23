#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

/*
Bottom-up approach

mincoinchange(W)
  mincoins[W] = fill 0
  for(w: 1 to W)
    mincoins[w] = max value
    for(i: |coins|)
      if (coin[i] <= w)
        val = mincoins[w- coin[i]] +1
        if(val < mincoins[w])
          mincoins[w] = val
  return mincoins[W]
*/

int min_coin_change(int money, vector<int> & coins){
    vector<int> minCoins(money+1, 0);
    for(int m=1;m <= money; ++m){
        minCoins[m] = numeric_limits<int>::max();
        for(int i =0;i<coins.size();++i){
            int val;
            if(coins[i] <= m){
                val = minCoins[m - coins[i]] +1;
                if(val < minCoins[m])
                    minCoins[m] = val;
            }
        }
    }
    return minCoins[money];
}
/*
Top-down approach

mincoins[0] = 0
mincoins[1...W-1] = fill max value

mincoinchange(W)
  if(W ==0) return 0;
  if(mincoins(W) != max value)
    return mincoins(W);
  for(i : |coins|)
    if(coins[i] <= W)
      val = mincoinchange(W-coins[i]) +1
      if(val < mincoins(W))
        mincoins[W] = val
  return mincoins(W)
*/

int min_coin_change_top_down(int money, vector<int> & coins){
    vector<int> minCoins(money+1, numeric_limits<int>::max());
    if(money == 0) return 0;
    if(minCoins[money] != numeric_limits<int>::max())
        return minCoins[money];
    for(int i =0; i< coins.size(); ++i){
        int val;
        if(coins[i] <= money){
            val = min_coin_change_top_down(money - coins[i], coins) + 1;
            if(val < minCoins[money])
                minCoins[money] = val;
        }
    }
    return minCoins[money];
}

int main(){
    int numCoins, value;
    cin >> numCoins;
    vector<int> myCoins;
    for(int i =0;i<numCoins;++i)
    {
        cin >> value;
        myCoins.push_back(value);     
    }
    int amount;
    cin >> amount;
    cout << min_coin_change(amount, myCoins) << endl;
    cout << min_coin_change_top_down(amount, myCoins);
    
    return 0;
}