// Fara coada - O(m * n)

// #include <iostream>
// #include <queue>
// #include <vector>
// #include <string>

// int A, B, C;
// std::vector<std::string> steps1, steps2;

// int main(){
//     std::cin >> A >> B >> C;

    
//     int v1 = 0, v2 = 0;
//     while(v1 != C && v2 != C){
//         if(v2 == 0){
//             v2 = B;
//             steps1.push_back("R B");
//         }
//         else if(v1 == A){
//             v1 = 0;
//             steps1.push_back("A C");
//         }
//         else{
//             int poured = std::min(v2, A - v1);
//             v2 -= poured;
//             v1 += poured;
//             steps1.push_back("B A");
//         }
//     }
//     v1 = 0, v2 = 0;
//     while(v1 != C && v2 != C){
//         if(v1 == 0){
//             v1 = A;
//             steps2.push_back("R A");
//         }
//         else if(v2 == B){
//             v2 = 0;
//             steps2.push_back("B C");
//         }
//         else{
//             int poured = std::min(v1, B - v2);
//             v1 -= poured;
//             v2 += poured;
//             steps2.push_back("A B");
//         }
//     }

//     if(steps1.size() < steps2.size()){
//         std::cout << steps1.size() << '\n';
//         for(std::string s : steps1){
//             std::cout << s << '\n';
//         }
//     }
//     else{
//         std::cout << steps2.size() << '\n';
//         for(std::string s : steps2){
//             std::cout << s << '\n';
//         }
//     }
// }

// Solutie cu coada (considerabil mai lunga =(( )
#include <iostream>
#include <queue>
#include <vector>
#include <string>

#define pii std::pair<int, int>
const pii ZERO = {0, 0};
int A, B, C;
std::vector<std::vector<int> > viz;
std::vector<std::vector<pii> > back;
std::vector<std::vector<std::string> > pas;

void print_sol(pii u){
    if(u == ZERO)
        return;
    print_sol(back[u.first][u.second]);
    std::cout << pas[u.first][u.second] << '\n';
}

int main(){
    std::cin >> A >> B >> C;

    viz.resize(A + 1, std::vector<int>(B + 1, 0));
    back.resize(A + 1, std::vector<pii>(B + 1, {-1, -1}));
    pas.resize(A + 1, std::vector<std::string>(B + 1, ""));

    viz[0][0] = true;
    std::queue<pii> q;
    q.push({0, 0});
    pii sol = {-1, -1};
    while(!q.empty()){
        pii t = q.front();
        q.pop();
        if(t.first == C || t.second == C){
            sol = t;
            break;
        }

        if(t.first == 0){
            pii p = {A, t.second};
            if(!viz[p.first][p.second]){
                viz[p.first][p.second] = viz[t.first][t.second] + 1;
                back[p.first][p.second] = t;
                pas[p.first][p.second] = "R A";
                q.push(p);
            }
        }
        if(t.second == 0){
            pii p = {t.first, B};
            if(!viz[p.first][p.second]){
                viz[p.first][p.second] = viz[t.first][t.second] + 1;
                back[p.first][p.second] = t;
                pas[p.first][p.second] = "R B";
                q.push(p);
            }
        }
        if(t.first + t.second <= A){
            pii p = {t.first + t.second, 0};
            if(!viz[p.first][p.second]){
                viz[p.first][p.second] = viz[t.first][t.second] + 1;
                back[p.first][p.second] = t;
                pas[p.first][p.second] = "B A";
                q.push(p);
            }
        }
        if(t.first + t.second <= B){
            pii p = {0, t.first + t.second};
            if(!viz[p.first][p.second]){
                viz[p.first][p.second] = viz[t.first][t.second] + 1;
                back[p.first][p.second] = t;
                pas[p.first][p.second] = "A B";
                q.push(p);
            }
        }
        pii p = {t.first, 0};
        if(!viz[p.first][p.second]){
            viz[p.first][p.second] = viz[t.first][t.second] + 1;
            back[p.first][p.second] = t;
            pas[p.first][p.second] = "B C";
            q.push(p);
        }
        p = {0, t.second};
        if(!viz[p.first][p.second]){
            viz[p.first][p.second] = viz[t.first][t.second] + 1;
            back[p.first][p.second] = t;
            pas[p.first][p.second] = "A C";
            q.push(p);
        }
        if(t.first < A){
            int dif = A - t.first;
            dif = std::min(t.second, dif);
            p = {t.first + dif, t.second - dif};
            if(!viz[p.first][p.second]){
                viz[p.first][p.second] = viz[t.first][t.second] + 1;
                back[p.first][p.second] = t;
                pas[p.first][p.second] = "B A";
                q.push(p);
            }
        }
        if(t.second < B){
            int dif = B - t.second;
            dif = std::min(t.first, dif);
            p = {t.first - dif, t.second + dif};
            if(!viz[p.first][p.second]){
                viz[p.first][p.second] = viz[t.first][t.second] + 1;
                back[p.first][p.second] = t;
                pas[p.first][p.second] = "A B";
                q.push(p);
            }
        }
    }
    std::cout << viz[sol.first][sol.second] - 1<< '\n';
    print_sol(sol);
}