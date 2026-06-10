// O(n log n log val_max) - procesare inversa offline + small-to-large merge cu trie binar
// https://csacademy.com/submission/7534365

#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_BIT = 30;

struct TrieNode {
    int child[2] = {-1, -1};
};

std::vector<TrieNode> trie_pool;
std::vector<int> free_list;

int new_node() {
    if (!free_list.empty()) {
        int id = free_list.back();
        free_list.pop_back();
        trie_pool[id].child[0] = -1;
        trie_pool[id].child[1] = -1;
        return id;
    }
    int id = (int)trie_pool.size();
    trie_pool.emplace_back();
    return id;
}

void free_subtree(int u) {
    if (u == -1) {
        return;
    }
    free_subtree(trie_pool[u].child[0]);
    free_subtree(trie_pool[u].child[1]);
    free_list.push_back(u);
}

void insert_value(int root, int value) {
    int node = root;
    for (int b = MAX_BIT; b >= 0; --b) {
        int bit = (value >> b) & 1;
        if (trie_pool[node].child[bit] == -1) {
            int fresh = new_node();
            trie_pool[node].child[bit] = fresh;
        }
        node = trie_pool[node].child[bit];
    }
}

int query_max(int root, int value) {
    int node = root;
    int best = 0;
    for (int b = MAX_BIT; b >= 0; --b) {
        int bit = (value >> b) & 1;
        int desired = bit ^ 1;
        if (trie_pool[node].child[desired] != -1) {
            best |= (1 << b);
            node = trie_pool[node].child[desired];
        }
        else {
            node = trie_pool[node].child[bit];
        }
    }
    return best;
}

struct Segment {
    int root = -1;
    int best_xor = 0;
    std::vector<int> values;
};

void merge_segments(std::vector<Segment>& seg, int a, int b) {
    Segment& A = seg[a];
    Segment& B = seg[b];
    A.best_xor = std::max(A.best_xor, B.best_xor);

    if (A.values.size() >= B.values.size()) {
        for (int x : B.values) {
            A.best_xor = std::max(A.best_xor, query_max(A.root, x));
            insert_value(A.root, x);
        }
        A.values.insert(A.values.end(), B.values.begin(), B.values.end());
        free_subtree(B.root);
        B.root = -1;
        B.values.clear();
    }
    else {
        for (int x : A.values) {
            A.best_xor = std::max(A.best_xor, query_max(B.root, x));
            insert_value(B.root, x);
        }
        B.values.insert(B.values.end(), A.values.begin(), A.values.end());
        free_subtree(A.root);
        A.root = -1;
        A.values.clear();
        B.best_xor = A.best_xor;
        std::swap(A, B);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 0;
    std::cin >> N;

    std::vector<int> v(N + 1, 0);
    std::vector<int> order(N + 1, 0);
    std::vector<int> prefix_xor(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        std::cin >> v[i];
    }
    for (int i = 1; i <= N; ++i) {
        prefix_xor[i] = prefix_xor[i - 1] ^ v[i];
    }
    for (int i = 1; i <= N; ++i) {
        std::cin >> order[i];
    }

    std::reverse(order.begin() + 1, order.end());

    trie_pool.reserve(6000000);

    std::vector<bool> active(N + 2, false);
    std::vector<int> left_end(N + 2, 0);
    std::vector<int> right_end(N + 2, 0);
    std::vector<Segment> seg(N + 1);
    std::vector<int> ans(N + 1, 0);

    int global_max = 0;

    for (int step = 1; step <= N; ++step) {
        int p = order[step];
        active[p] = true;

        Segment& S = seg[p];
        S.root = new_node();
        S.values.clear();
        S.values.push_back(prefix_xor[p - 1]);
        insert_value(S.root, prefix_xor[p - 1]);
        S.best_xor = query_max(S.root, prefix_xor[p]);
        insert_value(S.root, prefix_xor[p]);
        S.values.push_back(prefix_xor[p]);
        left_end[p] = p;
        right_end[p] = p;
        int curr = p;

        if (p > 1 && active[p - 1]) {
            int l = left_end[p - 1];
            merge_segments(seg, l, curr);
            right_end[l] = p;
            left_end[p] = l;
            curr = l;
        }
        if (p < N && active[p + 1]) {
            int r = right_end[p + 1];
            merge_segments(seg, curr, p + 1);
            right_end[curr] = r;
            left_end[r] = curr;
        }

        global_max = std::max(global_max, seg[curr].best_xor);
        ans[step] = global_max;
    }

    for (int j = 1; j <= N; ++j) {
        std::cout << ans[N - j + 1] << '\n';
    }

    return 0;
}
