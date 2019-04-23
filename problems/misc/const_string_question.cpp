#include <iostream>
#include <string>
using namespace std;
// does passing c style string int (const *c) create a copy? 
class Tester {
    public:
    const char * foo(){
        string str;
        cin >> str;
        const char * c = str.c_str();
        const char *d = str.c_str();
        cout << "mem c from str.c_str() in foo " << &c << endl;
        cout << "mem d from str.c_str() in foo " << &d << endl;
        return c;
    }
    
    ~Tester(){ cout << "Destructor called!\n";}
};

void bar (const char * c){
    Tester t;
    cout << "mem c in bar " << &c << endl;
    c = t.foo(); 
    cout << "mem c in bar " << &c << endl;
}
int main(){
    string s = "hello"; 
    const char * c = s.c_str();
    
    cout << "mem c in main " << &c << endl;
    bar(c);

    cout << "mem c in main " << &c << endl;
    cout << "s " << s <<  ", c " << c << endl;
    return 0;
}