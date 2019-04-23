#include <iostream>
#include <string>
#include "stack.h"
using std::cout;
using std::cin;
using std::endl;
using namespace std;


int main()
{
    
    Stack<std::string> st;
    std::string po;
    while(!st.isFull() && po != "quit"){
        cin >> po;
        st.push(po);
    } 
    cout << endl;
    while(!st.isEmpty()){
        st.pop(po);
        cout << st.size() << ": "<< po << endl;
    } 

    return 0;
}