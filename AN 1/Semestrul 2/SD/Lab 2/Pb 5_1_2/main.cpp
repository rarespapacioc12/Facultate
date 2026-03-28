#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

std::ifstream fin("strabunica.in");
std::ofstream fout("strabunica.out");

int N;
long long sol;
std::vector<int> v, nextS, prevS;
std::stack<int> S;

int main(){
    fin >> N;

    v.resize(N);
    nextS.resize(N, N);
    prevS.resize(N, -1);
    
    for(int& x : v)
        fin >> x;
    
    for(int i = 0; i < N; ++i){
        while(!S.empty() && v[i] < v[S.top()]){
            nextS[S.top()] = i;
            S.pop();
        }
        S.push(i);
    }

    for(;!S.empty();S.pop());

    for(int i = N - 1; i >= 0; --i){
        while(!S.empty() && v[i] < v[S.top()]){
            prevS[S.top()] = i;
            S.pop();
        }
        S.push(i);
    }

    for(int i = 0; i < N; ++i){
        sol = std::max(sol, 1ll * v[i] * (nextS[i] - prevS[i] - 1));
    }

    fout << sol;
}