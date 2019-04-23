#include <iostream>

#include <cmath>
using namespace std;
int gcd(int a, int b) {
	  if(a == 0)
		  return b;
	  if(b == 0)
		  return a;
	  int r;
	  if(a >= b){
		  r = a% b;
		  return gcd(r, b);
	  }
	  else{
		  r = b % a;
		  return gcd(r, a);
      }
}

long long lcm(int a, int b) {
    return ((long long)a * b) / gcd(a,b);
}

int fib(int n, int m) {
    int a = 0, b = 1;
    if (n <= 1)
        return n;
    int fib = 0;
    for(int i =2;i<= n;i++){
        fib = (a + b) % m;
        a = b % m;
        b = fib;
    }
    return fib;
}
int pisano_period(unsigned long long n, int m){
    int a=0, b=1, fib = 0;
    for(unsigned long long i =2; i<=n+1;i++){
        fib = (a + b) % m;
        a = b % m;
        b = fib;
        if(a% m == 0 && b % m == 1)
            return i-1;
    }
    return -1;
}

void fib_test(unsigned long long  n, unsigned long long &a, unsigned long long & b) {
    a = 0, b = 1;
    if (n <= 1)
        return;
    unsigned long long fib = 0;
    for(unsigned long long i =2;i<= n;i++){
        fib = a + b;
        a = b;
        b = fib;
    }
}
unsigned long long pisano_period_test(unsigned long long n, int m){
    unsigned long long a, b;
    for(unsigned long long i =2; i<=n;i++){
        fib_test(i+1, a, b);
        if(a% m == 0 && b % m == 1)
            return i;
    }
    return -1;
}
bool isPrime(int n){
    if(n == 2)
        return true;
    if(n%2 ==0 || n<2)
        return false;
    for (int i = 3; i<= sqrt(n); i+=2)
        if(n%i == 0)
            return false;
    return true;
}

//where n = b^k; return k
double getPowerOfBase(int n, int b){
    double k = log(n)/ log(b);
    return k;
}

double pisano(int n){
    if(n == 1)
        return 1;
    if(n == 2)
        return 3;
    if(n == 3)
        return 8;
    double k;
    //handle when n is prime...
    if(isPrime(n)){
        cout << "not handled!";
        return (n-1)/ (n%10);
    }
    for(int i=2; i<= n; i++){
        if(n%i != 0) continue;
        if(isPrime(i)){
            //general formula: if n is prime and n = i^k then p(n^k) = p(n)* n^(k-1)
            if(modf(getPowerOfBase(n, i), &k) ==0)//is n = i^k
                return pisano(i) * pow(i,k-1);
        }
        if(gcd(i, n/i)== 1){
                cout << "gcd" << i << " " << n/i << endl;
            return pisano(i) * pisano(n/i);}
    }
    return 0;
}

int main()
{
    unsigned long long n;
    int m;

    // while(true)
    //{
        cin >> n >> m;
        int p = pisano_period(n,m);
        //cout << "p: " << p << endl;

        int remainder = n% p;
        //cout << "r: " << remainder << endl;
        int f = fib(remainder, m);
        //cout << "f[r]: " << f << ", f[r] % m: " << f% m << endl;
        cout << f %m <<endl;
    //}
//    while(true)
//    {
//        cin >> n;// >> m;
//        //cout << pisano_period(n,m) << endl;
//        cout << pisano(n) << endl;
//        //cout << pisano_period_test(n,m) << endl;
//    }
//    cin >> n;

    return 0;
}
