#include <fstream>
#include <set>
#include <algorithm>

std::ifstream fin("sea2.in");
std::ofstream fout("sea2.out");

typedef std::pair<int, int> point;

int N;
std::set<point> S;

int main(){
    fin >> N;

    S.insert({0, 3e5});
    S.insert({3e5, 0});
    for(point p; N--;){
        fin >> p.first >> p.second;      
        auto it = S.lower_bound(p);
        if(it->second > p.second){
            fout << "-1\n";
        }
        else{
            auto end = it;
            while(it != S.begin() && it->second < p.second){
                --it;
            }
            ++it;
            S.erase(it, end);
            S.insert(p);
            fout << S.size() - 2 << '\n';
        }
    }
}