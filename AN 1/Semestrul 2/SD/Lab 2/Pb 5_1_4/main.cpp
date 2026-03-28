// Solutie O(n^2)

// #include <iostream>
// #include <fstream>
// #include <vector>

// // Simulez relatia in O(1) cu matrice de adiacenta
// std::ifstream fin("input.txt");

// int n;
// std::vector<std::vector<bool> > mat;

// int main(){
//     fin >> n;

//     mat = std::vector<std::vector<bool> >(n, std::vector<bool>(n));

//     for(int i = 0; i < n; ++i){
//         for(int x, j = 0; j < n; ++j){
//             fin >> x;
//             mat[i][j] = x;
//         }
//     }

//     for(int i = 0; i < n; ++i){
//         int cntLine = 0, cntCol = 0;
//         for(int j = 0; j < n; ++j){
//             if(mat[i][j])
//                 cntLine++;
//             if(mat[j][i])
//                 cntCol++;
//         }
//         if(cntLine == 1 && cntCol == n){
//             std::cout << i;
//             return 0;
//         }
//     }
//     std::cout << -1; // No celebrity was found;
// }


// Solutie O(n) fara stiva
// #include <iostream>
// #include <fstream>
// #include <vector>

// // Simulez relatia in O(1) cu matrice de adiacenta
// std::ifstream fin("input.txt");

// int n;
// std::vector<std::vector<bool> > mat;

// int main(){
//     fin >> n;

//     mat = std::vector<std::vector<bool> >(n, std::vector<bool>(n));

//     for(int i = 0; i < n; ++i){
//         for(int x, j = 0; j < n; ++j){
//             fin >> x;
//             mat[i][j] = x;
//         }
//     }

//     int sol = 0;
//     for(int i = 1; i < n; ++i){
//         if(mat[sol][i]){
//             sol = i;
//         }
//     }
        
//     for(int i = 0; i < n; ++i){
//         if(i == sol){
//             continue;
//         }
//         if(mat[sol][i] || !mat[i][sol]){
//             std::cout << -1;
//             return 0;
//         }
//     }
//     std::cout << sol;
// }

// Solutie O(n) cu stiva
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

ifstream fin("input.txt");

int n;
vector<vector<bool> > mat;
stack<int> S;

int main(){
    fin >> n;

    mat = std::vector<std::vector<bool> >(n, std::vector<bool>(n));

    for(int i = 0; i < n; ++i){
        for(int x, j = 0; j < n; ++j){
            fin >> x;
            mat[i][j] = x;
        }
    }

    for(int i = 0; i < n; ++i){
        S.push(i);
    }

    while(S.size() != 1){
        int a = S.top();
        S.pop();
        int b = S.top();
        S.pop();
        if(mat[a][b]){
            S.push(b);
        }
        else{
            S.push(a);
        }
    }

    int cand = S.top();
    for(int i = 0; i < n; ++i){
        if(i == cand){
            continue;
        }
        if(mat[cand][i] || !mat[i][cand]){
            cout << -1;
            return 0;
        }
    }
    cout << cand;
}