/* Statement:
You are given an array a of n integers. Answer q queries of the form (l, r): is
a[l . . . r] a permutation of {0, 1, . . . , r−l}? Aim for an O(n+q) time complexity
algorithm.
*/

/* Idea:
Generalizing the idea from Problem 3.2.2, I want to do the following check:
- check that there are exactly r - l + 1 distinct values in interval [l...r]
- check that the interval has the number 0 in it and the maximum is r - l
However, this solution has a complexity of O(nlogn + q) because I am forced to use a RMQ
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <unordered_map>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

int n, q;
std::vector<int> v, E, prev, max_prev, has_zero;
std::vector<std::vector<int> > RMQ;
std::unordered_map<int, int> last; //last[i] = last occurance of i

void compute_max_prev(){
    prev.resize(n, -1);
    max_prev.resize(n, -1);

    last[v[0]] = 0;

    for(int i = 1; i < n; ++i){
        if(last.find(v[i]) != last.end()){
            prev[i] = last[v[i]];
        }
        max_prev[i] = std::max(max_prev[i - 1], prev[i]);
        last[v[i]] = i;
    }
}

void build_rmq(){
    E.resize(n + 1, 0);
    RMQ.resize(std::ceil(std::log2(n) + 1), std::vector<int>(n, -1e9));

    for(int i = 2; i <= n; ++i){
        E[i] = E[i >> 1] + 1;
    }

    RMQ[0] = v;

    for(int i = 1; (1 << i) <= n; ++i){
        for(int j = 0; j < n; ++j){
            RMQ[i][j] = RMQ[i - 1][j];
            int t = j + (1 << (i - 1));
            if(t < n && RMQ[i - 1][t] > RMQ[i][j]){
                RMQ[i][j] = RMQ[i - 1][t];
            }
        }
    }
}

int max_query(int l, int r){
    int len = r - l + 1, e = E[len];
    return std::max(RMQ[e][l], RMQ[e][r - (1 << e) + 1]);
}

int main(){
    fin >> n >> q;

    v.resize(n);
    has_zero.resize(n);
    for(int& x : v){
        fin >> x;
    }

    has_zero[0] = (v[0] == 0);
    for(int i = 1; i < n; ++i){
        has_zero[i] = has_zero[i - 1] + (v[i] == 0);
    }

    compute_max_prev();
    build_rmq();

    for(int l, r;q--;){
        fin >> l >> r;
        fout << (max_query(l, r) == r - l && 
        (has_zero[r] - (l == 0 ? 0 : has_zero[l - 1]) == 1) &&
        max_prev[r] < l) << '\n';
    }
}