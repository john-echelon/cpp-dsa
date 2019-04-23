#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
unsigned long long m;

unsigned long long getAddress(unsigned long long x){
    unsigned long long a= 1, b = 2, p=10000019;
    unsigned long long h = ((a*x + b) % p)%m;
    return  h;
}

 long long hash_func(const string& s,  long long multiplier,  long long prime) {
     long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}

int main()
{
    long long multiplier= 263, prime= 1000000007;
    while(true){
        string pattern, text;
        cin >> pattern >> text;
        for(int i =0 ;i<= text.size() - pattern.size(); ++i)
            cout <<text.substr(i, pattern.size()) << " " << hash_func(text.substr(i, pattern.size()), multiplier, prime) << endl;
    }
}
/*

int main() {
    int n; unsigned long long x;
    while(true){
        cin >> n >>  m;
        for(int i =0; i <n;i++)
        {
           cin >> x;
           cout << x << " " << getAddress(x) << endl;
        }
        cout << "new set:\n";
    }
    return 0;
}
*/