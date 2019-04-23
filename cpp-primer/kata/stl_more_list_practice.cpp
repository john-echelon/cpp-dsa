#include <iostream>
#include <limits>
#include <cctype>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <ctime>
using namespace std;

void container_practice(){
    
    vector<int> test(10, 1);
    for(auto i: test) cout << i << " "; cout << endl; 
    vector<int> other = { 11,12,13 };
    test.assign(other.begin(), other.end());
    for(auto i: test) cout << i << " " ; cout << endl; 
    
    test.assign(10, 1); 
    test.assign(4, 7);
    for(auto i: test) cout << i << " " ; cout << endl;
    // 1 1 1 1 1 1 1 1 1 1 
    // 11 12 13 
    // 7 7 7 7 
}


bool isgt_ten(int n){ return n > 10; }

void list_practice(){
  //Additional Methods for lists
   list<string> words1 {"the", "quick", "the", "lazy", "dog",};
   list<string> words2 {"brown", "fox", "jumped", "over"};
   
    for(auto i: words1) cout << i << " "; cout << endl;
    auto it = words1.begin();
    advance(it, 2);
    words1.splice(it, words2);
    for(auto i: words1) cout << i << " "; cout << endl;
    list<string> words3 { "with sox", "with locks", "with clocks", "with blocks" };
    
    it = words1.begin();
    advance(it, 4);
    words1.splice(it, words3, words3.begin());
    for(auto i: words1) cout << i << " "; cout << endl;
    for(auto i: words3) cout << i << " "; cout << endl;
    
    words1.splice(it, words3, words3.begin(), words3.end());
    for(auto i: words1) cout << i << " "; cout << endl;
    
    std::list<int> l = { 1,100,2,3,10,1,11,-1,12 };
 
    l.remove(1); // remove both elements equal to 1
    l.remove_if(isgt_ten);
    //l.remove_if([](int n){ return n > 10; }); // remove all elements greater than 10
 
    for (int n : l) {
        std::cout << n << ' '; 
    }
    std::cout << '\n';
}

int main(){
    // list_practice();
    container_practice();
    return 0;
}