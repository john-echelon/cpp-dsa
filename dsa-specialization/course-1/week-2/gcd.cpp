#include <iostream>
#include <stdlib.h>
using namespace std;
int gcd(int a, int b) {
  //write your code here
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_actual(int a, int b) {
	  if(a == 0)
		  return b;
	  if(b == 0)
		  return a;
	  int r;
	  if(a >= b){
		  r = a% b;
		  return gcd_actual(r, b);
	  }
	  else{
		  r = b % a;
		  return gcd_actual(r, a);
      }
}

long long lcm(int a, int b) {
    return ((long long)a * b) / gcd_actual(a,b);
}
void gcd_stress_test(){
    int a, b;
    int expected, actual;
    int i =0;
    do{
        a = rand() % 1000+1;
        b = rand() % 1000+1;
        cout << "a: " << a << " b:" << b << endl;
        expected = gcd(a, b);
        actual = gcd_actual(a, b);
        if(expected == actual)
            std::cout << "OK, Results Match: " << expected << " : "<< actual << endl;
        else{
            std::cout << "FAIL, Mismatch!: " << expected << " : "<< actual << endl;
            break;
        }
        i++;
    }while(expected == actual);
}

int main() {
  int a, b;
  while(1){
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;}
  //gcd_stress_test();
  return 0;
}
