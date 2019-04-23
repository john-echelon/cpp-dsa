using std::ostream;
using std::istream;
#ifndef STRINGY_H_
#define STRINGY_H_
class Stringy {
private: 
   char * str;			    //pointer to Stringy
   int len;			        //length of Stringy
   static int num_strings;		//number of objects
public:
//constructors and other methods
   Stringy();			    //default constructor
   Stringy(const char *s);	//constructor
   Stringy(const Stringy &);	//copy constructor
   ~Stringy();			    //destructor
   int length()const {return len; }
//overloaded operator methods
   Stringy & operator=(const Stringy &);
   Stringy & operator=(const char *);
   char & operator[](int i);
   const char & operator[](int i) const;
//overloaded operator friends
   friend bool operator<(const Stringy & st1, const Stringy & st2);
   friend bool operator>(const Stringy & st1, const Stringy & st2);
   friend bool operator==(const Stringy & st1, const Stringy & st2);
   friend ostream & operator<<(ostream & os, const Stringy & st);
   friend istream & operator>>(istream & is,  Stringy & st);
//static function
   static int HowMany();
};
#endif