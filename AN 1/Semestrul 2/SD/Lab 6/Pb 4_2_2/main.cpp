// https://www.infoarena.ro/job_detail/3241517 - asta e cu aib ca e mai usor de bagat, daca imi aduc aminte bag si aint

#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin("inv.in");
std::ofstream fout("inv.out");

const int MOD = 9917;
int N, count, seg[400005];
std::vector<std::pair<int, int>> v;

void update(int node, int st, int dr, int poz) {
    if (st == dr) {
        ++seg[node];
        return;
    }
    else {
        int m = (st + dr) / 2;
        if (poz <= m) {
            update(2 * node, st, m, poz);
        }
        else {
            update(2 * node + 1, m + 1, dr, poz);
        }
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
}

int query(int node, int st, int dr, int qL, int qR) {
    if (qL > qR) {
        return 0;
    }
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
        return query(2 * node, st, m, qL, qR) + query(2 * node + 1, m + 1, dr, qL, qR);
    }
}

int main() {
    fin >> N;

    v.resize(N);

    for (int i = 0; i < N; ++i) {
        fin >> v[i].first;
        v[i].second = i;
    }

    std::sort(v.begin(), v.end());

    for(int i = 0; i < N; ++i) {
        v[i].first = i + 1;
    }

    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    for (int x, i = 0; i < N; ++i) {
        update(1, 1, N, v[i].first);
        count += query(1, 1, N, v[i].first + 1, N);
        count %= MOD;
    }
    fout << count;
}