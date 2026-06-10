// https://www.infoarena.ro/job_detail/3355906

#include <fstream>

typedef long long ll;

std::ifstream fin("mit.in");
std::ofstream fout("mit.out");

struct Node {
    ll lazy;
    ll val;
    Node() = default;
    Node(ll val, ll lazy = 0) : lazy(lazy), val(val) {}
};

const ll NMAX = 1e5;

ll N, Q, x;
Node seg[4 * NMAX + 5];

void push(ll node, ll st, ll dr) {
    if (seg[node].lazy != 0) {
        if (st != dr) {
            seg[2 * node].val += seg[node].lazy;
            seg[2 * node].lazy += seg[node].lazy;
            seg[2 * node + 1].val += seg[node].lazy;
            seg[2 * node + 1].lazy += seg[node].lazy;
        }
        seg[node].lazy = 0;
    }
}

void build(ll node, ll st, ll dr) {
    if (st == dr) {
        fin >> x;
        seg[node] = Node(x);
    } else {
        ll m = (st + dr) / 2;
        build(node * 2, st, m);
        build(node * 2 + 1, m + 1, dr);
        seg[node].val = std::max(seg[2 * node].val, seg[2 * node + 1].val);
    }
}

void update(ll node, ll st, ll dr, ll L, ll R, ll val) {
    if (L <= st && dr <= R) {
        seg[node].val += val;
        seg[node].lazy += val;
        return;
    }
    push(node, st, dr);
    ll m = (st + dr) / 2;
    if (R <= m) {
        update(2 * node, st, m, L, R, val);
    } else if (m < L) {
        update(2 * node + 1, m + 1, dr, L, R, val);
    } else {
        update(2 * node, st, m, L, R, val);
        update(2 * node + 1, m + 1, dr, L, R, val);
    }
    seg[node].val = std::max(seg[2 * node].val, seg[2 * node + 1].val);
}

ll query(ll node, ll st, ll dr, ll L, ll R) {
    if (L <= st && dr <= R) {
        return seg[node].val;
    }
    push(node, st, dr);
    ll m = (st + dr) / 2;
    if (R <= m) {
        return query(2 * node, st, m, L, R);
    }
    if (m < L) {
        return query(2 * node + 1, m + 1, dr, L, R);
    }
    return std::max(query(2 * node, st, m, L, R), query(2 * node + 1, m + 1, dr, L, R));
}

int main() {
    fin >> N >> Q;
    build(1, 1, N);
    for (ll tip; Q--;) {
        fin >> tip;
        if (tip == 1) {
            ll L, R;
            fin >> L >> R;
            fout << query(1, 1, N, L, R) << '\n';
        } else {
            ll L, R, X;
            fin >> L >> R >> X;
            update(1, 1, N, L, R, X);
        }
    }
}