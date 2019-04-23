#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    unsigned long long number = -1;
};
int m=100000;
vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

int getAddress(unsigned long long x){
    unsigned long long a= 1, b = 2, p=10000019;
    int h = ((a*x + b) % p)%m;
    return  h;
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<vector<Query>> contacts(m);
    for (size_t i = 0; i < queries.size(); ++i){
        int val = getAddress(queries[i].number);
        
        if (queries[i].type == "add") {
            bool found = false;
            for(int j =0; j< contacts[val].size(); ++j){
                if(contacts[val][j].number == queries[i].number)
                {
                    contacts[val][j].name = queries[i].name;
                    found = true;
                    break;
                }
            }
            if(!found){
                Query q;
                q.number = queries[i].number;
                q.name = queries[i].name;
                contacts[val].push_back(q);
            }
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts[val].size(); ++j){
                if (contacts[val][j].number == queries[i].number) {
                    contacts[val].erase(contacts[val].begin() + j);
                    break;
                }
            }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts[val].size(); ++j){
                if (contacts[val][j].number == queries[i].number) {
                    response = contacts[val][j].name;
                    break;
                }
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
