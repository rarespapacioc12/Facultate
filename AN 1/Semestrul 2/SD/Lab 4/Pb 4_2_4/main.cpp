// Idea: at each step it is optimal to remove the shortest 2 sticks and merge them together
// For a O(nlogn) solution I can do that with a multiset

// #include <iostream>
// #include <set>

// int N, cost;
// std::multiset<int> ms;

// int main(){
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     std::cin >> N;

//     for(int x; N--;){
//         std::cin >> x;
//         ms.insert(x);
//     }

//     while(ms.size() > 1){
//         int a = *ms.begin();
//         ms.erase(ms.begin());
//         int b = *ms.begin();
//         ms.erase(ms.begin());
//         cost += a + b;
//         ms.insert(a + b);
//     }
    
//     std::cout << cost;
// }

// Fac o schema cu doua cozi si counting sort
// Practic cu counting sort imi pun elementele in q1 sortate
// La fiecare pas, extrag cele mai mici 2 elemente din q1 reunit cu q2
// Adaug suma in q2 si dat fiind ca suma de la pasul i + 1 > suma de la pasul i
// in q2 o sa am elementele tot sortate
// Complexitatea devine O(n + V), unde V = 1000 deci cand n->inf complexitatea tinde la O(n)

#include <iostream>
#include <queue>

int N, cost;
int fr[1001];
std::queue<int> q1, q2;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    for(int x; N--;){
        std::cin >> x;
        ++fr[x];
    }

    for(int i = 0; i <= 1000; ++i){
        for(;fr[i]--;){
            q1.push(i);
        }
    }

    while(q1.size() + q2.size() > 1){
        int a, b;
        if(q2.empty()){
            a = q1.front();
            q1.pop();
        }
        else if(q1.empty()){
            a = q2.front();
            q2.pop();
        }
        else{
            if(q1.front() < q2.front()){
                a = q1.front();
                q1.pop();
            }
            else{
                a = q2.front();
                q2.pop();
            }
        }

        if(q2.empty()){
            b = q1.front();
            q1.pop();
        }
        else if(q1.empty()){
            b = q2.front();
            q2.pop();
        }
        else{
            if(q1.front() < q2.front()){
                b = q1.front();
                q1.pop();
            }
            else{
                b = q2.front();
                q2.pop();
            }
        }
        cost += a + b;
        q2.push(a + b);
    }
    std::cout << cost;
}