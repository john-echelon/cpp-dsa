#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    unsigned int n;
    unsigned int s,p,q;
    cin >> n >> s >> p >> q;
    
    unsigned int m = ((unsigned int)1 <<31);

    set<unsigned int> arr;
    unsigned int key = (s % m);
    arr.insert(key);
    for(int i = 1; i< n; ++i){
        key = abs((key *p)%m + (q % m));
        
        // cout << "key " << key << endl;
        if (arr.find(key) == arr.end()) {
            arr.insert(key);
        }
    }
    cout << arr.size();
    
    return 0;
}