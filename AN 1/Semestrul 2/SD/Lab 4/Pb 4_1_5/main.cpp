#include <iostream>
#include <vector>
#include <queue>

const int NMAX = 99615;
const int MOD = 998244353;

int N;
std::vector<bool> viz;
std::vector<std::vector<int> > G;
std::vector<std::vector<std::vector<int> > > dp; //dp[i][j][k] = nr de moduri de a colora arborele astfel incat pe drumul
// de la 1 la i se afla exact j noduri colorate cu negru si nodul i il colorez cu k
// 0 = negru, 1 = rosu

// Am doua frunze v si w
// fie u = lca(v, w)
// atunci daca proprietatea se respecta pt lca(v, w)

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;
    G.resize(N + 1);
    viz.resize(N + 1);
    dp = std::vector<std::vector<std::vector<int> > >(N + 1);
    for(int x, y, i = 1; i < N; ++i){
        std::cin >> x >> y;
        G[x].push_back(y);
    }

    dp[1][1][0] = 1;

    std::queue<int> q;
    q.push(1);
    viz[1] = true;

    while(!q.empty()){

    }
}