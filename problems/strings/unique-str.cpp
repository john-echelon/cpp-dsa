#include <iostream>
#include <cstring>
using namespace std;
bool isUnique(char str[], int n) {
	int flag = 0;
	for (int i = 0; i < n; ++i) {
		int val = tolower(str[i]) - 'a';
		if ((flag & (1 << val))>0)
			return false;
		cout << "val: " << val << endl;
		flag |= (1 << val);

		//cout << flag;
	}
	return true;
}


int main()
{
	char input[10];
	while (true) {
		cin >> input;
		cout << endl << isUnique(input, strlen(input)) << endl;
	}
}