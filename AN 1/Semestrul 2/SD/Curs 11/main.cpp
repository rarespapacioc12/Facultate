// sqrt decomposition
// update + query - O(sqrt(N))

// agar - MIUB 202?
// tii pt fiecare val intervalul (x, 2x) si cand urci in arbore ii dai merge

#include <iostream>
#include <set>

typedef std::pair<int, int> pii;

const int NMAX = 1e5;

int N, Q;
std::set<pii> seg[4 * NMAX + 5];

bool can_be_merged(pii a, pii b){
    return (a.first <= b.first && a.second >= b.first) ||
    (b.first <= a.first && b.second >= a.first);
}

std::set<pii> merge_intervals(const std::set<pii>& a, const std::set<pii>& b){
    auto ans = a;
    for(auto interval : b){

    }
}

void init(int node, int st, int dr){
    if(st == dr){
        int x;
        std::cin >> x;
        seg[node] = std::set<pii>{{x, 2 * x}};
    }
    else{
        int m = st + ((dr - st) >> 1);

        init(node << 1, st, m);
        init(node << 1 | 1, m + 1, dr);

        seg[node] = merge_intervals(seg[node << 1], seg[node << 1 | 1]);
    }
}

std::set<pii> query(int node, int st, int dr, int qL, int qR){
    if(qL <= st && dr <= qR){
        return seg[node];
    }
    else{
        int m = st + ((dr - st) >> 1);

        if(qR <= m){
            return query(node << 1, st, m, qL, qR);
        }
        if(m < qL){
            return query(node << 1 | 1, m + 1, dr, qL, qR);
        }
        return merge_intervals(
            query(node << 1, st, m, qL, qR),
            query(node << 1 | 1, m + 1, dr, qL, qR)
        );
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N >> Q;

    init(1, 1, N);

    for(int l, r; Q--;){
        std::cin >> l >> r;
        auto ans = query(1, 1, N, l + 1, r + 1);
        std::cout << (ans.size() == 1) ? "DA\n" : "NU\n";
    }
}