// Hashuri
// The dictionary problem
// insert(x)
// erase(x)
// exists(x)

// Hash function
// g:U -> H
// g(x) = y
// Am y, nu pot sti nimic despre x
// - g(x) = y mereu
// - x e mare, y e mic

// x apartine U
// Presupunem ca |U| <= 1000
// O solutie este sa folosim vectori de frecventa
// O(1) timp/op si O(|U|) spatiu
// #include <iostream>

// const int MAX = 1000;
// int H[MAX];

// void insert(int x){
//     H[x] = 1;
// }

// void erase(int x){
//     H[x] = 0;
// }

// bool exists(int x){
//     return H[x];
// }

// |U| >> 1000
// g:U -> H
// O(1) timp si O(|H|) spatiu

// insert: t[g(x)] = 1;
// erase: t[g(x)] = 0;
// exists: return t[g(x)];
// apar coliziuni

// insert: t[g(x)] e un vector
//         t[g(x)].push_back(x);
// query: for(auto val : t[g(x)]) if(val == x) return true;
// return false;
// erase: Delete x from t[g(x)]

// Spatiu - O(|H| + n), cu n = nr de inserturi
// Timp - O(n)
// Functia hash ar fi bine sa fie secreta
// Functia hash ar trebui sa imparta U in mod uniform

// g(x) = sin(x) - uniforma, dar nu e hash bun
// h(x) = abcd... barat - uniforma, dar nu e hash bun
// f(x) = floor(sinh(x) * k)
// g'(x) = x mod |H| - uniforma, ok
// f'(x) = x AND 2^P, unde |H| = 2^P - 1 - uniforma, ok 