// sigma = {"a", "1", "ceva", "patrat"}
// sigma = {"mo", "ca", "nu"}
// a.a=aa
// L = {a^(2i)b^(3j) | i >= 0 si j >= 0}

// Tema 1
// DFA, NFA, lambda_NFA
// Bonus: algoritmul de minimizare/transf din lambda_NFA in DFA
// Sa primeasca ca input din fisier un graf de DFA si pe fiecare linie din fisier sa prezinti cate un element
// Input: sintaxa custom
// Ex:
// input.dfa
// q0, ..., qn
// a b
// q0
// 7
// q0 a q3
// ...
// starti finale
// cuvinte.txt
// abba
// acca
// abba

// output.dfa
// a: q3
// ab: q7
// abb: Nu exista tranzitii
// Respins

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

bool parse_word(const std::string& word, std::vector<std::string>& path){
    int curr_node = mp[initial_state];
    int poz = 0;

    while(poz < (int)word.length()){
        bool found = false;

        for(auto [x, y] : G[curr_node]){
            if(poz + (int)x.length() <= (int)word.length() && x == word.substr(poz, x.length())){
                path.push_back(word.substr(0, poz + x.length()) + ": merg in " + inv_mp[y] + "\n");
                curr_node = y;
                poz += x.length();
                found = true;
                break;
            }
        }

        if(found == false){
            path.push_back(word.substr(0, poz) + ": Nu exista tranzitii!\n");
            return false;
        }
    }

    if(final_states.find(curr_node) != final_states.end()){
        path.push_back(word + ": Cuvant admis!\n");
        return true;
    }

    path.push_back(word + ": Cuvant respins!\n");
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
        parse_word(word, path);

        for(const auto& s : path){
            fout << s;
        }
    }
}