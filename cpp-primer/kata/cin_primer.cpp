#include <iostream>
#include <string>
#include <limits>
using namespace std;

void example1(){
    int age; char name[30];
    cout << "Enter name ";
    cin >> name;
    cout << "Enter age ";
    cin >> age;
    
    cout << name << " " << age;
}

void example2(){
    int age; char name[30];
    cout <<"Enter name ";
    cin.get(name, 30);
    cout <<"Enter age ";
    cin >> age;
    cout << name << " " << age;
}

void example3(){
    char fname[30], lname[30];
    cout <<"Enter first name ";
    cin.get(fname, 30);
    cin.get();
    cout <<"Enter last name ";
    cin.get(lname, 30);
    cout << fname << " " << lname;
}

void example4(){
    int age; char name[30];
    cout <<"Enter name ";
    cin.getline(name, 30);
    cout <<"Enter age ";
    cin >> age;
    cout << name << " " << age;
}

void example5(){
    int age; string name;
    cout <<"Enter name ";
    getline(cin, name);
    cout <<"Enter age ";
    cin >> age;
    cout << name << " " << age;
}

void example6(){
    float fl;
    while(!(cin >> fl)){
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    cout << fl;
    //http://www.augustcouncil.com/~tgibson/tutorial/iotips.html
}

void example7(){
    char input[100];
    char ch; int i=0;
    while(cin.get(ch)){
        if(ch == '\n')
        break;
        else input[i++] = ch; 
    }
    cout << input;
}

int main(){
    //Write a function to input name (no spacing) and age using cin to output name age
    //example1();
    //Now do the same using cin.get(char *, int)
    //example2();
    //The problem with cin. Write two input statements for first name and last name using cin.get(char *, int) and output the full name.
    //Notice the newline is preserved in the stream buffer and sent to the next available cin.get stream.
    //The get() leaves the newline character in the input queue, whereas the getline() reads and discards the newline character.
    //This also applies if the first input statement was inputted via cin, followed by cin.getline(char * streamsize n).
    //Use cin.get() or cin.ignore() to fix this.
    //example3();
    //Now enter the full name (with spacing) using cin.getline(char *, streamsize n), followed by the age in the next input
    //example4();
    //Now enter the full name (with spacing) using getline(istream & is, string & str), followed by the age in the next input
    //example5();
    //Write a function that inputs a numeric input using cin, and repeatedly ignores the input if the input is invalid (e.g. not a number)
    //Otherwise, output the number
    //example6();
    //TODO: Write a cin.get(char) while loop for input and use EOF to indicate end of input. Output the input.
    //example7();

    return 0;
}