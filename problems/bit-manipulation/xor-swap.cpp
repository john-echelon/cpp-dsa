#include <iostream>

using namespace std;
void flip(int *a, int *b)
{
    *a = *a ^ *b;
    // Now, we can recover *a_orig by applying *a XOR *b_orig
    *b = *a ^ *b;
    // So we have the following situation:
    // The value originally stored in *a, a_orig, is now in *b
    // and *a still stores a_orig ^ b_orig
    // This means that we can recover the value of b_orig by applying 
    // the XOR operation to *a and a_orig.  Since *b stores a_orig...
    *a = *a ^ *b;
}

int main()
{
	int a, b;
	while (true) {
		cin >> a >> b;
	    flip(&a, &b);
		cout << a << " " << b;
	}
}