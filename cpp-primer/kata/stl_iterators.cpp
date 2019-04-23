#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

void show(vector<int> & v){
    for(auto val :v)
    cout << val << ' ';
    cout << endl;
}

int main(){
    // Demonstrate the algorithm copy() for copying data from one container to another
    int casts[10] = {6, 7, 2, 9, 4, 11, 8, 7, 10, 5 };
    vector<int> dice(10);
    copy(casts, casts + 10, dice.begin()); 
    show(dice);
    
    // Demo ostream_iterator
    ostream_iterator<int, char> out_iter(cout, " ");
    copy(dice.begin(), dice.end(), out_iter);
    cout << endl;
    
    // Demo an Anonymous ostream_iterator instance
    copy(dice.begin(), dice.end(), ostream_iterator<int, char>(cout, "**"));
    cout << endl;
    
    // Demo istream_iterator
    copy(istream_iterator<int, char>(cin), istream_iterator<int, char>(), dice.begin());
    cout << endl;
    show(dice);
    
    // Demo back_insert_iterator
    vector<int> nums = {1,2,3,4,5};
    copy(dice.begin(), dice.begin()+2, back_insert_iterator<vector<int>>(nums));
    show(nums);
    
    // Demo insert_iterator
    copy(dice.begin()+2, dice.begin()+4, insert_iterator<vector<int>>(nums, nums.begin()+3));
    show(nums);
    
    // Demo front_insert_iterator
    list<int> myList(10);
    copy(nums.begin(),nums.end(),myList.begin());
    
    copy(dice.begin()+4, dice.begin()+6, front_insert_iterator<list<int>>(myList));
    copy(myList.begin(), myList.end(), ostream_iterator<int, char>(cout, " "));
    return 0;
}