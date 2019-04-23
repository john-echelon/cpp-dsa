#include<iostream>
#include<cstring>
using namespace std;

int reverse(char * str){
    char tmp;
    char * end = str + strlen(str)-1;
    /*while(*end){ //find end of string
        ++end;
    }
    --end; //set one char back, since last char is null
   */
   
    while(str < end){
        tmp = *str;
        *str++ = *end;
        *end-- = tmp;
    
    }
}
int main()
{
    while(true){
        char str[20];
        cin >> str;
        reverse(str);
        cout << str << endl;
    }
}