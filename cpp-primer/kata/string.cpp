#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
    // using string constructors
    // The class defines string::npos as the maximum possible length of the string. Typically max value of unsigned int.
    
    // display max possible length of a string
    cout << string::npos << endl; // 18446744073709551615
    
    // string(charT const* s)
    string one("Lottery Winner!"); 
    cout << one << endl; // Lottery Winner!
    
    // string(size_type count, charT ch)
    string two (20, '$'); // $$$$$$$$$$$$$$$$$$$
    cout << two << endl;
    
    string const other("Exemplary");
    // string(string const& other, size_type pos, size_type count)
    string three(other, 0, other.length()-1);
    cout << three << endl; // Exemplar
    
    // string(charT const* s, size_type count)
    string four("C-s\0tyle string", 8);
    cout << four << " " << four.length() << endl;
    
    // string(charT const* s)  a string literal that contains embedded '\0' characters stops at the null character
    string five("C-s\0tyle string");
    cout << five << " " << five.length() << endl;
    
    char mutable_c_str[] = "another C-style string";
    // string::string(InputIt first, InputIt last)
    string six(begin(mutable_c_str)+8, end(mutable_c_str)-1);
    cout << six << '\n'; // "C-style string"
    
    string six_again(mutable_c_str+8, mutable_c_str + strlen(mutable_c_str));
    cout << six_again << '\n'; // "C-style string"
    
    // string(const string& other)
    string seven(other);
    cout << seven << endl;
    
    {
        // string::string(string&& str)
        std::string s(std::string("C++ by ") + std::string("example"));
        std::cout << s << '\n'; // "C++ by example"
    }
 
    {
        // string(std::initializer_list<charT> ilist)
        std::string s({ 'C', '-', 's', 't', 'y', 'l', 'e' });
        std::cout << s << '\n'; // "C-style"
    }
    
    // overloaded +=
    one += "Oops!";
    cout << one << endl;
    
    // overload +, =
    four = two + three + two;
    cout << four << endl;
    
    // See also find, rfind, find_first_of, find_last_of, find_first_not_of, find_last_not_of
    // capacity, reserve
    // Parameters: 
    // pos	-	position at which to start the search
    // count	-	length of substring to search for
    
    // size_type find( const basic_string& str, size_type pos = 0 ) const
    string pangram("the quick brown fox jumped over the lazy dog");
    string lazy("lazy");
    cout << pangram.find(lazy) << endl; // 36
    cout << pangram.find(lazy, 37) << endl;  // 18446744073709551615
    
    // size_type find( const CharT* s, size_type pos, size_type count ) const;
    cout << pangram.find("og", 0, 1) << endl; // 12
    cout << pangram.find("og", 0, 2) << endl; // 42
    
    // size_type find( const CharT* s, size_type pos = 0 ) const;
    cout << pangram.find("lazy") << endl; // 36
    cout << pangram.find("lazy", 37) << endl;  // 18446744073709551615
    
    //size_type find( CharT ch, size_type pos = 0 ) const;
    cout << pangram.find('o') << endl; // 12
    cout << pangram.find('o', 13) << endl; // 42
    
    // find_first_of
    // Finds the first character equal to one of the characters in the given character sequence. The search considers only the interval [pos, size()). If the character is not present in the interval, npos will be returned.
    return 0;
}