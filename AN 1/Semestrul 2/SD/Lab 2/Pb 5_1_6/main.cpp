// Deci cum am zis si la laborator ideea mea e sa simulez un deque cu 2 stive
// Problema de care ma lovesc este urmatoarea. Pentru problema clasica de deque, am o ordine a elementelor.
// Pentru operatii aritmetice, ordinea nu e neaparat relevanta si se rezuma doar la a scoate din deque pozitiile care nu mai sunt valide pentru
// subsecventa mea.
// La minim si maxim, pot sa imi definesc o ordine relativa bazata pe operatii
// La xor, pot sa merg pe principiul de la operatii aritmetice inverse
// Problema mea vine la operatiile de AND si OR care, desi sunt asociative, nu au invers si nu inteleg cum pot sa le stabilesc o ordine

// Dupa multe lupte, mi-a venit o alta idee. Ma folosesc de stive de perechi ca sa tin sume (folosit ca nume simbolic pentru compuneri)
// de prefixe si de sufixe si le compun ca sa imi obtin rezultatul
// Pentru solutia asta, aparent e nevoie de element neutru, cum e mentionat si in enunt

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

typedef std::pair<int, int> pii;
const int e = 0;

std::ifstream fin("input.txt");

int n, k;
std::vector<int> v;

int f(int a, int b){
    return a | b;
}

std::stack<pii> in, out;

int main(){
    fin >> n >> k;

    v.resize(n);
    for(int& x : v)
        fin >> x;

    for(int i = 0; i < k; ++i){
        int new_prefix = (in.empty() ? v[i] : f(in.top().second, v[i]));
        in.push({v[i], new_prefix});
    }

    for(int i = k; i < n; ++i){
        int res = f((out.empty() ? e : out.top().second), (in.empty() ? e : in.top().second));
        std::cout << res << ' ';

        if(out.empty()){
            while(!in.empty()){
                int x = in.top().first;
                in.pop();
                
                if(out.empty()){
                    out.push({x, x});
                }
                else{
                    out.push({x, f(x, out.top().second)});
                }
            }
        }
        out.pop();
        if(in.empty()){
            in.push({v[i], v[i]});
        }
        else{
            in.push({v[i], f(in.top().second, v[i])});
        }
    }
    int res = f((out.empty() ? e : out.top().second), (in.empty() ? e : in.top().second));
    std::cout << res << ' ';
}