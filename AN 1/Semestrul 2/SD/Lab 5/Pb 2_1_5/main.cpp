// https://codeforces.com/gym/104009/submission/375225462

#include <iostream>
#include <array>
#include <string>
#include <set>

struct compare{
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    }
};

struct TrieNode {
    std::set<std::pair<int, int>, compare> k_recent;
    TrieNode* father;
    std::array<TrieNode*, 26> children;
    std::pair<int, int> word_data = {0, 0};
    TrieNode (TrieNode* father) : father(father) { children.fill(nullptr); }
};

int Q, K, id_count = 0;
TrieNode* root = new TrieNode(nullptr);

TrieNode* add_letter(TrieNode* curr, char c){
    int idx = c - 'a';
    if(curr->children[idx] == nullptr) {
        curr->children[idx] = new TrieNode(curr);
    }
    return curr->children[idx];
}

void propagate(TrieNode* curr, const std::pair<int, int>& p) {
    while (curr != nullptr) {
        if (p.first > 1) {
            curr->k_recent.erase({p.first - 1, p.second});
        }
        if ((int)curr->k_recent.size() < K) {
            curr->k_recent.insert(p);
        }
        else {
            auto worst_it = std::prev(curr->k_recent.end());
            if (compare()(p, *worst_it)) {
                curr->k_recent.erase(worst_it);
                curr->k_recent.insert(p);
            }
            else {
                // p doesn't beat this node's worst, and old entry wasn't here either
                // (if old was erased, size would be K-1 and we'd be in the branch above).
                // Ancestors are strictly more competitive, so p won't beat them either.
                break;
            }
        }
        curr = curr->father;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> Q >> K;

    TrieNode* curr = root;

    for (int type; Q--;) {
        std::cin >> type;
        if (type == 1) {
            char c;
            std::cin >> c;
            curr = add_letter(curr, c);
            if (curr->k_recent.empty()) {
                std::cout << "-1\n";
            }
            else{
                std::string output;
                for (auto [x, y] : curr->k_recent) {
                    output += std::to_string(y);
                    output += ' ';
                }
                output.back() = '\n';
                std::cout << output;
            }
        }
        else if (type == 2) {
            curr = root;
        }
        else if (type == 3) {
            if (curr != root) {
                curr = curr->father;
            }
        }
        else {
            auto& wd = curr->word_data;
            if (wd.first == 0) {
                wd = {1, id_count};
            }
            else {
                ++wd.first;
            }
            propagate(curr, wd);
        }
        ++id_count;
    }
}
