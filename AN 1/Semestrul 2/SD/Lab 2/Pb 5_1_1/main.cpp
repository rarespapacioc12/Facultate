// solutie  - https://cses.fi/problemset/result/16520366/

#include <iostream>
#include <vector>
#include <stack>

int N;
std::vector<int> v, sol;
std::stack<int> S;

int main(){
    std::cin >> N;

    v.resize(N + 1);
    sol.resize(N + 1);
    for(int i = 1; i <= N; ++i)
        std::cin >> v[i];

    for(int i = N; i >= 1; --i){
        while(!S.empty() and v[i] < v[S.top()]){
            sol[S.top()] = i;
            S.pop();
        }
        S.push(i);
    }

    for(int i = 1; i <= N; ++i)
        std::cout << sol[i] << ' ';
}

