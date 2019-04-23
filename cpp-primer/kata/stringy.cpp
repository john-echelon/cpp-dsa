#include <iostream>
#include <cstring>
//#include <ostream>
//#include <istream>
#include "stringy.h"
using namespace std;
int Stringy::num_strings = 0;

//constructors and other member methods
Stringy::Stringy(){
    str = new char[1];
    str[0] = '\0';
    len = 0;
    ++num_strings;
}

Stringy::Stringy(const char *s){
    //assumes s is bounded by newline char 
    len = strlen(s);
    str = new char[len+1];
    strncpy(str, s, len);
    str[len] = '\0';
    ++num_strings;
}

Stringy::Stringy(const Stringy & other){
    len = other.len; 
    str = new char[len+1];
    strcpy(str, other.str);
    ++num_strings;
}

Stringy::~Stringy(){
    delete [] str;
    len = 0;
    --num_strings;
}

Stringy & Stringy::operator=(const Stringy & other){
    if(this == &other)
        return *this;
    delete [] str;
    len = strlen(other.str); 
    str = new char[len+1];
    strncpy(str, other.str, len);
    str[len] = '\0';
    ++num_strings;
    return *this;
}

Stringy & Stringy::operator=(const char * s){
   len = strlen(s);
   str = new char[len+1];
   strcpy(str, s);
   ++num_strings;
   return *this;
}

char & Stringy::operator[](int i){ return str[i]; }

const char & Stringy::operator[](int i)const { return str[i]; }

// overloaded operator friend
bool operator<(const Stringy & st1, const Stringy & st2){
    return strcmp(st1.str, st2.str) < 0;
}

bool operator>(const Stringy & st1, const Stringy & st2){
    return strcmp(st1.str, st2.str) > 0;
}

bool operator==(const Stringy & st1, const Stringy & st2){
    return strcmp(st1.str, st2.str) == 0;
}

ostream & operator<<(ostream & os, const Stringy &st){
    os << st.str;
    return os;
}

istream & operator>>(istream & is, Stringy & st){
    is >> st.str;
    return is;
}
// static function
int Stringy::HowMany(){ return Stringy::num_strings; }
int main (){
    Stringy s;
    cin >> s;
    cout << s << ":" << s.length() << endl;
    Stringy s2("world!");
    cout << s2;
    return 0;
    
}