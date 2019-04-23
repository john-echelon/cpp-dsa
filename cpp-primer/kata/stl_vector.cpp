#include <iostream>
#include <vector>
using namespace std;
void show(vector<int> & v){
    for(auto val :v)
    cout << ' ' << val;
    cout << endl;
}
int main(){
    //constructors
    
    //demonstrate fill constructor
    vector<int> v1(4, 9999);
    //demonstrate range constructor
    vector<int> v2(v1.begin(), v1.end());
    //demo copy constructor
    vector<int> v3(v2);
    //demo initializer list constructor
    int myInts[] = {16, 2, 77, 29};
    vector<int> v4(myInts, myInts + sizeof(myInts)/sizeof(int));
    //demo iterating through a vector using iterator and output its contents
    for(vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
        cout << ' ' << *it;
    cout << endl;
    
    //assign elements to a vector using vector::assign and a range (or fill)
    vector<int> v5;
    v5.assign(v4.begin(), v4.begin()+2);
    
    //Add element at end
    v5.push_back(27);
    //Delete last element
    v5.pop_back();
    //Insert a single element
    v5.insert(v5.begin(), 101);
    //Insert a range
    v1.insert(v1.end(), v5.begin(), v5.end());
    //Iterate results 
    show(v1); 
    //Erase using iterator position
    v1.erase(v1.begin()+5);
    //Iterate results
    show(v1); 
    //Erase using range
    v1.erase(v1.begin()+1,v1.begin()+4);
    show(v1);
    //Iterate results
    //Swap and show contents of vectors
    cout << "Swapping...\n";
    v1.swap(v5);
    show(v1);
    show(v5);
    
    //Clear vector contents
    v5.clear();
    return 0;
}