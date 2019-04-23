#include <iostream>
#include <stack>
#include <string>
using namespace std;
struct Bracket {
    Bracket(int type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    //while(true){
    getline(std::cin, text);

    std::stack <Bracket> myStack;
    int position;
    int mismatchPosition = -1;
    for (position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            myStack.push(Bracket(next,position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(myStack.empty()){
              //Case 1a: unmatched closing bracket; 
              //no avail opening bracket to match closing bracket
              mismatchPosition = position +1;
              break;
            }
            Bracket b = myStack.top();
            char top = b.type;
            
            if(( top == '(' && next == ')') || ( top == '[' && next == ']') || ( top == '{' && next == '}'))
            {
              myStack.pop();
            }
            else{ 
              //Case 1b: unmatched closing bracket
              mismatchPosition = position +1;
              break;
            }
        }
    }

    if(mismatchPosition != -1)
      cout << mismatchPosition; //pos of laste unmatched closing bracket
    else if(!myStack.empty())
    {
      //Case 2: unmatched opening bracket
      Bracket b = myStack.top();
      cout << b.position; //pos of first unmatched opening bracket
    }
    else 
      cout <<"Success";
      
    cout << endl;
    //}
    return 0;
}
