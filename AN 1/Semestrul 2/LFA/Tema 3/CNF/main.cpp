#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const std::string lambda = "_";

// gramatica: foloec set-uri ca sa elimin automat duplicatele (lambda = vector gol)
std::set<std::string> V;       // neterminale
std::set<std::string> Sigma;   // terminale
std::string start;
std::map<std::string, std::set<std::vector<std::string> > > R;

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
bool isTerminal(const std::string& x) { return Sigma.find(x) != Sigma.end(); }

// generez un nume nou de neterminal pornind de la o baza, evitand coliziunile
std::string freshName(const std::string& base) {
    if (!V.count(base) && !Sigma.count(base)) return base;
    int idx = 1;
    while (V.count(base + std::to_string(idx)) || Sigma.count(base + std::to_string(idx))) ++idx;
    return base + std::to_string(idx);
}

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
        R[lhs].insert(symbols);
    }
}

void readGrammar() {
    for (const std::string& x : splitSpaces(readNextLine(fin))) V.insert(x);
    for (const std::string& x : splitSpaces(readNextLine(fin))) Sigma.insert(x);
    start = splitSpaces(readNextLine(fin))[0];
    int ruleCount = std::stoi(splitSpaces(readNextLine(fin))[0]);
    for (int i = 0; i < ruleCount; ++i) parseRule(readNextLine(fin));
}

// Pasul 1: START - daca simbolul de start apare in vreo parte dreapta,
// introduc un start nou S0 -> S care nu mai apare nicaieri in dreapta
void stepSTART() {
    bool onRhs = false;
    for (auto& rule : R)
        for (const auto& prod : rule.second)
            for (const std::string& sym : prod)
                if (sym == start) onRhs = true;

    if (onRhs) {
        std::string newStart = freshName(start + "0");
        V.insert(newStart);
        R[newStart].insert({start});
        start = newStart;
    }
}

// Pasul 2: TERM - in regulile cu cel putin 2 simboluri inlocuiesc fiecare terminal t
// cu un neterminal nou X_t si adaug regula X_t -> t
void stepTERM() {
    std::map<std::string, std::string> termVar;
    std::map<std::string, std::set<std::vector<std::string> > > newR;

    for (auto& rule : R) {
        const std::string& A = rule.first;
        for (const auto& prod : rule.second) {
            if (prod.size() >= 2) {
                std::vector<std::string> np;
                for (const std::string& sym : prod) {
                    if (isTerminal(sym)) {
                        if (!termVar.count(sym)) {
                            std::string name = freshName("X_" + sym);
                            termVar[sym] = name;
                            V.insert(name);
                            newR[name].insert({sym});
                        }
                        np.push_back(termVar[sym]);
                    } else np.push_back(sym);
                }
                newR[A].insert(np);
            } else {
                newR[A].insert(prod);
            }
        }
    }
    R = newR;
}

// Pasul 3: BIN - sparg regulile A -> B1 B2 ... Bm cu m > 2 in lant de reguli binare
void stepBIN() {
    std::map<std::string, std::set<std::vector<std::string> > > newR;

    for (auto& rule : R) {
        const std::string& A = rule.first;
        for (const auto& prod : rule.second) {
            if (prod.size() <= 2) {
                newR[A].insert(prod);
            } else {
                std::string cur = A;
                for (int i = 0; i + 2 < (int)prod.size(); ++i) {
                    std::string next = freshName("C");
                    V.insert(next);
                    newR[cur].insert({prod[i], next});
                    cur = next;
                }
                newR[cur].insert({prod[prod.size() - 2], prod[prod.size() - 1]});
            }
        }
    }
    R = newR;
}

// Pasul 4: DEL - elimin lambda-productiile.
// gasesc neterminalele anulabile si pentru fiecare regula generez toate variantele
// in care simbolurile anulabile sunt prezente sau lipsesc (mai putin varianta vida)
void stepDEL() {
    std::set<std::string> nullable;
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto& rule : R) {
            if (nullable.count(rule.first)) continue;
            for (const auto& prod : rule.second) {
                bool allNullable = true;
                for (const std::string& sym : prod)
                    if (!nullable.count(sym)) { allNullable = false; break; }
                // productia vida sau cu toate simbolurile anulabile => neterminalul e anulabil
                if (allNullable) { nullable.insert(rule.first); changed = true; break; }
            }
        }
    }

    std::map<std::string, std::set<std::vector<std::string> > > newR;
    for (auto& rule : R) {
        const std::string& A = rule.first;
        for (const auto& prod : rule.second) {
            if (prod.empty()) continue; // lambda-productiile se sterg (start tratat mai jos)

            // pozitiile anulabile pot fi pastrate sau scoase -> toate combinatiile
            std::vector<int> nullPos;
            for (int i = 0; i < (int)prod.size(); ++i)
                if (isNonterminal(prod[i]) && nullable.count(prod[i])) nullPos.push_back(i);

            for (int mask = 0; mask < (1 << (int)nullPos.size()); ++mask) {
                std::set<int> removed;
                for (int b = 0; b < (int)nullPos.size(); ++b)
                    if (mask & (1 << b)) removed.insert(nullPos[b]);

                std::vector<std::string> variant;
                for (int i = 0; i < (int)prod.size(); ++i)
                    if (!removed.count(i)) variant.push_back(prod[i]);

                if (!variant.empty()) newR[A].insert(variant);
            }
        }
    }

    R = newR;
    // singura lambda-productie permisa: cea a simbolului de start, daca limbajul contine lambda
    if (nullable.count(start)) R[start].insert({});
}

// Pasul 5: UNIT - elimin regulile unitare A -> B.
// pentru fiecare pereche unitara (A, B) copiez in A toate productiile non-unitare ale lui B
void stepUNIT() {
    // inchiderea perechilor unitare (inclusiv (A, A))
    std::set<std::pair<std::string, std::string> > pairs;
    for (const std::string& A : V) pairs.insert({A, A});

    bool changed = true;
    while (changed) {
        changed = false;
        std::set<std::pair<std::string, std::string> > add;
        for (auto& p : pairs) {
            const std::string& A = p.first;
            const std::string& B = p.second;
            if (!R.count(B)) continue;
            for (const auto& prod : R[B]) {
                if (prod.size() == 1 && isNonterminal(prod[0])) {
                    std::pair<std::string, std::string> np = {A, prod[0]};
                    if (!pairs.count(np)) { add.insert(np); changed = true; }
                }
            }
        }
        for (auto& np : add) pairs.insert(np);
    }

    std::map<std::string, std::set<std::vector<std::string> > > newR;
    for (auto& p : pairs) {
        const std::string& A = p.first;
        const std::string& B = p.second;
        if (!R.count(B)) continue;
        for (const auto& prod : R[B]) {
            if (prod.size() == 1 && isNonterminal(prod[0])) continue; // sar peste cele unitare
            newR[A].insert(prod);
        }
    }
    R = newR;
}

void printGrammar() {
    fout << "Neterminale:";
    for (const std::string& x : V) fout << " " << x;
    fout << "\nTerminale:";
    for (const std::string& x : Sigma) fout << " " << x;
    fout << "\nSimbol de start: " << start << "\n";
    fout << "Reguli:\n";

    // afisez intai regulile simbolului de start, apoi restul
    std::vector<std::string> order;
    order.push_back(start);
    for (auto& rule : R) if (rule.first != start) order.push_back(rule.first);

    for (const std::string& A : order) {
        if (!R.count(A) || R[A].empty()) continue;
        fout << A << " ->";
        bool first = true;
        for (const auto& prod : R[A]) {
            fout << (first ? " " : " | ");
            first = false;
            if (prod.empty()) fout << lambda;
            else {
                for (int i = 0; i < (int)prod.size(); ++i)
                    fout << (i ? " " : "") << prod[i];
            }
        }
        fout << "\n";
    }
}

int main() {
    readGrammar();

    stepSTART();
    stepTERM();
    stepBIN();
    stepDEL();
    stepUNIT();

    printGrammar();
}
