#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <typeinfo>
#include "linked-list.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::copy;
using std::list;
using std::ostream_iterator;
int main()
{
    LinkedList<std::string> data;
    data.push_back("hello");
    data.push_back("world");
    data.push_front("^");
    data.push_back("$");
    
    for(LinkedList<string>::iterator ptr = data.begin(); ptr != data.end(); ptr++ )
        cout << *ptr<< " ";
    cout << endl;
    
    //init list
    int myInts[] = { 10, 3, 7, 5 };
    list<int> eList(myInts, myInts + sizeof(myInts) / sizeof(int));
    ostream_iterator<int, char> out (cout, " ");
    
    //show list
    copy(eList.begin(), eList.end(), out);
    cout << endl;
    
    //show inserted list
    list<int>::iterator itl = eList.begin();
    ++itl;       
    eList.insert (itl,2);
    copy(eList.begin(), eList.end(), out);  cout << endl;
    
    //show reverse list
    copy(eList.rbegin(), eList.rend(), out);
    cout << endl;
    
    //init custom list
    LinkedList<int> aList;
    aList.push_back(10);
    aList.push_back(3);
    aList.push_back(7);
    aList.push_back(5);
    
    //show custom list
    copy(aList.begin(), aList.end(), out);  cout << endl;
    
    //show inserted custom list
    LinkedList<int>::iterator it = aList.begin();
    ++it;       
    aList.insert (it,2);
    copy(aList.begin(), aList.end(), out);  cout << endl;
    
    //show reverse custom list
    copy(aList.rbegin(), aList.rend(), out);  cout << endl;
    return 0;
}