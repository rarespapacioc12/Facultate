#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

std::ifstream fin("input_nfa.txt");
std::ifstream cuvin("cuvinte.txt");
std::ofstream fout("output.txt");

typedef std::pair<std::string, int> pci;

std::unordered_map<std::string, int> mp;
std::vector<std::string> inv_mp;
std::vector<std::vector<pci> > G;
std::unordered_set<std::string> alphabet;
std::unordered_set<int> final_states;
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

void check_word(const std::string& word){
    std::vector<int> curr_states = {mp[initial_state]};
    sort(curr_states.begin(), curr_states.end());
    curr_states.erase(unique(curr_states.begin(), curr_states.end()), curr_states.end());

    int poz = 0;

    while(poz < (int)word.length()){
        std::vector<std::string> possible_symbols = {};

        for(int state : curr_states){
            for(auto [x, y] : G[state]){
                if(poz + (int)x.length() <= (int)word.length() && x == word.substr(poz, x.length())){
                    possible_symbols.push_back(x);
                }
            }
        }

        sort(possible_symbols.begin(), possible_symbols.end());
        possible_symbols.erase(unique(possible_symbols.begin(), possible_symbols.end()), possible_symbols.end());

        if(possible_symbols.empty()){
            fout << word.substr(0, poz) << ": Nu exista tranzitii!\n";
            fout << word << ": Cuvant respins!\n";
            return;
        }

        std::string chosen_symbol = "";
        for(const auto& symbol : possible_symbols){
            if(poz + (int)symbol.length() <= (int)word.length() && symbol == word.substr(poz, symbol.length())){
                chosen_symbol = symbol;
                break;
            }
        }

        std::vector<int> next_states = {};
        for(int state : curr_states){
            for(auto [x, y] : G[state]){
                if(x == chosen_symbol){
                    next_states = reunion(next_states, std::vector<int>{y});
                }
            }
        }

        fout << word.substr(0, poz + chosen_symbol.length()) << ": " << show_states(next_states) << "\n";

        curr_states = next_states;
        poz += chosen_symbol.length();
    }

    for(int state : curr_states){
        if(final_states.find(state) != final_states.end()){
            fout << word << ": Cuvant admis!\n";
            return;
        }
    }

    fout << word << ": Cuvant respins!\n";
}

int main(){
    read_input();
    std::string word;
    while(std::getline(cuvin, word)){
        if(word.empty()){
            if(final_states.find(mp[initial_state]) != final_states.end()){
                fout << "Lambda: {" << initial_state << "}\n";
                fout << "Lambda: Cuvant admis!\n";
            }
            else{
                fout << "Lambda: {" << initial_state << "}\n";
                fout << "Lambda: Cuvant respins!\n";
            }
            continue;
        }

        check_word(word);
    }
}