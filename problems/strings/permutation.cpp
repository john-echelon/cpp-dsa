#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

bool isPermutation(string &a, string &b){
    if(a.length() != b.length())
        return false;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

bool isPermutation( char * a, char * b){
    int aLen = strlen(a);
    int bLen = strlen(b);
    if(aLen!= bLen)
        return false;

    int count[256] = {0};
    //for c-style strings
    for(int i =0; i< aLen; ++i){
        int val = (int) a[i];
        count[val]++;
    }
    for(int i = 0; i< bLen; ++i){
        int val = (int) b[i];
        if(--count[val] <0){
            return false;
        }
    }
    return true;
}
int main(){
    string a, b;
    while(true){
        getline(cin, a);
        getline(cin, b);
        cout << isPermutation(a, b) << endl;
        //c-style version
        char * ac = new char[a.length()+1];
        char * bc = new char[b.length()+1];
        strcpy(ac, a.c_str());
        strcpy(bc, b.c_str());
        cout << isPermutation(ac, bc) << endl;
        delete [] ac;
        delete [] bc;
    }
}