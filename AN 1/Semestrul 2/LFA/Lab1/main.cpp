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

const std::string lambda = "!";

std::unordered_map<std::string, int> mp; // mapare pentru int ca sa fac graful mai usor as in starile sa fie puse de la 0 la nr_stari - 1
std::vector<std::string> inv_mp;
std::vector<std::vector<pci> > G; // graful
std::unordered_set<std::string> alphabet;
std::unordered_set<int> final_states;
std::string initial_state;

int counter, function_pairs;

void read_states(){
    std::string s;
    std::getline(fin, s);

    int i = 0;
    while(s[i]){
        std::string stare = "";
        while(s[i] and s[i] != ' '){
            stare += s[i];
            ++i;
        }
        inv_mp.push_back(stare);
        mp[stare] = counter++;
        if(!s[i])
            break;
        ++i;
    }
    fin.clear();
}

void read_alphabet(){
    std::string s;
    std::getline(fin, s);

    int i = 0;
    while(s[i]){
        std::string symbol = "";
        while(s[i] and s[i] != ' '){
            symbol += s[i];
            ++i;
        }
        alphabet.insert(symbol);
        if(!s[i])
            break;
        ++i;
    }
    fin.clear();
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

void dfs(int curr_node, const std::string& word, int poz){
    if(word == lambda){
        if(final_states.find(mp[initial_state]) == final_states.end()){
            fout << "Lambda: Cuvant respins!\n";
        }
        else{
            fout << "Lambda: Cuvant admis!\n";
        }
        return;
    }
    if(poz == (int)word.length()){
        if(final_states.find(curr_node) == final_states.end()){
            fout << "Cuvant respins!\n";
        }
        else{
            fout << "Cuvant admis!\n";
        }
        return;
    }
    bool ok = false;
    for(auto [x, y] : G[curr_node]){
        if(x.length() + poz <= word.length() && x == word.substr(poz, x.length())){
            ok = true;
            fout << word.substr(0, poz + x.length()) + ": merg in " + inv_mp[y] + "\n";
            dfs(y, word, poz + x.length());
        }
    }
    if(ok == false){
        fout << word + ": Nu exista!\n Cuvant respins!\n";
        return;
    }
}

int main(){
    read_input();
    std::string word;
    while(std::getline(cuvin, word)){
        cuvin.clear();
        dfs(mp[initial_state], word, 0);
    }
}