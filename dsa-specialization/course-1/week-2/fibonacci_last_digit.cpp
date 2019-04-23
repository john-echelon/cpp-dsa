#include <iostream>
#include <stdlib.h>     /* srand, rand */
using namespace std;
int calc_fib(int n) {
    if (n <= 1)
        return n;

    return calc_fib(n - 1) + calc_fib(n - 2);
}

int get_fibonacci_last_digit(int n) {
    if (n <= 1)
        return n;
    int a = 0, b = 1, fib = 0;
    for(int i =2;i<= n;i++){
        fib = (a + b)%10;
        a = b;
        b = fib;
    }
    return fib;
}


void actual_test(){
    int n = 0;
    //while(true){
        std::cin >> n;
        int c = get_fibonacci_last_digit(n);
        std::cout << c << '\n';
    //}
}
int main() {
    actual_test();
    return 0;

}
