#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int feast(int n, int c, int m){
    /*
    int chocs = n/c;
    int total = chocs;
    int wrappers = chocs;
    chocs = wrappers/m;
    while(chocs > 0){
        total+= chocs;//5+2,+1,+1
        wrappers = chocs + (wrappers%m);//2+1,1+1,1+0
        chocs = wrappers/m;//1,1,0
    }
    return total;
    */
    int boughtCandy = n/ c;
    return boughtCandy + (boughtCandy - 1)/ (m-1);
}
int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int c;
        int m;
        cin >> n >> c >> m;
        cout << feast(n, c, m) << endl;
    }
    return 0;
}