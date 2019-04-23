#include <iostream>

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
	  int current_gcd = 1;
	  if(a == 0)
		  return b;
	  if(b == 0)
		  return a;
	  int ab_prime;
	  if(a >= b){
		  ab_prime = a / b;
		  return gcd_actual(ab_prime, b);
	  }
	  else{
		  ab_prime = b/ a;
		  return gcd_actual(ab_prime, a);
      }
}
int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
