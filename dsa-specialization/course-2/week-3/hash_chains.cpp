#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<vector<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems = vector<vector<string>>(bucket_count);
    }

    bool Find(const string &s){
         vector<string> & list = elems[hash_func(s)];
         vector<string>::iterator it = std::find(list.begin(), list.end(), s);
         return it != list.end();
    }
    
    void Add(const string & s){
        vector<string> & list = elems[hash_func(s)];
        vector<string>::iterator it = std::find(list.begin(), list.end(), s);
        if(it == list.end()){
            list.push_back(s);
        }
    }
    
    void Remove(const string & s){
        vector<string> & list = elems[hash_func(s)];
        vector<string>::iterator it = std::find(list.begin(), list.end(), s);
        if(it != list.end()){
            list.erase(it);
        }
    }     
    
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            int hash = query.ind;
            if(!elems[hash].empty()){
                for (int i = static_cast<int>(elems[hash].size()) - 1; i >= 0; --i)
                    std::cout << elems[hash][i] << " ";
            }
            std::cout << "\n";
        } else {
            if (query.type == "find")
                writeSearchResult(Find(query.s));
            else if (query.type == "add") {
                Add(query.s);
            } else if (query.type == "del") {
                Remove(query.s);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
