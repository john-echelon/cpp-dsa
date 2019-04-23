#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

 long long hash_func(const string& s, long long multiplier, long long prime) {
     long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}

vector< long long> PrecomputeHashes(const Data& data,   long long multiplier,  long long prime){
    vector< long long> hashes(data.text.size()- data.pattern.size()+1);
    string s = data.text.substr(data.text.size()-data.pattern.size(), data.pattern.size());
     long long y =1;
    hashes[data.text.size()-data.pattern.size()] = hash_func(s, multiplier, prime);
    
    for(int i = 1; i<=data.pattern.size();++i)
        y = (y *multiplier) % prime;
    
    for(int i = data.text.size()-data.pattern.size()-1; i>=0; --i){
        long long a = multiplier * hashes[i+1] + data.text[i];
        long long b =  y * data.text[i+ data.pattern.size()];
        hashes[i] = ((a - b) % prime + prime) % prime;
        //hashes[i] = (multiplier * hashes[i+1] + data.text[i] - y * data.text[i+ data.pattern.size()]) % prime;
    }
    
    return hashes;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    long long multiplier= 263, prime= 1000000007;
    std::vector<int> ans;
    long long pHash = hash_func(s, multiplier, prime);
    vector<long long> h = PrecomputeHashes(input, multiplier, prime);
    
    for(int i =0; i<= t.size()-s.size(); ++i)
    {
        if(pHash != h[i])
            continue;
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
