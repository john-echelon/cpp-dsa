#include <iostream>

using namespace std;
int get_change(int n) {
    int coins =0;

    if(n >=10){
        coins += n/ 10;
        n%=10;
    }
    if(n>=5){
        coins += n/ 5;
        n%=5;
    }
    coins += n;
    return coins;
}

int get_change_greedy(int n, int denom[], int denomSize){

    int coins = 0;
    for (int i = 0; i < denomSize; i++) {
        if ( n >= denom[i]) {
            coins += n / denom[i];
            n %= denom[i];
        }
    }
    return coins;
}

int main() {
  int n;
  int denom[] = { 10, 5, 1 };
  std::cin >> n;
  std::cout << get_change_greedy(n, denom, 3) << '\n';
}
