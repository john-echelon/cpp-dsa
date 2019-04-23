#include <iostream>
#include <limits>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

int is_valid_char(int c){
    return ispunct(c) || isspace(c);
}
bool palindrome(string str){
    //transform str in place to lower case

    transform(str.begin(), str.end(), str.begin(), ::tolower);
    str.erase(remove_if(str.begin(), str.end(), is_valid_char), str.end());

    string::iterator i = str.begin();
    string::reverse_iterator j = str.rbegin();
    int mid = str.size()/2;
    for(int k=0; k<mid; i++, j++, k++){
            if(*i != *j) return false;
    }
    return true;
}
int main()
{
   string input;
   while( getline(cin, input)){
    cout << palindrome(input) << endl;
   }


    return 0;
}
