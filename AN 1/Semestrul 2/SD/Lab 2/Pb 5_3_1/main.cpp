// https://www.infoarena.ro/job_detail/3347824

#include <fstream>
#include <deque>
#include <vector>

std::ifstream fin("deque.in");
std::ofstream fout("deque.out");

int n, k;
long long s;
std::vector<int> v;

int main(){
    fin >> n >> k;

    v.resize(n);
    for(int& x : v){
        fin >> x;
    }
    
    std::deque<int> d;

    for(int i = 0; i < n; ++i){
        if(i < k){
            while(!d.empty() && v[i] < v[d.front()]){
                d.pop_front();
            }
            d.push_front(i);
        }
        else{
            s += v[d.back()];
            while(!d.empty() && i - d.back() >= k){
                d.pop_back();
            }
            while(!d.empty() && v[i] < v[d.front()]){
                d.pop_front();
            }
            d.push_front(i);
        }
    }
    s += v[d.back()];
    fout << s;
}