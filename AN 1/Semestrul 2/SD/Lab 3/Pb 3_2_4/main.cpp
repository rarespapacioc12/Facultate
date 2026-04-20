/* Statement:
You are given an array a of n integers. Answer q queries of the form (l, r): is
a[l . . . r] a permutation of {0, 1, . . . , r−l}? Aim for an O(n+q) time complexity
algorithm.
*/

/* Idea:
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

/* O(n + q) solution, discussed in lab
fie b_i = h(a_i)
functia h alege un random din [0, 10^18]
s = xor de la i = l pana la r din b_i
s2 = xor de la i = 0 pana la r - l din h(i)
daca s = s2:
    da
altfel:
    nu
*/

#include <fstream>
#include <vector>
#include <random>
#include <unordered_map>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const int64_t talent = 1e18;

std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<int64_t> numar(0, talent);

int n, q;
std::vector<int64_t> v;
std::unordered_map<int64_t, int64_t> H;
std::vector<int64_t> prefix_sum_v, prefix_sum_interval;

int main(){
    fin >> n >> q;

    v.resize(n);
    prefix_sum_v.resize(n);
    prefix_sum_interval.resize(n);

    for(auto& x : v){
        fin >> x;
    }

    for(int64_t i = 0; i < n; ++i){
        if(H.find(i) == H.end()){
            H[i] = numar(gen);
        }
        if(H.find(v[i]) == H.end()){
            H[v[i]] = numar(gen);
        }
        if(i == 0){
            prefix_sum_v[i] = H[v[i]];
            prefix_sum_interval[i] = H[i];
        }
        else{
            prefix_sum_v[i] = prefix_sum_v[i - 1] ^ H[v[i]];
            prefix_sum_interval[i] = prefix_sum_interval[i - 1] ^ H[i];
        }
    }

    for(int l, r; q--;){
        fin >> l >> r;
        fout << (prefix_sum_interval[r - l] == (prefix_sum_v[r] ^ (l == 0 ? 0 : prefix_sum_v[l - 1]))) << '\n';
    }
}