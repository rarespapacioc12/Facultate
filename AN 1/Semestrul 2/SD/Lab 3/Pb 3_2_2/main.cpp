// https://www.infoarena.ro/job_detail/3349498

#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <set>
#include <deque>

std::ifstream fin("secv5.in");
std::ofstream fout("secv5.out");

std::vector<long long> v;
long long n, l, u;

long long count(int dim){
    if(dim == 0){
        return 0;
    }
    std::unordered_map<long long, int> ap;
    std::vector<long long> dp(n + 1, 0);
    int lasti = 0;
    long long counter = 0;
    for(int i = 0; i < n; ++i){
        if(ap.find(v[i]) != ap.end()){
            ++ap[v[i]];
            --dp[i + 1];
            ++dp[lasti];
        }
        else{
            if((int)ap.size() < dim){
                ap[v[i]] = 1;
                --dp[i + 1];
                ++dp[lasti];
            }
            else{
                while((int)ap.size() == dim){
                    ap[v[lasti]]--;
                    if(ap[v[lasti]] == 0){
                        ap.erase(v[lasti]);
                    }
                    ++lasti;
                }
                ap[v[i]] = 1;
                ++dp[lasti];
                --dp[i + 1];
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(i > 0){
            dp[i] += dp[i - 1];
        }
        counter += dp[i];
    }
    return counter;
}

int main(){
    fin >> n >> l >> u;

    v.resize(n);
    
    for(auto& x : v){
        fin >> x;
    }
    fout << count(u) - count(l - 1);
}