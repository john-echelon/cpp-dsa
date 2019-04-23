#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main(){
    list<int> one(5, 2);
    int stuff[5] = {1, 2, 4, 8, 6};
    list<int> two;
    two.insert(two.begin(), stuff, stuff + 5);
    int more[6] = {6, 4, 2, 4, 6, 5};
    list<int> three(two);
    three.insert(three.end(), more, more +6);
    
    cout << "List one: ";
    ostream_iterator<int, char> out(cout, " ");
    copy(one.begin(), one.end(), out);
    
    cout << endl << "List two: ";
    copy(two.begin(), two.end(), out);
    
    cout << endl << "List three: ";
    copy(three.begin(), three.end(), out);
    
    cout << endl << "List three minus 2s: ";
    three.remove(2);
    copy(three.begin(), three.end(), out);
    
    cout << endl << "List three after splice: ";
    three.splice(three.begin(), one);
    copy(three.begin(), three.end(), out);
    
    cout << endl << "List one: ";
    copy(one.begin(), one.end(), out);
    
    cout << endl << "List three after unique: ";
    three.unique();
    copy(three.begin(), three.end(), out);
    
    cout << endl << "List three after sort & unique: ";
    three.sort();
    three.unique();
    copy(three.begin(), three.end(), out);
    
    cout << endl << "Sorted two after merge into three: ";
    two.sort();
    three.merge(two);
    copy(three.begin(), three.end(), out);
    return 0;
}