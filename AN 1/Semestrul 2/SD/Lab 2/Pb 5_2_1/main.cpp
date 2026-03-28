// https://kilonova.ro/submissions/286676
// https://infoarena.ro/job_detail/3347794

#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;

#define POZ pair<int, int>

ifstream fin("alee.in");
ofstream fout("alee.out");

vector<vector <int> > a;

void border() {
    for (int i = 0; i < a.size(); ++i) {
        a[0][i] = -1;
        a[a.size() - 1][i] = -1;
        a[i][0] = -1;
        a[i][a.size() - 1] = -1;
    }
}

int main() {
    queue <POZ> q;
    int n, m, x, y, dl[] = { -1, 0, 1, 0 }, dc[] = { 0, -1, 0, 1 };
    POZ pcrt, vec, start, stop;
    fin >> n >> m;
    a.resize(n + 2);
    for (int i = 0; i < n + 2; ++i)
        a[i].resize(n + 2);
    for (int i = 1; i <= m; ++i) {
        fin >> x >> y;
        a[x][y] = -1;
    }
    border();
    fin >> start.first >> start.second >> stop.first >> stop.second;
    q.push(start);
    a[start.first][start.second] = 1;
    while (!q.empty() and a[stop.first][stop.second] == 0) {
        pcrt = q.front();
        for (int i = 0; i < 4; ++i) {
            vec = make_pair(pcrt.first + dl[i], pcrt.second + dc[i]);
            if (a[vec.first][vec.second] == 0) {
                q.push(vec);
                a[vec.first][vec.second] = a[pcrt.first][pcrt.second] + 1;
            }
        }
        q.pop();
    }
    fout << a[stop.first][stop.second];
}