#include <iostream>

using namespace std;

int example1(int (*arg)[4], int size){
    int sum = 0;
    for(int i=0; i<size;++i){
        for(int j=0;j<4;++j)
            sum += arg[i][j];
    }
    return sum;
}

int main(){

    // Declare and initialize 3x4 int array in one line
    int data[3][4] = { {1,2,3}, {4,5,6}, {7,8,9}};
    
    // Declare and allocate memory a 3x4, two dimensional int array: 
    int (* ar)[4] = new int[3][4];
    
    // Write a function that takes in a pointer-to-array-of-four-int and returns the total of all elements
    cout << example1(data, 3);
    return 0;
    
    // Deallocate the two dimensional array
    delete ar;
    
    // Declare and allocate a 5x4, two dimensional jagged array
    int ** jagged = new int*[5];
    for(int i=0; i<5; ++i)
        jagged[i] = new int[4];
    
    // Deallocate the two dimensional arry
    for(int i=0; i<5; ++i)
        delete[] jagged;
    
}