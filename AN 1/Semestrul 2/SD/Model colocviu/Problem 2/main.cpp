#include <bits/stdc++.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int NMAX = 1.5e5;

struct Node {
    int occ;
    int val;
    Node() : occ(0), val(0) {}
};


int n, cnt;
unordered_map<int, int> ap;

class StreamGcdCalculator{
    Node seg[4 * NMAX + 5];
    int N;

    void increment(int node, int st, int dr, int poz) {
        if(st == dr) {
            ++seg[node].occ;
            seg[node].val = ap[poz];
        }
        else {
            int m = (st + dr) / 2;
            if(poz <= m) {
                increment(2 * node, st, m, poz);
            }
            else {
                increment(2 * node + 1, m + 1, dr, poz);
            }
            seg[node].val = __gcd(seg[2 * node].val, seg[2 * node + 1].val);
        }
    }

    void decrement(int node, int st, int dr, int poz) {
        if(st == dr) {
            --seg[node].occ;
            if(seg[node].occ == 0){
                seg[node].val = 0;
            }
        }
        else {
            int m = (st + dr) / 2;
            if(poz <= m) {
                increment(2 * node, st, m, poz);
            }
            else {
                increment(2 * node + 1, m + 1, dr, poz);
            }
            seg[node].val = __gcd(seg[2 * node].val, seg[2 * node + 1].val);
        }
    }
public:
    StreamGcdCalculator(int x) : N(x) {}
    void insert(int x) {
        if(ap.find(x) == ap.end()) {
            ap[x] = ++cnt;
        }
        increment(1, 1, N, ap[x]);
    }

    void erase(int x) {
        decrement(1, 1, N, ap[x]);
    }

    int gcd() {
        return seg[1].val;
    } 
};
int main () {
    fin >> n;
    StreamGcdCalculator s(n);
    for(int i = 1; i <= n; ++i) {
        int tip, x;
        fin >> tip;
        if(tip == 1) {
            fin >> x;
            s.insert(x);
        }
        else if(tip == 2) {
            fin >> x;
            s.erase(x);
        }
        else {
            fout << s.gcd() << '\n';
        }
    }
}