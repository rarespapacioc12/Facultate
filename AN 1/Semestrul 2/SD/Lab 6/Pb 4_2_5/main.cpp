// https://www.infoarena.ro/job_detail/3355934
// Deci iti zic sincer ca aici m-a ajutat claude putin 
// Legit am incercat toate variantele posibile de AINT si AIB
// Si ma gandeam ca o sa iasa elegant cu bitset sau ceva, dar eram pe la 60mb at best (imi intrau pe 60)
// Nu stiam asa bine Mo, dar ma bucur ca am invatat ceva nou.

#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>

std::ifstream fin("infinitywar.in");
std::ofstream fout("infinitywar.out");

const int W = (10000 + 64) / 64;

int N, Q, block;
uint64_t cur[W];

std::vector<short> armies[50001];
int ans[100001];

struct Query { int l, r, idx; };

void toggle(int i) {
    for (short x : armies[i])
        cur[x / 64] ^= (1ULL << (x % 64));
}

int popcount() {
    int cnt = 0;
    for (int j = 0; j < W; j++)
        cnt += __builtin_popcountll(cur[j]);
    return cnt;
}

int main() {
    fin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        int k, x;
        fin >> k;
        armies[i].resize(k);
        for (int j = 0; j < k; j++)
            fin >> armies[i][j];
    }

    block = std::max(1, (int)std::sqrt(N));
    Query queries[100001];
    for (int i = 0; i < Q; i++) {
        fin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    std::sort(queries, queries + Q, [](const Query& a, const Query& b) {
        int ba = a.l / block, bb = b.l / block;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? a.r > b.r : a.r < b.r;
    });

    int l = 1, r = 0;
    for (int i = 0; i < Q; i++) {
        while (r < queries[i].r) toggle(++r);
        while (l > queries[i].l) toggle(--l);
        while (r > queries[i].r) toggle(r--);
        while (l < queries[i].l) toggle(l++);
        ans[queries[i].idx] = popcount();
    }

    for (int i = 0; i < Q; i++)
        fout << ans[i] << '\n';
}