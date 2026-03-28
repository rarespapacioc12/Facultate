#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

std::ifstream fin("input_lambda_nfa.txt");
std::ifstream cuvin("cuvinte.txt");
std::ofstream fout("output.txt");

typedef std::pair<std::string, int> pci;
const std::string lambda = "_";

std::unordered_map<std::string, int> mp;
std::vector<std::string> inv_mp;
std::vector<std::vector<pci> > G;
std::unordered_set<std::string> alphabet;
std::unordered_set<int> final_states;
std::vector<std::vector<int> > lambda_completion;
std::string initial_state;

int counter, function_pairs;

std::vector<int> reunion(const std::vector<int>& S1, const std::vector<int>& S2){
    std::vector<int> sol(S1.size() + S2.size());
    auto it = std::set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), sol.begin());
    sol.resize(it - sol.begin());
    return sol;
}

std::string show_states(const std::vector<int>& states){
    std::string s = "{";
    for(int i = 0; i < (int)states.size(); ++i){
        s += inv_mp[states[i]];
        if(i + 1 < (int)states.size()){
            s += ", ";
        }
    }
    s += "}";
    return s;
}

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

void lambda_closure(int start, std::vector<bool>& viz){
    for(auto [x, y] : G[start]){
        if(x == lambda && !viz[y]){
            viz[y] = true;
            lambda_closure(y, viz);
        }
    }
}

void compute_lambda_transitions(){
    lambda_completion.resize(counter);
    for(int i = 0; i < counter; ++i){
        std::vector<bool> viz(counter, false);
        viz[i] = true;
        lambda_closure(i, viz);
        for(int j = 0; j < counter; ++j){
            if(viz[j]){
                lambda_completion[i].push_back(j);
            }
        }
    }
}

void check_word(const std::string& word, int poz, const std::vector<int>& states, std::vector<std::string>& path, bool& is_found){
    std::vector<int> curr_states = {};
    for(int x : states){
        curr_states = reunion(curr_states, lambda_completion[x]);
    }

    if(word == lambda){
        path.push_back("Lambda: " + show_states(curr_states) + "\n");
        for(int x : curr_states){
            if(final_states.find(x) != final_states.end()){
                path.push_back("Lambda: Cuvant admis!\n");
                is_found = true;
                return;
            }
        }
        path.push_back("Lambda: Cuvant respins!\n");
        return;
    }

    if(poz == 0){
        path.push_back(": " + show_states(curr_states) + "\n");
    }

    if(poz == (int)word.length()){
        for(int x : curr_states){
            if(final_states.find(x) != final_states.end()){
                path.push_back(word + ": Cuvant admis!\n");
                is_found = true;
                return;
            }
        }
        path.push_back(word + ": Cuvant respins!\n");
        return;
    }

    std::vector<std::string> possible_symbols = {};
    for(int state : curr_states){
        for(auto [x, y] : G[state]){
            if(x != lambda && poz + (int)x.length() <= (int)word.length() && x == word.substr(poz, x.length())){
                possible_symbols.push_back(x);
            }
        }
    }

    sort(possible_symbols.begin(), possible_symbols.end());
    possible_symbols.erase(unique(possible_symbols.begin(), possible_symbols.end()), possible_symbols.end());

    if(possible_symbols.empty()){
        path.push_back(word.substr(0, poz) + ": Nu exista tranzitii!\n");
        path.push_back(word + ": Cuvant respins!\n");
        return;
    }

    for(const auto& symbol : possible_symbols){
        std::vector<int> next_states = {};
        for(int state : curr_states){
            for(auto [x, y] : G[state]){
                if(x == symbol){
                    next_states = reunion(next_states, std::vector<int>{y});
                }
            }
        }

        std::vector<int> shown_states = {};
        for(int x : next_states){
            shown_states = reunion(shown_states, lambda_completion[x]);
        }

        path.push_back(word.substr(0, poz + symbol.length()) + ": " + show_states(shown_states) + "\n");
        check_word(word, poz + symbol.length(), next_states, path, is_found);
        return;
    }
}

int main(){
    read_input();
    compute_lambda_transitions();
    std::string word;
    while(std::getline(cuvin, word)){
        if(word.empty()){
            continue;
        }
        cuvin.clear();
        std::vector<int> states = {mp[initial_state]};
        std::vector<std::string> path;
        bool is_found = false;

        check_word(word, 0, states, path, is_found);

        for(const auto& s : path){
            fout << s;
        }
    }
}