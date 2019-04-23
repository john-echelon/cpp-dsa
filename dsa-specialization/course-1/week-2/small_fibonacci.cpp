#include <iostream>
#include <stdlib.h>     /* srand, rand */
using namespace std;
int calc_fib(int n) {
    if (n < 2)
        return n;

    return calc_fib(n - 1) + calc_fib(n - 2);
}

int calc_fib_actual(int n) {
    if (n < 2)
        return n;
    int a = 0, b = 1, fib = 0;
    for(int i =2;i<= n;i++){
        fib = a + b;
        a = b;
        b = fib;
    }
    return fib;
}
void stress_test(){
    int n = 0;
    int expected, actual;
    do{
        n = rand() % 46; //0 to 45
        cout << "n is " << n << endl;
        expected = calc_fib(n);
        actual = calc_fib_actual(n);
        if(expected == actual)
            std::cout << "OK, Results Match: " << expected << " : "<< actual << endl;
        else{
            std::cout << "FAIL, Mismatch!: " << expected << " : "<< actual << endl;
            break;
        }
    }while(expected == actual);
}

void actual_test(){
    int n = 0;
    std::cin >> n;

    std::cout << calc_fib_actual(n) << '\n';
}
int main() {
    //stress_test();
    actual_test();
    return 0;

}
