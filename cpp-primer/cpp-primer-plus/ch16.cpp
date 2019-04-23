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

int is_valid_char(int c){
  return ispunct(c) || isspace(c);
}
bool palindrome(string str){
  //str to lower case  via transform, erase
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  str.erase(remove_if(str.begin(), str.end(), is_valid_char), str.end());

  string::iterator i = str.begin();
  string::reverse_iterator j = str.rbegin();
  int mid = str.size()/2;
  for(int k=0; k<mid; i++, j++, k++){
    if(*i != *j) return false;
  }
  return true;
}

template<class T>
int reduce (T arr[], int n){
  list<T> items(n);
  copy(arr, arr+n, items.begin());
  items.sort();
  items.unique();
  return items.size();
}

vector<int> Lotto(int max, int num){
  vector<int> items;
  for(int i=1;i<= max;++i){
    items.push_back(i);
  }
  random_shuffle(items.begin(), items.end());
  vector<int>::const_iterator first = items.begin();

  vector<int> result(items.begin(), items.begin()+num);
  return result;
}

void exercise_1to2(){
  string input;
  while( getline(cin, input)){
    cout << palindrome(input) << endl;
  }
}

void exercise_3(){
  ifstream fin;
  fin.open("wordlist.txt");
  if(fin.is_open() == false)
  {
    cerr << "Can't open file. Bye.\n";
    exit(EXIT_FAILURE);
  }
  vector<string> wordlist;
  string input;
  while(fin)
  {
    getline(fin, input);
    wordlist.push_back(input);
  }
  fin.close();
  int num = wordlist.size();

  
  srand(time(0));
  char play;
  cout << "Will you play a word game? <y/n>";
  cin >> play;
  play = tolower(play);
  while(play == 'y')
  {
    string target = wordlist[rand()% num];
    int length = target.length();
    string attempt(length, '-');
    string badchars;
    int guesses = 6;
    cout << "Guess my secret word. It has " << length << " letters, and you guess\none letter at a time. You get " <<
    guesses << " wrong guesses.\n";
    cout << "Your word: " << attempt << endl;
    while(guesses > 0 && attempt != target)
    {
        char letter;
        cout << "Guess a letter: ";
        cin >> letter;
        if(badchars.find(letter) != string::npos || attempt.find(letter)!= string::npos){
            cout << "You already guessed that. Try again.\n";
            continue;
        }
        
        int loc = target.find(letter);
        if(loc == string::npos){
            cout << "Oh, bad guess!\n";
            --guesses;
            badchars += letter;
        }
        else
        {
            cout << "Good guess!\n";
            attempt[loc] = letter;
            //check if letter appears again
            loc = target.find(letter, loc+1);
            while(loc!= string::npos){
                attempt[loc]= letter;
                loc = target.find(letter, loc+1);   
            }
        }
        cout << "Your word: " << attempt << endl;
        if(attempt != target){
            if(badchars.length() >0)
              cout << "Bad choices: " << badchars << endl;
            cout << guesses << " bad guesses left\n";
        }
    }
    if(guesses > 0)
        cout << "That's right!\n";
    else
        cout << "Sorry, the word is " << target << ".\n";
        
        cout << "Will you play another? <y/n> ";
        cin >> play;
        play = tolower(play);
  }
  cout << "Bye.\n";
}

void exercise_4to5(){
  ifstream fin;

  fin.open("reduce_testcase01.txt");
  if(fin.is_open() == false)
  {
    cerr << "Can't open file. Bye.\n";
    exit(EXIT_FAILURE);
  }
  int n, i=0;
  fin >> n;
  long *input= new long[n];
  while(fin){
   
    fin>> input[i++];
  }
  fin.close();
  cout << reduce(input, n) << endl;
  delete[] input;
  
  
  fin.open("reduce_testcase02.txt");
  if(fin.is_open() == false)
  {
    cerr << "Can't open file. Bye.\n";
    exit(EXIT_FAILURE);
  }
  
  i=0;
  fin >> n;
  string *str_input= new string[n];
  while(fin){
   
    fin>> str_input[i++];
  }
  fin.close();
  cout << reduce(str_input, n);
  delete[] str_input;
}

void exercise_7(){
  vector<int> winners = Lotto(51, 6);
  for(auto i: winners){
    cout << i << " ";
  }
  cout << endl;
}

void exercise_8(){
  cout << "Enter names for list #1, enter 'exit' to finish\n";
  list<string> list1, list2;
  string input;
  while(input != "exit"){
    getline(cin, input);
    list1.push_back(input);
  }
  cout << "Enter names for list #2, enter 'exit' to finish\n";
  input = "";
  while(input != "exit"){
    getline(cin, input);
    list2.push_back(input);
  }
  
  list1.sort(); list2.sort();
  
  cout << "Displaying sorted names for list#1.\n";
  for(auto i: list1)
    cout << i << endl;
  
    
  cout << "Displaying sorted names for list#2.\n";
  for(auto i: list2)
    cout << i << endl;
    
  list1.merge(list2);
  list1.unique();
  cout << "Displaying sorted names after merge.\n";
  for(auto i: list1)
    cout << i << endl;
}
int main()
{
  //exercise_1to2();
  //exercise_3();
  //exercise_4to5();
  //exercise_7();
  exercise_8();
  return 0;
}
