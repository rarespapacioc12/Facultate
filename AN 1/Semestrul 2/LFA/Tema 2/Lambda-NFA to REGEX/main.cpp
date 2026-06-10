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

std::string simplify_regex(std::string s, const std::vector<std::string>& alphabet) {
    bool changed = true;
    while (changed) {
        changed = false;
        
        // simplific patternul (_|x)(_|x)* la x* ca sa fac regexul minimal
        for (const std::string& sym : alphabet) {
            if (sym.length() == 1) {
                char c = sym[0];
                std::string pattern = std::string("(_|") + c + ")(_|" + c + ")*";
                size_t pos = s.find(pattern);
                if (pos != std::string::npos) {
                    s = s.substr(0, pos) + std::string(1, c) + "*" + s.substr(pos + pattern.length());
                    changed = true;
                    break;
                }
            }
        }
    }
    
    return s;
}

std::string combine(const std::string& a, const std::string& b, const std::string& op, const std::vector<std::string>& alphabet) {
    // procesez stelarea
    if (op == "*") {
        if (a == "" || a == "_") return "_";
        if (a.length() == 1) return a + "*";
        return "(" + a + ")*";
    }
    // expresie goala
    if (a == "" || b == "") return a + b;
    // reuniune
    if (op == "|") {
        if (a == "_") return b == "_" ? "_" : (b.length() == 0 ? "_" : "_|" + b);
        if (b == "_") return a == "_" ? "_" : (a.length() == 0 ? "_" : a + "|_");
        if (a == b) return a;
        return a + "|" + b;
    }
    // concatenare
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
        
        return simplify_regex(a_res + b_res, alphabet);
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
    
    std::vector<std::string> alphabet;
    std::string sym = "";
    for (char c : line) {
        if (c == ' ') {
            if (sym != "") {
                alphabet.push_back(sym);
                sym = "";
            }
        } else {
            sym += c;
        }
    }
    if (sym != "") alphabet.push_back(sym);
    
    std::string init_state;
    fin >> init_state;

    int n;
    fin >> n;

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> g;

    // fac tranzitiile (unde am muchii cu mai multe valori bag direct |)
    for (int i = 0; i < n; ++i) {
        std::string u, symbol, v;
        fin>> u >> symbol >> v;
        if (g[u][v] == "") g[u][v] = symbol;
        else g[u][v] = combine(g[u][v], symbol, "|", alphabet);
    }

    // adaug starile ajutatoare
    std::string S = "START_NEW";
    std::string F = "FINAL_NEW";

    g[S][init_state] = "_";

    std::string f_state;
    while (fin>> f_state) {
        g[f_state][F] = "_";
    }

    // folosesc regula de abstractizare
    // pentru fiecare stare k din automatul original
    for (const std::string& k : states) {
        // trec prin toate starile posibile i de plecare
        for (auto it_i = g.begin(); it_i != g.end(); ++it_i) {
            std::string i = it_i->first;
            // daca i = k sau n-am cale de la i la k dau skip
            if (i == k || g[i].find(k) == g[i].end()) continue;

            // trec prin toate starile in care se poate ajunge din k
            for (auto it_j = g[k].begin(); it_j != g[k].end(); ++it_j) {
                std::string j = it_j->first;
                // for now, ignor starile care se intorc in k
                if (j == k) continue;

                // calculez o cale alternativa de la i la j care trece prin starea k
                // ik = expresia regulata de pe arcul de la i la k
                std::string ik = g[i][k];
                // kj = expresia regulata de pe arcul de la k la j
                std::string kj = g[k][j];
                // kk = expresia regulata a ciclului de la k la k (daca exista)
                // Daca nu exista ciclu, kk ramane gol (epsilon)
                std::string kk = g[k].count(k) ? combine(g[k][k], "", "*", alphabet) : "";

                // construiesc calea completa: i -> k -> k* -> k -> j
                // aceasta reprezentare include toate variantele de trecere prin k si eventual ciclurile sale
                std::string path = combine(ik, kk, ".", alphabet);
                path = combine(path, kj, ".", alphabet);

                // combin aceasta cale noua cu arcul direct daca exista deja arcul i -> j
                // daca exista deja un arc direct, fac reuniunea celor doua expresii
                // altfel, doar setez expresia din noul arc
                if (g[i].find(j) != g[i].end()) {
                    g[i][j] = combine(g[i][j], path, "|", alphabet);
                } else {
                    g[i][j] = path;
                }
            }
        }
        // dupa ce am procesat toate drumurile prin k, sterg starea k din graf
        // aceasta elimina si arcurile care ieseau din k si intrau in k
        g.erase(k);
        for (auto& par : g) par.second.erase(k);
    }

    // obtin expresia regulara finala si o simplific (explicat mai sus ce simplific)
    std::string result = g[S][F];
    result = simplify_regex(result, alphabet);
    fout << result << "\n";
}