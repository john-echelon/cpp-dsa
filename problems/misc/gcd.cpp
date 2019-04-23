#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b){
    if (b == 0)
        return a;
    int r = a%b;
    cout << b << ", " << r << endl; 
    return gcd(b, r);
}

int gcd_iterate(int a, int b){
    while(b != 0){
        cout << a << ", " << b << endl;
        int r = a %b;
        a = b;
        b = r;
    }
    return a;
}
int gcd_subtract(int a, int b){
    while(a != b)
    {
        if(a > b)
            a-= b;
        else b-=a;
        cout << a << ", " << b << endl;
    }
    return a;
}
int main(){
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    cout << gcd_subtract(a, b) << endl;
    cout << gcd_iterate(a, b) << endl;
    
    return 0;
}