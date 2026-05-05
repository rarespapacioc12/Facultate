#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

bool needs_parens(const std::string& s) {
    int depth = 0;
    for (char c : s) {
        if (c == '(') depth++;
        else if (c == ')') depth--;
        else if (c == '|' && depth == 0) return true;
    }
    return false;
}

std::string combine(const std::string& a, const std::string& b, const std::string& op) {
    if (op == "*") {
        if (a == "" || a == "_") return "_";
        if (a.length() == 1) return a + "*";
        return "(" + a + ")*";
    }
    if (a == "" || b == "") return a + b;
    if (op == "|") {
        if (a == "_") return b == "_" ? "_" : (b.length() == 0 ? "_" : "_|" + b);
        if (b == "_") return a == "_" ? "_" : (a.length() == 0 ? "_" : a + "|_");
        if (a == b) return a;
        return a + "|" + b;
    }
    if (op == ".") {
        std::string a_val = a == "_" ? "" : a;
        std::string b_val = b == "_" ? "" : b;
        if (a_val == "" && b_val == "") return "_";
        if (a_val == "") return b_val;
        if (b_val == "") return a_val;
        
        bool a_needs = needs_parens(a_val);
        bool b_needs = needs_parens(b_val);
        
        std::string a_res = a_needs ? "(" + a_val + ")" : a_val;
        std::string b_res = b_needs ? "(" + b_val + ")" : b_val;
        
        return a_res + b_res;
    }
    return "";
}

int main() {

    std::string line;
    std::getline(fin, line);
    
    std::vector<std::string> states;
    std::string state = "";
    for (char c : line) {
        if (c == ' ') {
            if (state != "") {
                states.push_back(state);
                state = "";
            }
        } else {
            state += c;
        }
    }
    if (state != "") states.push_back(state);

    std::getline(fin, line);
    
    std::string init_state;
    fin >> init_state;

    int n;
    fin >> n;

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> g;

    for (int i = 0; i < n; ++i) {
        std::string u, symbol, v;
        fin>> u >> symbol >> v;
        if (g[u][v] == "") g[u][v] = symbol;
        else g[u][v] = combine(g[u][v], symbol, "|");
    }

    std::string S = "START_NEW";
    std::string F = "FINAL_NEW";

    g[S][init_state] = "_";

    std::string f_state;
    while (fin>> f_state) {
        g[f_state][F] = "_";
    }

    for (const std::string& k : states) {
        for (auto it_i = g.begin(); it_i != g.end(); ++it_i) {
            std::string i = it_i->first;
            if (i == k || g[i].find(k) == g[i].end()) continue;

            for (auto it_j = g[k].begin(); it_j != g[k].end(); ++it_j) {
                std::string j = it_j->first;
                if (j == k) continue;

                std::string ik = g[i][k];
                std::string kj = g[k][j];
                std::string kk = g[k].count(k) ? combine(g[k][k], "", "*") : "";

                std::string path = combine(ik, kk, ".");
                path = combine(path, kj, ".");

                if (g[i].find(j) != g[i].end()) {
                    g[i][j] = combine(g[i][j], path, "|");
                } else {
                    g[i][j] = path;
                }
            }
        }
        g.erase(k);
        for (auto& par : g) par.second.erase(k);
    }

    fout << g[S][F] << "\n";
}