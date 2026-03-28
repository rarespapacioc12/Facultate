// Observatie: lungimea stringului solutie va fi suma paritatilor aparitiilor fiecarui caracter in stringul initial

// Nu am gasit solutie de O(n) cu stiva, dar asta e O(n * sigma + sigma^3) ceea ce effectively e O(n * sigma)

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <algorithm>

// std::ifstream fin("input.txt");

// std::string s;
// std::vector<std::vector<int> > next;
// bool parity[256];

// int main(){
//     fin >> s;

//     int len = s.length();

//     for(int i = 0; i < len; ++i){
//         parity[s[i]] = (parity[s[i]] != 1);
//     }
//     next = std::vector<std::vector<int> > (len + 1, std::vector<int>(256, -1));
//     for(int i = len - 1; i >= 0; --i){
//         for(int j = 0; j < 256; ++j){
//             if(s[i] == j){
//                 next[i][j] = i;
//             }
//             else{
//                 next[i][j] = next[i + 1][j];
//             }
//         }
//     }
//     int sol_len = 0;
//     for(int i = 0; i < 256; ++i){
//         if(parity[i]){
//             ++sol_len;
//         }
//     }
//     std::string ans;
//     int i = 0;

//     while(sol_len > 0){
//         for(int c = 0; c < 256; ++c){
//             if(!parity[c]){
//                 continue;
//             }

//             int p = (i <= len ? next[i][c] : -1);
//             if(p == -1){
//                 continue;
//             }

//             bool ok = true;
//             for(int d = 0; d < 256; ++d){
//                 if(!parity[d] || d == c){
//                     continue;
//                 }
//                 if(p + 1 > len || next[p + 1][d] == -1){
//                     ok = false;
//                     break;
//                 }
//             }
//             if(ok){
//                 ans.push_back((char)c);
//                 parity[c] = 0;
//                 --sol_len;
//                 i = p + 1;
//                 break;
//             }
//         }
//     }
//     std::cout << ans << '\n';
// }

// Scriu asta dupa ce am bagat solutia. Vreau sa ii multumesc colegului meu Antonie-Gabriel Belu ca a venit cu o idee cu monotonic stack
// la o problema asemanatoare la seminar si mi-a venit ideea si cum sa bag monotonic stack la problema asta

// Idee. Fie n = len(s) si n1 = len(solutie). Aplic monotonic stack tinand in stiva o solutie optima, folosindu-ma de faptul ca am maxim n - n1
// operatii de pop la dispozitie si tinand cont ce litere am voie sa am in solutie
// Complexitate - O(n + sigma) ~ O(n)

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <algorithm>

std::ifstream fin("input.txt");

std::string s;
bool parity[256], in_stack[256];
int freq[256];

int main(){
    fin >> s;

    int n = s.length();

    for(int i = 0; i < n; ++i){
        ++freq[s[i]];
    }
    
    int n1 = 0;

    for(int i = 0; i < 256; ++i){
        parity[i] = (freq[i] % 2 == 1);
        n1 += parity[i];
    }

    std::stack<int> S;

    for(int i = 0; i < n; ++i){
        char c = s[i];
        --freq[c];

        if(!parity[c]){
            continue;
        }

        if(in_stack[c]){
            continue;
        }

        while(!S.empty() && c < s[S.top()] && freq[s[S.top()]] > 0){
            in_stack[s[S.top()]] = false;
            S.pop();
        }

        S.push(i);
        in_stack[c] = true;
    }

    std::string ans;

    for(; !S.empty(); S.pop()){
        ans.push_back(s[S.top()]);
    }

    std::reverse(ans.begin(), ans.end());

    std::cout << ans << '\n';
}