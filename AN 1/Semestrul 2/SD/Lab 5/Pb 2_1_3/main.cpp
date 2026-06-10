#include <fstream>
#include <vector>

std::ifstream fin("xormax.in");
std::ofstream fout("xormax.out");

struct TrieNode {
    int child[2];
    int max_idx;
    TrieNode() : child{-1, -1}, max_idx(-1) {}
};

const int MAX_BIT = 30;

void insert_value(std::vector<TrieNode>& trie, int value, int idx) {
    int node = 0;
    if (trie[node].max_idx < idx) {
        trie[node].max_idx = idx;
    }
    for (int b = MAX_BIT; b >= 0; --b) {
        int bit = (value >> b) & 1;
        if (trie[node].child[bit] == -1) {
            trie[node].child[bit] = (int)trie.size();
            trie.emplace_back();
        }
        node = trie[node].child[bit];
        if (trie[node].max_idx < idx) {
            trie[node].max_idx = idx;
        }
    }
}

int query_best(std::vector<TrieNode>& trie, int value, int& best_idx) {
    int node = 0;
    int best_xor = 0;
    for (int b = MAX_BIT; b >= 0; --b) {
        int bit = (value >> b) & 1;
        int desired = bit ^ 1;
        if (trie[node].child[desired] != -1) {
            best_xor |= (1 << b);
            node = trie[node].child[desired];
        }
        else {
            node = trie[node].child[bit];
        }
    }
    best_idx = trie[node].max_idx;
    return best_xor;
}

int main() {
    int N = 0;
    fin >> N;

    std::vector<int> v(N);
    for (int& x : v) {
        fin >> x;
    }

    std::vector<TrieNode> trie;
    trie.emplace_back();

    int prefix = 0;
    int best_val = 0;
    int best_l = 1;
    int best_r = 1;
    int best_len = N + 1;

    insert_value(trie, 0, 0);

    for (int r = 1; r <= N; ++r) {
        prefix ^= v[r - 1];
        int idx = 0;
        int curr = query_best(trie, prefix, idx);
        int l = idx + 1;
        int len = r - idx;

        if (curr > best_val || (curr == best_val && r == best_r && len < best_len)) {
            best_val = curr;
            best_l = l;
            best_r = r;
            best_len = len;
        }

        insert_value(trie, prefix, r);
    }

    fout << best_val << ' ' << best_l << ' ' << best_r;
    return 0;
}