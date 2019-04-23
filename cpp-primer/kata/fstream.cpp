#include <iostream>
#include <fstream>
using namespace std;

void example1(){
    char str[100];
    ofstream a_file("example.txt", ios::trunc);
    //ios::app   -- Append to the file
    //ios::ate   -- Set the current position to the end
    //ios::trunc -- Delete everything in the file
    a_file << "Hello World!";
    a_file.close();
}

void example2(){
    char str[100];
    ifstream ifs("example.txt");
    if(!ifs.is_open()){
        cout << "File could not be opened!";
    }else {
        ifs.getline(str, 100);
        cout << str << endl;
    }
    //ifs is closed implicitly here 
    
}
int main(){
    //TODO: Demonstrate a file write.
    example1();
    //TODO: Demonstrate a file read.
    example2();
    return 0;
}