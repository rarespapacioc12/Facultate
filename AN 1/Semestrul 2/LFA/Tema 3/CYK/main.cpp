#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

std::ifstream fin("input.txt");
std::ifstream wordIn("word.txt");
std::ofstream fout("output.txt");

const std::string lambda = "_";

// gramatica trebuie sa fie in Forma Normala Chomsky: reguli A -> a sau A -> B C
std::set<std::string> V;
std::set<std::string> Sigma;
std::string start;

// termRules[a]  = neterminalele A cu A -> a
// pairRules[BC] = neterminalele A cu A -> B C
std::map<std::string, std::set<std::string> > termRules;
std::map<std::pair<std::string, std::string>, std::set<std::string> > pairRules;
bool startNullable = false; // exista S -> lambda ?

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
// In input simbolurile pot fi lipite (ex: "XC", "X_aC1"), nu doar separate prin spatii,
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
        if (symbols.size() == 1 && symbols[0] == lambda) symbols.clear();

        if (symbols.empty()) {
            if (lhs == start) startNullable = true;            // S -> lambda
        } else if (symbols.size() == 1 && !isNonterminal(symbols[0])) {
            termRules[symbols[0]].insert(lhs);                  // A -> a
        } else if (symbols.size() == 2) {
            pairRules[{symbols[0], symbols[1]}].insert(lhs);    // A -> B C
        }
    }
}

void readGrammar() {
    for (const std::string& x : splitSpaces(readNextLine(fin))) V.insert(x);
    for (const std::string& x : splitSpaces(readNextLine(fin))) Sigma.insert(x);
    start = splitSpaces(readNextLine(fin))[0];
    int ruleCount = std::stoi(splitSpaces(readNextLine(fin))[0]);
    for (int i = 0; i < ruleCount; ++i) parseRule(readNextLine(fin));
}

// CYK: tabela triunghiulara T[i][len] = multimea neterminalelor care genereaza
// subsirul care incepe la pozitia i si are lungimea len
bool cyk(const std::string& word) {
    int n = (int)word.length();
    if (n == 0) return startNullable;

    // T[i][len], cu i de la 0 la n-1 si len de la 1 la n
    std::vector<std::vector<std::set<std::string> > > T(
        n, std::vector<std::set<std::string> >(n + 1));

    // pasul de baza (len = 1): T[i][1] = { A | A -> word[i] }
    for (int i = 0; i < n; ++i) {
        std::string a(1, word[i]);
        if (termRules.count(a))
            for (const std::string& A : termRules[a]) T[i][1].insert(A);
    }

    // pasul recursiv: pentru fiecare lungime len si fiecare pozitie de start i,
    // impart subsirul in doua parti de lungimi k si len - k
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            for (int k = 1; k < len; ++k) {
                for (const std::string& B : T[i][k]) {
                    for (const std::string& C : T[i + k][len - k]) {
                        auto it = pairRules.find({B, C});
                        if (it != pairRules.end())
                            for (const std::string& A : it->second) T[i][len].insert(A);
                    }
                }
            }
        }
    }

    // cuvantul e acceptat daca simbolul de start genereaza tot sirul
    return T[0][n].count(start) > 0;
}

int main() {
    readGrammar();

    std::string line;
    while (std::getline(wordIn, line)) {
        std::vector<std::string> parts = splitSpaces(line);
        if (parts.empty()) continue;

        std::string word = parts[0];
        if (word == lambda) word = "";

        bool accepted = cyk(word);
        fout << "Cuvant: " << (word.empty() ? lambda : word)
             << " -> " << (accepted ? "DA" : "NU") << "\n";
    }
}
