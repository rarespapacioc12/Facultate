#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const std::string lambda = "_";

// neterminalele, terminalele si regulile gramaticii
std::set<std::string> V;                                  // neterminale
std::set<std::string> Sigma;                              // terminale
std::string start;                                        // simbolul de start
std::map<std::string, std::vector<std::vector<std::string> > > R; // reguli (lambda = vector gol)

std::vector<std::string> splitSpaces(const std::string& line) {
    std::vector<std::string> res;
    std::string cur;
    for (char c : line) {
        if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
            if (!cur.empty()) { res.push_back(cur); cur.clear(); }
        } else cur += c;
    }
    if (!cur.empty()) res.push_back(cur);
    return res;
}

// imparte o parte dreapta in simboluri reale.
// In input simbolurile pot fi lipite (ex: "XRX", "aTb"), nu doar separate prin spatii,
// asa ca fac potrivire greedy pe cel mai lung simbol cunoscut din V sau Sigma.
std::vector<std::string> tokenizeSymbols(const std::string& s) {
    std::vector<std::string> res;
    size_t i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') { ++i; continue; }
        std::string best;
        for (const std::string& sym : V)
            if (sym.size() > best.size() && s.compare(i, sym.size(), sym) == 0) best = sym;
        for (const std::string& sym : Sigma)
            if (sym.size() > best.size() && s.compare(i, sym.size(), sym) == 0) best = sym;
        if (best.empty()) best = std::string(1, c); // simbol necunoscut (ex: lambda '_')
        res.push_back(best);
        i += best.size();
    }
    return res;
}

std::string readNextLine(std::ifstream& in) {
    std::string line;
    while (std::getline(in, line)) {
        for (char c : line)
            if (c != ' ' && c != '\r' && c != '\n' && c != '\t') return line;
    }
    return "";
}

bool isNonterminal(const std::string& x) { return V.find(x) != V.end(); }

// parsez o linie de forma  A -> alfa | beta | ...
// fiecare alternativa e o secventa de simboluri separate prin spatiu, iar "_" inseamna lambda
void parseRule(const std::string& line) {
    size_t arrow = line.find("->");
    if (arrow == std::string::npos) return;

    std::string lhs = splitSpaces(line.substr(0, arrow))[0];
    std::string rhs = line.substr(arrow + 2);

    std::string alt;
    std::vector<std::string> alts;
    for (char c : rhs) {
        if (c == '|') { alts.push_back(alt); alt.clear(); }
        else alt += c;
    }
    alts.push_back(alt);

    for (const std::string& a : alts) {
        std::vector<std::string> symbols = tokenizeSymbols(a);
        // o productie lambda o tin ca vector gol
        if (symbols.size() == 1 && symbols[0] == lambda) symbols.clear();
        R[lhs].push_back(symbols);
    }
}

void readGrammar() {
    std::vector<std::string> nonterm = splitSpaces(readNextLine(fin));
    for (const std::string& x : nonterm) V.insert(x);

    std::vector<std::string> term = splitSpaces(readNextLine(fin));
    for (const std::string& x : term) Sigma.insert(x);

    start = splitSpaces(readNextLine(fin))[0];

    int ruleCount = std::stoi(splitSpaces(readNextLine(fin))[0]);
    for (int i = 0; i < ruleCount; ++i) parseRule(readNextLine(fin));
}

// pentru taierea ramurilor calculez minimul de caractere terminale pe care le poate
// genera fiecare neterminal (lungimea celei mai scurte derivari complete)
const long long INF = 1e18;
std::map<std::string, long long> minChars;

void computeMinChars() {
    for (const std::string& A : V) minChars[A] = INF;

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto& rule : R) {
            const std::string& A = rule.first;
            for (const auto& prod : rule.second) {
                long long sum = 0;
                bool ok = true;
                for (const std::string& sym : prod) {
                    if (isNonterminal(sym)) {
                        if (minChars[sym] == INF) { ok = false; break; }
                        sum += minChars[sym];
                    } else {
                        sum += (long long)sym.length();
                    }
                }
                if (ok && sum < minChars[A]) { minChars[A] = sum; changed = true; }
            }
        }
    }
}

// concatenez simbolurile (toate terminale) ca sa obtin cuvantul efectiv
std::string joinWord(const std::vector<std::string>& form) {
    std::string w;
    for (const std::string& sym : form) w += sym;
    return w;
}

int main() {
    readGrammar();
    computeMinChars();

    // lungimea cuvintelor cerute se afla pe ultima linie din input, dupa reguli
    std::vector<std::string> kLine = splitSpaces(readNextLine(fin));
    if (kLine.empty()) {
        fout << "Eroare: lipseste lungimea k pe ultima linie din input.txt\n";
        return 1;
    }
    int k = std::stoi(kLine[0]);

    // explorez arborele de derivare pornind de la simbolul de start
    std::queue<std::vector<std::string> > q;
    std::set<std::vector<std::string> > visited;
    std::set<std::string> results;

    std::vector<std::string> startForm = {start};
    q.push(startForm);
    visited.insert(startForm);

    // limita de siguranta ca sa nu intru in derivari infinite cu lambda-productii
    int cap = 2 * k + 50;

    while (!q.empty()) {
        std::vector<std::string> form = q.front();
        q.pop();

        // gasesc primul neterminal din sir
        int idx = -1;
        for (int i = 0; i < (int)form.size(); ++i) {
            if (isNonterminal(form[i])) { idx = i; break; }
        }

        // sir doar de terminale -> verific lungimea
        if (idx == -1) {
            if ((int)joinWord(form).length() == k) results.insert(joinWord(form));
            continue;
        }

        // taierea ramurilor: estimez lungimea minima a cuvantului final
        long long lowerBound = 0;
        bool dead = false;
        for (const std::string& sym : form) {
            if (isNonterminal(sym)) {
                if (minChars[sym] == INF) { dead = true; break; }
                lowerBound += minChars[sym];
            } else lowerBound += (long long)sym.length();
        }
        if (dead || lowerBound > k) continue;
        if ((int)form.size() > cap) continue;

        // expandez primul neterminal cu fiecare din productiile sale
        const std::string& A = form[idx];
        for (const auto& prod : R[A]) {
            std::vector<std::string> next;
            for (int i = 0; i < idx; ++i) next.push_back(form[i]);
            for (const std::string& sym : prod) next.push_back(sym);
            for (int i = idx + 1; i < (int)form.size(); ++i) next.push_back(form[i]);

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }

    fout << "Cuvinte de lungime " << k << " din L(G):\n";
    if (results.empty()) {
        fout << "(niciun cuvant)\n";
    } else {
        for (const std::string& w : results) fout << (w.empty() ? lambda : w) << "\n";
    }
}
