#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Transition {
    std::string v;
    std::string pop_sym;
    std::string push_sym;
};

struct Step {
    std::string processed;
    std::string state;
    std::string stack;
};

std::vector<std::string> splitSpaces(const std::string& line) {
    std::vector<std::string> res;
    std::string cur;
    for (char c : line) {
        if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
            if (!cur.empty()) {
                res.push_back(cur);
                cur.clear();
            }
        } else {
            cur += c;
        }
    }
    if (!cur.empty()) res.push_back(cur);
    return res;
}

std::string readNextLine(std::ifstream& in) {
    std::string line;
    while (std::getline(in, line)) {
        bool empty = true;
        for (char c : line) {
            if (c != ' ' && c != '\r' && c != '\n' && c != '\t') {
                empty = false;
                break;
            }
        }
        if (!empty) return line;
    }
    return "";
}

bool dfs(
    const std::string& state,
    size_t w_idx,
    const std::string& word,
    std::string& stack,
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Transition>>>& g,
    int acc_type,
    const std::unordered_set<std::string>& f_states,
    std::vector<Step>& path,
    std::vector<Step>& longest_path
) {
    path.push_back({word.substr(0, w_idx), state, stack});
    
    if (path.size() > longest_path.size()) {
        longest_path = path;
    }
    
    if (w_idx == word.length()) {
        bool acc = false;
        if (acc_type == 0 && stack.empty()) acc = true;
        else if (acc_type == 1 && f_states.find(state) != f_states.end()) acc = true;
        else if (acc_type == 2 && stack.empty() && f_states.find(state) != f_states.end()) acc = true;
        
        if (acc) return true;
    }

    std::vector<std::string> syms = {"_"};
    if (w_idx < word.length()) syms.push_back(std::string(1, word[w_idx]));

    for (const std::string& sym : syms) {
        if (g[state].find(sym) != g[state].end()) {
            for (const auto& tr : g[state][sym]) {
                bool popped = false;
                char popped_ch = 0;
                
                if (tr.pop_sym != "_") {
                    if (stack.empty() || stack.back() != tr.pop_sym[0]) continue;
                    popped_ch = stack.back();
                    stack.pop_back();
                    popped = true;
                }
                
                int pushed = 0;
                if (tr.push_sym != "_") {
                    for (int i = (int)tr.push_sym.length() - 1; i >= 0; --i) {
                        stack.push_back(tr.push_sym[i]);
                        pushed++;
                    }
                }
                
                if (dfs(tr.v, w_idx + (sym == "_" ? 0 : 1), word, stack, g, acc_type, f_states, path, longest_path)) {
                    return true;
                }
                
                for (int i = 0; i < pushed; ++i) stack.pop_back();
                if (popped) stack.push_back(popped_ch);
            }
        }
    }
    
    path.pop_back();
    return false;
}

int main() {
    std::ifstream fin("input.txt");

    std::vector<std::string> states = splitSpaces(readNextLine(fin));
    std::vector<std::string> alphabet = splitSpaces(readNextLine(fin));
    std::string init_state = splitSpaces(readNextLine(fin))[0];
    std::string init_stack_sym = splitSpaces(readNextLine(fin))[0];
    int n = std::stoi(splitSpaces(readNextLine(fin))[0]);

    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Transition>>> g;
    for (int i = 0; i < n; ++i) {
        std::vector<std::string> pts = splitSpaces(readNextLine(fin));
        if (pts.size() >= 5) {
            std::string u = pts[0], sym = pts[1], v = pts[2], pop_s = pts[3], push_s = pts[4];
            g[u][sym].push_back({v, pop_s, push_s});
        }
    }

    int acc_type = std::stoi(splitSpaces(readNextLine(fin))[0]);
    // 0 = stiva vida
    // 1 = stare finala
    // 2 = ambele
    
    std::unordered_set<std::string> final_states;
    std::string last_line = readNextLine(fin);
    if (!last_line.empty()) {
        std::vector<std::string> f_states = splitSpaces(last_line);
        for (const auto& s : f_states) final_states.insert(s);
    }

    std::ifstream wordIn("word.txt");
    std::ofstream fout("output.txt");

    std::string wLine;
    while (std::getline(wordIn, wLine)) {
        std::vector<std::string> wPts = splitSpaces(wLine);
        if (wPts.empty()) continue;
        
        std::string word = wPts[0];
        if (word == "_") word = "";

        std::string stack = init_stack_sym;
        std::vector<Step> path;
        std::vector<Step> longest_path;
        
        bool accepted = dfs(init_state, 0, word, stack, g, acc_type, final_states, path, longest_path);

        fout << "Cuvant: " << (word.empty() ? "_" : word) << "\n";
        
        const auto& path_to_print = accepted ? path : longest_path;
        
        for (const auto& step : path_to_print) {
            fout << (step.processed.empty() ? "_" : step.processed) 
                << " " << step.state 
                << " " << (step.stack.empty() ? "_" : step.stack) << "\n";
        }
        
        if (accepted) {
            fout << "-> Word accepted.\n\n";
        } else {
            fout << "-> Word rejected. (ultimul drum explorat)\n\n";
        }
    }
}