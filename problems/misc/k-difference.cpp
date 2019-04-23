#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>

using std::cout;
using std::cin;
using std::endl;
using namespace std;

int kDifference(vector < int > a, int k) {
    set<pair<int,int>> s;
    
    for(int i =0; i<a.size();i++){
        for(int j =1; j<a.size()-1;j++){
            if(abs(a[i]-a[j]) == k){
                bool skip = false;
                for(set<pair<int,int>>::iterator iter = s.begin(); iter != s.end(); ++iter){
                    if(((*iter).first == a[i] && (*iter).second == a[j]) || ((*iter).first == a[j] && (*iter).second == a[i])){
                        skip = true;
                        break;
                    }
                }
                if(!skip)
                    s.insert(make_pair(a[i], a[j]));
            }
        }
    }
    return s.size();
}
int main()
{
    int arr[] = {1,1,3,5,3,4,2};
    
    vector<int> a(7);
    copy(arr, arr+7, a.begin());
    int ans = kDifference(a, 2);
    cout << ans << ' ';
    
    
    vector<int> b;
    b.push_back(9);
    b.push_back(8);
    insert_iterator<vector<int>> ins(a, a.begin()+1);
    copy(b.begin(), b.end(), ins);
    cout << endl;
    for(auto i : a){
        cout << i << ' ';
    }
    return 0;
}

/*
Test case
6

1
12
5
3
4
2

2
*/