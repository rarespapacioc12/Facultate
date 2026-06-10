#include <fstream>
#include <algorithm>

std::ifstream fin("maxq.in");
std::ofstream fout("maxq.out");

typedef long long ll;
const int NMAX = 2e5;

struct Node {
    ll sum;
    ll pref;
    ll suff;
    ll maxq;
};

int N, M;
Node seg[4 * NMAX + 5];

Node merge(Node st, Node dr) {
    Node p;

    p.sum = st.sum + dr.sum;
    p.pref = std::max(st.pref, st.sum + dr.pref);
    p.suff = std::max(dr.suff, dr.sum + st.suff);
    p.maxq = std::max({st.maxq, dr.maxq, st.suff + dr.pref});

    return p;
}

void build(int node, int st, int dr) {
    if (st == dr) {
        fin >> seg[node].sum;
        seg[node].pref = std::max(0ll, seg[node].sum);
        seg[node].suff = std::max(0ll, seg[node].sum);
        seg[node].maxq = std::max(0ll, seg[node].sum);
    }
    else {
        int m = (st + dr) / 2;
        build(2 * node, st, m);
        build(2 * node + 1, m + 1, dr);
        seg[node] = merge(seg[2 * node], seg[2 * node + 1]);
    }
}

void update(int node, int st, int dr, int poz, ll val) {
    if (st == dr) {
        seg[node].sum = val;
        seg[node].pref = std::max(0ll, val);
        seg[node].suff = std::max(0ll, val);
        seg[node].maxq = std::max(0ll, val);
    }
    else {
        int m = (st + dr) / 2;
        if (poz <= m) {
            update(2 * node, st, m, poz, val);
        }
        else {
            update(2 * node + 1, m + 1, dr, poz, val);
        }
        seg[node] = merge(seg[2 * node], seg[2 * node + 1]);
    }
}

Node query(int node, int st, int dr, int qL, int qR) {
    if (qL <= st && dr <= qR) {
        return seg[node];
    }
    else {
        int m = (st + dr) / 2;
        if (qR <= m) {
            return query(2 * node, st, m, qL, qR);
        }
        if (m < qL) {
            return query(2 * node + 1, m + 1, dr, qL, qR);
        }
        return merge(query(2 * node, st, m, qL, qR), query(2 * node + 1, m + 1, dr, qL, qR));
    }
}

int main() {
    fin >> N;
    build(1, 1, N);
    fin >> M;
    for (;M--;) {
        int tip;
        fin >> tip;
        if (tip == 0) {
            int poz;
            ll val;
            fin >> poz >> val;
            update(1, 1, N, poz + 1, val);
        }
        else {
            int a, b;
            fin >> a >> b;
            fout << query(1, 1, N, a + 1, b + 1).maxq << '\n';
        }
    }
}