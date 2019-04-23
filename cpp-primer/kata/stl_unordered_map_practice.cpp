#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(){
     // Create an unordered_map of three strings (that map to strings)
    std::unordered_map<std::string, std::string> u = {
        {"RED","#FF0000"},
        {"GREEN","#00FF00"},
        {"BLUE","#0000FF"}
    };
 
    // Iterate and print keys and values of unordered_map
    for( const auto& n : u ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    
    std::unordered_map<int,char> map = {{1,'a'},{1,'b'},{1,'d'},{2,'b'}};
    auto range = map.equal_range(2);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
    for( const auto& n : map ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    int key = 1; 
    cout << "Count of Key:[" << key << "]: " << map.count(key) << "\n";
    map[key] = 'e';
    for( const auto& n : map) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    return 0;
}