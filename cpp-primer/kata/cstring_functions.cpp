#include <iostream>
#include <cstring>
using namespace std;

void ex1(){
    char str1[] = "Sample string";
    char str2[20];
    strcpy(str2, str1);
    cout << str2 << " " << strlen(str2);
}

void ex2(){
    //strcpy will overflow the memory in str2
    char str1[] = "Sample string";
    char str2[8];
    strcpy(str2, str1);
    cout << str2 << " " << strlen(str2);
}

void ex3(){
    char str1[] = "Sample string";
    char str2[50];
    strncpy(str2, str1, strlen(str1));
    cout << str2 << " " << strlen(str2);
}

void ex4(){
    char str1[] = "Sample string";
    char str2[8];
    strncpy(str2, str1, strlen(str1));
    cout << str2 << " " << strlen(str2);
}

void ex5(){
    char str1[] = "alpha";
    char str2[] = "bravo";
    cout << strcmp(str1, str2);
}

void ex6(){
    char str1[50], str2[50], str3[100];
    cin.getline(str1, 50);
    cin.getline(str2, 50);
    strcat(str3, str1);
    strcat(str3, " ");
    strcat(str3, str2);
    cout << str3;
}

int main(){
    // Demonstrate strcpy where dest is long enough to contain the source. Output the dest and strlen.
    //ex1();
    
    // Demonstrate strcpy where dest is short enough to demonstrate overflow. Output the dest and strlen.
    //ex2();
    
    // Demonstrate strncpy where dest is long enough to contain the source. Output the dest and strlen.
    //ex3();
    
    // Demonstrate strncpy where dest is short enough to demonstrate overflow. Output the dest and strlen.
    ex4();
    
    // Demonstrate strcmp
    //ex5();
    
    // Prompt for a first and last name. Concat first and last seperated by a space using strcat. Output the full name.
    //ex6();
    return 0;
}