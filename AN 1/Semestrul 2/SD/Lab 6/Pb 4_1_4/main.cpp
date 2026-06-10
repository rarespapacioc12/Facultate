/*
You are given an array a of n integers and a non-idempotent function f. Answer
q queries of the form (l, r): compute f(a[l . . . r]). Aim for an O(n log n+q) time
complexity algorithm.

Inca ma bantuie SAI...
*/

#include <fstream>
#include <algorithm>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const int NMAX = 1e6;
const int LOGMAX = 21;

int N, Q, E[2 * NMAX + 5], rmq[LOGMAX][NMAX + 5];

// testing with sum since it is non-idempotent
int f(int a, int b) {
    return a + b;
}

// basically, because the standard rmq uses overlapping intervals for providing the result
// therefore, I need to change how I build it and how to query without doing that
// a first idea would be an qlogn solution similar to fenwick trees
/* int query(int st, int dr) {
    int len = dr - st + 1;
    int res = 0;
    int idx = st;
    for (int e = E[len]; e >= 0; --e) {
        if (idx + (1 << e) - 1 <= dr) {
            res = f(res, rmq[e][idx]);
            idx += (1 << e);
        }
    }
    return res;
}*/

// After some research I found out about disjoint sparse tables

int query(int st, int dr) {
    if (st == dr) {
        return rmq[0][st];
    }

    int e = E[(st - 1) ^ (dr - 1)] + 1;

    return f(rmq[e][st], rmq[e][dr]);
}

int main() {
    fin >> N;

    for (int i = 1; i <= N; ++i) {
        fin >> rmq[0][i];
    }

    for (int i = 2; i <= 2 * NMAX; ++i) {
        E[i] = 1 + E[i >> 1];
    }

    // the build for the qlogn soluton
    /* for (int i = 1; (1 << i) <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            rmq[i][j] = rmq[i - 1][j];
            if (j + (1 << (i - 1)) <= N) {
                rmq[i][j] = f(rmq[i][j], rmq[i - 1][j + (1 << (i - 1))]);
            }
        }
    }*/

    for (int e = 1; (1 << e) <= 2 * N; ++e) {
        int len = (1 << e);
        int half = len >> 1;

        for (int i = 1; i <= N; i += len) {
            int mid = i + half - 1;
            int r_boundary = i + len - 1;

            // first half suffixes
            if (mid >= i) {
                // Ne asigurăm doar că nu pornim de dincolo de N
                int actual_mid = std::min(N, mid);
                rmq[e][actual_mid] = rmq[0][actual_mid];
                for (int j = actual_mid - 1; j >= i; --j) {
                    rmq[e][j] = f(rmq[0][j], rmq[e][j + 1]);
                }
            }

            // second half prefixess
            if (mid + 1 <= N) {
                int actual_r = std::min(N, r_boundary);
                rmq[e][mid + 1] = rmq[0][mid + 1];
                for (int j = mid + 2; j <= actual_r; ++j) {
                    rmq[e][j] = f(rmq[e][j - 1], rmq[0][j]);
                }
            }
        }
    }

    fin >> Q;

    for (int st, dr; Q--;) {
        fin >> st >> dr;
        fout << query(st, dr) << '\n';
    }
}