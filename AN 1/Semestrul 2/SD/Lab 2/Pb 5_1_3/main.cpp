// https://kilonova.ro/problems/891
// Idee - pentru fiecare pozitie calculez
// sus[i][j] = pozitia maxima in care pot sa ma duc din (i, j) in sus astfel incat sa se pastreze regula de sah
// dupa aplic histograme pe fiecare linie cu restrictia ca imi actualizez prev si next si daca gasesc un element care nu respecta sah

// Adaug acest comentariu dupa ce mi-a iesit problema. M-a batut rau logica si ordinea de executie a unui if
// https://kilonova.ro/submissions/1053316
// https://www.infoarena.ro/job_detail/3347689

#include <fstream>
#include <vector>
#include <stack>

std::ifstream fin("fadema.in");
std::ofstream fout("fadema.out");

int n, m, global_max;
std::vector<std::vector<int> > A, sus;

int main(){
    fin >> n >> m;

    A = std::vector<std::vector<int> >(n, std::vector<int>(m));
    sus = std::vector<std::vector<int> >(n, std::vector<int>(m, n));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            fin >> A[i][j];
        }
    }

    for(int j = 0; j < m; ++j){
        std::stack<int> S;
        S.push(0);

        for(int i = 1; i < n; ++i){
            if(A[S.top()][j] != A[i][j]){
                S.push(i);
            }
            else{
                while(!S.empty()){
                    sus[S.top()][j] = i;
                    S.pop();
                }
                S.push(i);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        std::vector<int> prev(m, -1), next(m, m);
        std::stack<int> S;
        S.push(0);
        for(int j = 1; j < m; ++j){
            if(A[i][j] == A[i][S.top()]){
                while(!S.empty()){
                    next[S.top()] = j;
                    S.pop();
                }
            }
            else if(sus[i][j] < sus[i][S.top()]){
                while(!S.empty() && sus[i][j] < sus[i][S.top()]){
                    next[S.top()] = j;
                    S.pop();
                }
            }
            S.push(j);
        }
        
        for(;!S.empty();S.pop());

        S.push(m - 1);
        for(int j = m - 2; j >= 0; --j){
            if(A[i][j] == A[i][S.top()]){
                while(!S.empty()){
                    prev[S.top()] = j;
                    S.pop();
                }
            }
            else if(sus[i][j] < sus[i][S.top()]){
                while(!S.empty() && sus[i][j] < sus[i][S.top()]){
                    prev[S.top()] = j;
                    S.pop();
                }
            }
            S.push(j);
        }

        int local_max = 0;

        for(int j = 0; j < m; ++j){
            local_max = std::max(local_max, (sus[i][j] - i) * (next[j] - prev[j] - 1));
        }
        global_max = std::max(global_max, local_max);
    }
    fout << global_max;
}