#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t, n;
    cin >> t;
    vector<vector<int>> results(t);
    for(int i=0; i < t; i++){
        cin >> n; 
        vector<int> elements;
        int max_contiguous = 0;
        int max_non_contiguous = 0;
        int max_element = numeric_limits<int>::min();
        for(int j= 0; j < n; j++){
            int ele;
            cin >> ele;
            max_element = max(max_element, ele);
            if (ele > 0)
                max_non_contiguous += ele;
            if (j==0) {
                elements.push_back(ele);
                max_contiguous = ele;
            }
            else {
                int val = elements[j-1] + ele;
                if (val > ele)
                    elements.push_back(val);
                else 
                    elements.push_back(ele);
                max_contiguous = max(max_contiguous, elements.back());
            }
            /*
            if (ele > 0) {
                max_non_contiguous += ele;
                int current = elements.size()-1; 
                if ( elements.size() == 0 || elements[current] < 0)
                    elements.push_back(ele);
                else
                    elements[current]+= ele;
            }
            else
                elements.push_back(ele);
            */
        }
        // int max_contiguous = numeric_limits<int>::min();
        if(max_element <=0) {
            max_non_contiguous = max_element;
            max_contiguous = max_element;
        }
        /*
        else {
            vector<int> cache(elements.size(), 0);
            for(int q = 0; q < elements.size(); q++) {
                for(int r =q; r< elements.size(); r++) {
                    if (r > q)
                        cache[r] = cache[r-1] + elements[r];
                    else
                        cache[r] = elements[r];
                    max_contigious = max(max_contiguous, cache[r]);
                    if (max_contigious == max_non_contiguous)
                        break;
                }
                if (max_contigious == max_non_contiguous)
                    break;
            }
        }
        */
        results[i].push_back(max_contiguous);
        results[i].push_back(max_non_contiguous);
    }
    
    for(int i=0; i < t; i++){
        cout << results[i][0] << " " << results[i][1] << endl;
    }
    
    return 0;
}
