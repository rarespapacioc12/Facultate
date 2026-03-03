// 10% din nota finala - tema/teme + activitate

// Complexitate + sortari + extra

// Def: f apartine O(g) daca exista c si n_0 > 0 a.i. f(n) <= c*g(n) cu n >= n_0
// Omega - >=
// Theta - =
// o - <
// omega mic - >

// 1) 100n apartine O(n)
// 2) 2^(n+1) apartine O(2^n)
// 3) 2^(2n) nu apartine O(2^n)
// 4) n apartine O(nlogn)
// 5) n apartine o(n^2)
// 6) 100n nu apartine o(1000n)

// Sortari
// 1) Insertion Sort - O(n^2) timp si O(n) memorie
// 2) Selection Sort - O(n^2) timp si O(n) memorie
// 3) Bubble Sort - O(n^2) timp si O(n) memorie
// 4) Bogo Sort - O(n!) timp si O(n) memorie
// 5) Counting Sort - O(n + VMAX) timp si O(n + VMAX) memorie
// 6) Merge Sort - O(nlogn) si O(n) memorie
// 7) Radix Sort - O(nlogn)
// 8) Quick Sort - O(nlogn) average O(n^2) average
// 9) TimSort - O(nlogn)

// 1. N numere sortate, S o suma. Cate perechi (i, j) a.i. V[i] + V[j] == S

// #include <iostream>
// #include <algorithm>
// #include <vector>

// int N, S, cnt;
// std::vector<int> v;

// int main(){
//     std::cin >> N >> S;
//     v.resize(N);

//     for(int& x : v)
//         std::cin >> x;

//     int i = 0, j = N - 1;
//     while(i <= j){
//         if(v[i] + v[j] == S){
//             int val1 = v[i], val2 = v[j], cnt1 = 0, cnt2 = 0;
            
//             if(val1 == val2){
//                 int n = j - i + 1;
//                 cnt += n * (n - 1) / 2;
//                 break;
//             }
            
//             while(i <= j && v[i] == val1){
//                 ++cnt1;
//                 ++i;
//             }
//             while(i <= j && v[j] == val2){
//                 ++cnt2;
//                 --j;
//             }
//             cnt += cnt1 * cnt2;
//         }
//         else if(v[i] + v[j] < S)
//             ++i;
//         else
//             --j;
//     }
//     std::cout << cnt;
// }

// 2. Se dau N cuvinte. Cate perechi de anagrame sunt

// #include <iostream>
// #include <unordered_map>
// #include <string>
// #include <vector>

// int N;
// long long cnt;
// std::unordered_map<int, int> mp;

// int main(){
//     std::cin >> N;

//     for(std::string s; N--;){
//         std::cin >> s;
//         int mask = 0;
//         for(int i = 0; s[i] != 0; ++i)
//             mask |= (1 << (s[i] - 'a'));
//         ++mp[mask];
//     }

//     for(auto [x, y] : mp)
//         cnt += 1ll * y * (y - 1) / 2;
    
//     std::cout << cnt;
// }

// 3. Se da un vector cu N elemente care a fost sortat si apoi rotit circular. Gasiti valoarea 
// Idee: cautare binara cu pas
// if(pos + (1 << i) <= N and v[pos + (1 << i)] <= v[pos + (1 << i) + 1] and v[pos + (1 << i)] >= v[1])
//   pos = pos + (1 << i)

// #include <iostream>
// #include <vector>

// int N;
// std::vector<int> v;

// int main(){
//     std::cin >> N;

//     v.resize(N + 1);

//     for(int i = 1; i <= N; ++i)
//         std::cin >> v[i];

//     int pos = 1;
//     for(int i = 30; i >= 0; --i){
//         if(pos + (1 << i) <= N and v[pos + (1 << i)] <= v[pos + (1 << i) + 1] and v[pos + (1 << i)] >= v[1])
//             pos |= (1 << i);
//     }
//     std::cout << v[pos + 1];
// }

// 4. Se da o permutare. Fie i < j si pi > pj. Cate perechi i si j sunt?
// Idee: se foloseste merge sort.

// #include <iostream>
// #include <vector>

// const int MAX = 1e5;

// int n, v[MAX], a[MAX], b[MAX];
// long long cnt;

// void merge_sides(int l, int m, int r){
//     int i = l, j = m + 1, t = 0, u = 0, poz = l;

//     while(i <= m){
//         a[t++] = v[i++];
//     }

//     while(j <= r){
//         b[u++] = v[j++];
//     }

//     i = j = 0;
//     while(i < t and j < u){
//         if(a[i] < b[j]){
//             cnt += j;
//             v[poz++] = a[i++];
//         }
//         else{
//             v[poz++] = b[j++];
//         }
//     }

//     while(i < t){
//         v[poz++] = a[i++];
//         cnt += j;
//     }
    
//     while(j < u)
//         v[poz++] = b[j++];
// }

// void merge_sort(int left, int right){
//     if(right <= left)
//         return;

//     int m = (left + right) >> 1;
//     merge_sort(left, m);
//     merge_sort(m + 1, right);
//     merge_sides(left, m, right);
// }

// int main(){
//     std::cin >> n;

//     for(int i = 0; i < n; ++i)
//         std::cin >> v[i];

//     merge_sort(0, n - 1);

//     std::cout << cnt;
// }

// 5. Aranjare - ONI 2018
// N elemente pe o stiva
// M stive suplimentare
// K operatii
// Alege M si da K operatii a.i. sa sortezi cele N elemente
// M*K determina punctajul

// #include <bits/stdc++.h>
// using namespace std;

// ifstream fin("aranjare.in");
// ofstream fout("aranjare.out");

// int n, m, k, nrop;
// vector<int> v, v1, v2;
// vector<pair<int, int> > pasi;

// int main()
// {
//     fin >> n;

//     v.resize(n);
//     for(int& x : v)
//         fin >> x;

//     for(int bit = 0; bit < 15; ++bit){
//         while(!v.empty()){
//             int t = v.back();
//             v.pop_back();
//             if(t & (1 << bit)){
//                 v2.push_back(t);
//                 pasi.push_back({0, 2});
//             }
//             else{
//                 v1.push_back(t);
//                 pasi.push_back({0, 1});
//             }
//         }
//         while(!v1.empty()){
//             int t = v1.back();
//             v1.pop_back();
//             v.push_back(t);
//             pasi.push_back({1, 0});
//         }
//         while(!v2.empty()){
//             int t = v2.back();
//             v2.pop_back();
//             v.push_back(t);
//             pasi.push_back({2, 0});
//         }
//     }

//     fout << 2 << ' ' << pasi.size() << '\n';

//     for(auto [x, y] : pasi)
//         fout << x << ' ' << y << '\n';
// }

// 6. Farfurii - lot 2024 - https://kilonova.ro/problems/2838
// Idee - le sortez unde prind si dupa fac hanoi

// GETS TLE
// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <set>

// #define pii std::pair<int, int>
// const std::set<int> colset = {1, 2, 3};

// std::ifstream fin("farfurii.in");
// std::ofstream fout("farfurii.out");

// int cfinal;
// std::vector<int> C[4];

// pii find_max(){
//     int pmax = 0;
//     for(int i = 1; i <= 3; ++i)
//         if(pmax == 0 || C[i].empty() || (!C[pmax].empty() && C[i].back() > C[pmax].back())){
//             pmax = i;
//             if(C[i].empty()) break;
//         }

//     int p2 = 0;
//     for(int i = 1; i <= 3; ++i)
//         if(i != pmax && !C[i].empty() && (p2 == 0 || C[p2].back() < C[i].back()))
//             p2 = i;

//     return {pmax, p2};
// }

// bool sortat(const std::vector<int>& v){
//     for(int i = 0; i + 1 < (int)v.size(); ++i)
//         if(v[i] < v[i + 1])
//             return false;
//     return true;
// }

// void muta(int a, int b){
//     fout << a << ' ' << b << '\n';
//     C[b].push_back(C[a].back());
//     C[a].pop_back();
// }

// void hanoi(int k, int a, int b, int aux){
//     if(k <= 0) return;
//     hanoi(k - 1, a, aux, b);
//     muta(a, b);
//     hanoi(k - 1, aux, b, a);
// }

// int cnt_top_leq(int d, int val){
//     int k = 0;
//     for(int i = (int)C[d].size() - 1; i >= 0; --i){
//         if(C[d][i] <= val) ++k;
//         else break;
//     }
//     return k;
// }

// void uneste(int c1, int c2, int e){
//     int d = cfinal;
//     if(d != c1 && d != c2) d = c1;
//     int s = (d == c1 ? c2 : c1);

//     while(!C[s].empty()){
//         int p = C[s].back();
//         int k = cnt_top_leq(d, p);
//         hanoi(k, d, e, s);
//         muta(s, d);
//         hanoi(k, e, d, s);
//     }

//     if(d != cfinal){
//         int aux = 6 - d - cfinal;
//         hanoi((int)C[d].size(), d, cfinal, aux);
//     }
// }

// int main(){
//     for(int i = 1; i <= 3; ++i){
//         int nr; fin >> nr;
//         for(int x; nr--;){
//             fin >> x;
//             C[i].push_back(x);
//         }
//     }
//     fin >> cfinal;

//     int x = 0, y = 0;
//     while(true){
//         auto p = find_max();
//         x = p.first;
//         y = p.second;

//         if(C[x].empty()){
//             std::set<int> S = colset;
//             S.erase(x);
//             bool ok = true;
//             for(int el : S)
//                 if(!sortat(C[el]))
//                     ok = false;
//             if(ok){
//                 int a = *S.begin();
//                 int b = *std::next(S.begin());
//                 uneste(a, b, x);
//                 break;
//             }
//         }

//         muta(y, x);
//     }
//     fout << "0 0\n";
// }