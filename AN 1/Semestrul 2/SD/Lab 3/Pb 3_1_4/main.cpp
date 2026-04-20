/* Statement:
Implement a data structure with linear memory that supports:
• init x0, x1, . . . , xn−1 — O(n log2 n) expected time.
• exists x — O(1) worst-case time.
This is known as perfect hashing. A fully rigorous proof of the time complexity
is not required, but you should provide a short explanation of why each
step of your solution satisfies the claimed bounds.
*/

// In this implementation I used the idea from:
// https://www.cs.cmu.edu/~avrim/451f11/lectures/lect1004.pdf
/* Idea:
I'll use the following formula: h(x) = ((a * x + b) % p) % m
where a and b are chosen randomly until:
- the sum of the squares of all buckets (positions with collissions) <= 3 * N (for the first step)
- there are no collissions in any bucket (for the second step)

I am assuming positive integers. Otherwise I'll need to add the absolute value of the smallest number
in order to normalize them to positive integers
*/

#include <fstream>
#include <vector>
#include <random>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const int p = 1e9 + 7;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> a_gen(1, p - 1);
std::uniform_int_distribution<> b_gen(0, p - 1);

struct Bucket{
    int a;
    int b;
    int m;
    std::vector<int> elems;

    Bucket() : a(1), b(1), m(1), elems({}) {}
};

class HashTable{
private:
    int size;
    int A, B;
    std::vector<Bucket> H;

    int hash(int x, int a, int b, int m){
        return ((1ll * a * x + b) % p) % m;
    }

public:
    HashTable() = default;

    HashTable(std::vector<int>& v) : size(v.size()) {
        int n = v.size();
        H.resize(n);
        bool ok;
        do{
            ok = true;
            A = a_gen(gen);
            B = b_gen(gen);
            for(int i = 0; i < n; ++i){
                H[i].elems.clear();
            }
            for(int x : v){
                H[hash(x, A, B, size)].elems.push_back(x);
            }
            long long sum = 0;
            for(int i = 0; i < n; ++i){
                sum += 1ll * H[i].elems.size() * H[i].elems.size();
            }
            if(sum >= 3ll * n){
                ok = false;
            }
        }while(!ok);

        for(int i = 0; i < size; ++i){
            if(H[i].elems.size() > 0){
                int k = H[i].elems.size(), m = k * k;
                std::vector<int> newElems;
                bool ok;
                int a, b;
                do{
                    ok = true;
                    a = a_gen(gen);
                    b = b_gen(gen);
                    newElems = std::vector<int>(m, -1);
                    for(int x : H[i].elems){
                        int h = hash(x, a, b, m);
                        if(newElems[h] != -1){
                            ok = false;
                            break;
                        }
                        newElems[h] = x;
                    }
                }while(!ok);
                H[i].a = a;
                H[i].b = b;
                H[i].m = m;
                H[i].elems = newElems;
            }
        }
    }

    bool exists(int x){
        int bucket = hash(x, A, B, size);

        if(H[bucket].elems.empty()){
            return false;
        }

        int index = hash(x, H[bucket].a, H[bucket].b, H[bucket].m);
        return H[bucket].elems[index] == x;
    }
};

int n, q;
std::vector<int> v;

int main(){
    fin >> n >> q;

    v.resize(n);
    for(int& x : v){
        fin >> x;
    }

    HashTable hashTable(v);

    for(int x;q--;){
        fin >> x;
        fout << hashTable.exists(x) << '\n';
    }
}