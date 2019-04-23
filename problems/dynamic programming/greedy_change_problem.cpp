#include <iostream>

using namespace std;

int optimal_change(int amount){
    int num_coins = 0;
    int coins[3] = {10, 5, 1};
    for(int i =0; i<3;i++){
        while(amount >= coins[i] )
        {
            amount -= coins[i];
            num_coins++;
        }
    }
    return num_coins; 
}
int main(){
    int amount;
    cin >> amount;
    cout << optimal_change(amount); 
    return 0;
}