// https://www.infoarena.ro/job_detail/3349499

#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>

std::ifstream fin("subsecvente2.in");
std::ofstream fout("subsecvente2.out");

std::vector<std::string> v;
int n, sol;

int main()
{
    fin >> n;
    v.resize(n);
    for(int i = 0; i < n; ++i)
        fin >> v[i];
        
    int st = 0, dr = 60;
    
    while(st <= dr){
        int m = (st + dr) / 2, ok = 0;
        std::unordered_map<std::string, std::array<bool, 5> > M;
        for(int j = 0; j < n; ++j)
           for(int i = 0; i + m - 1 < v[j].size(); ++i)
                M[v[j].substr(i, m)][j] = true;
        
        for(auto elem : M){
            int cnt = 0;
            for(int i = 0; i < n; ++i)
                cnt += M[elem.first][i];
            if(cnt == n){
                ok = true;
                break;
            }
        }
        
        if(ok)
            sol = m, st = m + 1;
        else
            dr = m - 1;
    }
    fout << sol;
}