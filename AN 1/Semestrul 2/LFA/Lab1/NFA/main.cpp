#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

std::ifstream fin("input_dfa.txt");
std::ifstream cuvin("cuvinte.txt");
std::ofstream fout("output.txt");

typedef std::pair<std::string, int> pci;
typedef std::pair<int, int> pii;

const std::string lambda = "!";

std::unordered_map<std::string, int> mp;
std::vector<std::string> inv_mp;
std::vector<std::vector<pci> > G;
std::unordered_set<std::string> alphabet;
std::unordered_set<int> final_states;
std::string initial_state;

int counter, function_pairs;

void read_states(){
    std::string s;
    std::getline(fin, s);

    int i = 0;
    while(i < (int)s.size()){
        std::string stare = "";
        while(i < (int)s.size() && s[i] != ' '){
            stare += s[i];
            ++i;
        }
        if(!stare.empty()){
            inv_mp.push_back(stare);
            mp[stare] = counter++;
        }
        while(i < (int)s.size() && s[i] == ' '){
            ++i;
        }
    }
}

void read_alphabet(){
    std::string s;
    std::getline(fin, s);

    int i = 0;
    while(i < (int)s.size()){
        std::string symbol = "";
        while(i < (int)s.size() && s[i] != ' '){
            symbol += s[i];
            ++i;
        }
        if(!symbol.empty()){
            alphabet.insert(symbol);
        }
        while(i < (int)s.size() && s[i] == ' '){
            ++i;
        }
    }
}

void read_function(){
    G.resize(counter);
    for(int i = 0; i < function_pairs; ++i){
        std::string state1, state2, symbol;
        fin >> state1 >> symbol >> state2;
        G[mp[state1]].push_back({symbol, mp[state2]});
    }
}

void read_final_states(){
    std::string final_state;
    while(fin >> final_state){
        final_states.insert(mp[final_state]);
    }
}

void read_input(){
    read_states();
    read_alphabet();
    fin >> initial_state;
    fin >> function_pairs;
    read_function();
    read_final_states();
}

bool dfs(int curr_node, const std::string& word, int poz, std::vector<std::string>& path, std::unordered_set<long long>& visited){
    long long code = 1LL * curr_node * 1000000 + poz;
    if(visited.find(code) != visited.end()){
        return false;
    }
    visited.insert(code);

    if(word == lambda && poz == 0){
        if(final_states.find(mp[initial_state]) == final_states.end()){
            path.push_back("Lambda: Cuvant respins!\n");
            return false;
        }
        path.push_back("Lambda: Cuvant admis!\n");
        return true;
    }

    if(poz == (int)word.length()){
        if(final_states.find(curr_node) == final_states.end()){
            return false;
        }
        path.push_back(word + ": Cuvant admis!\n");
        return true;
    }

    bool ok = false;

    for(auto [x, y] : G[curr_node]){
        if(x == lambda){
            ok = true;
            int old_size = path.size();
            path.push_back(word.substr(0, poz) + ": merg in " + inv_mp[y] + "\n");
            if(dfs(y, word, poz, path, visited)){
                return true;
            }
            path.resize(old_size);
        }
        else if(poz + (int)x.length() <= (int)word.length() && x == word.substr(poz, x.length())){
            ok = true;
            int old_size = path.size();
            path.push_back(word.substr(0, poz + x.length()) + ": merg in " + inv_mp[y] + "\n");
            if(dfs(y, word, poz + x.length(), path, visited)){
                return true;
            }
            path.resize(old_size);
        }
    }

    if(ok == false){
        path.push_back(word.substr(0, poz) + ": Nu exista tranzitii!\n");
    }

    return false;
}

int main(){
    read_input();
    std::string word;
    while(std::getline(cuvin, word)){
        if(word.empty()){
            continue;
        }

        std::vector<std::string> path;
        std::unordered_set<long long> visited;

        bool is_found = dfs(mp[initial_state], word, 0, path, visited);

        for(const auto& s : path){
            fout << s;
        }

        if(!is_found){
            if(word == lambda){
                fout << "Lambda: Cuvant respins!\n";
            }
            else{
                fout << "Cuvant respins!\n";
            }
        }
    }
}