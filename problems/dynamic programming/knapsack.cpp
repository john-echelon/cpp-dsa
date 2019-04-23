#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct knapsack_item {
    double weight, value;
};

struct knapsack {
    vector<double> amounts;
    double value = 0;
};
knapsack fractional_knapsack(vector<knapsack_item> & starterSack, double maxPayload){
    knapsack mySack;

    for(auto & starterItem : starterSack){
        if(maxPayload == 0)
            return mySack;
        //cout << startItem.value << " " << starterItem.amount << endl;
        double amountToTake = min(starterItem.weight, maxPayload);
        mySack.value += amountToTake * (starterItem.value / starterItem.weight);
        mySack.amounts.push_back(amountToTake);
        maxPayload -= amountToTake;
    }
    
    return mySack;
}
int main(){
    int n;
    double capacity;
    cin >> n >> capacity;
    vector<knapsack_item> starterSack;
    for(int i = 0; i < n;i ++){
        knapsack_item item;
        cin >> item.value >> item.weight;
        starterSack.push_back(item );
    }
    for(auto & item: starterSack){
        cout << item.value << " " << item.weight << endl;
    }
    sort(starterSack.begin(), starterSack.end(), [](knapsack_item a, knapsack_item b) {
        return (b.value/b.weight) < (a.value/a.weight);
    });
    for(auto & item: starterSack){
        cout << item.value << " " << item.weight << endl;
    }
    knapsack result = fractional_knapsack(starterSack, capacity);
    cout << result.value << endl;
    return 0;
}