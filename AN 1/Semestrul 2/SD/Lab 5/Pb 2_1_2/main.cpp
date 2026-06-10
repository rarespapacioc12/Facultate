// 100p - https://kilonova.ro/submissions/1111202 (I prefer kn)

#include <fstream>
#include <vector>
#include <string>
#include <climits>

std::ifstream fin("ratina.in");
std::ofstream fout("ratina.out");

struct TrieNode {
    TrieNode* children[26] = {};
};

TrieNode* root;
int N, M;
std::vector<std::vector<TrieNode*>> paths;

void insert(const std::string& s, int idx) {
    TrieNode* curr = root;
    paths[idx].reserve(s.size());
    for (char c : s) {
        int p = c - 'a';
        if (!curr->children[p]) {
            curr->children[p] = new TrieNode();
        }
        curr = curr->children[p];
        paths[idx].push_back(curr);
    }
}

int main() {
    fin >> N >> M;
    root = new TrieNode();
    paths.assign(N, {});

    std::string buf;
    for (int i = 0; i < N; ++i) {
        fin >> buf;
        insert(buf, i);
    }

    int ids[16];
    for (int q = 0; q < M; ++q) {
        int t;
        fin >> t;

        int min_len = INT_MAX;
        for (int i = 0; i < t; ++i) {
            fin >> ids[i];
            --ids[i];
            int len = (int)paths[ids[i]].size();
            if (len < min_len) {
                min_len = len;
            }
        }

        int lo = 0, hi = min_len;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            TrieNode* ref = paths[ids[0]][mid - 1];
            bool ok = true;
            for (int i = 1; i < t; ++i) {
                if (paths[ids[i]][mid - 1] != ref) { 
                    ok = false; 
                    break; 
                }
            }
            if (ok) { 
                lo = mid;
            }
            else {
                hi = mid - 1;
            }
        }

        fout << lo << '\n';
    }
}
