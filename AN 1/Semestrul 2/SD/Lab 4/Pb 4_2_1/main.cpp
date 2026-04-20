// Implementation for max-heap, min-heap is symetric
// For testing I'll use the following problem: 
// https://www.pbinfo.ro/probleme/1855/heap
// (This source scored 100)

#include <fstream>
#include <stdexcept>

class Heap{
private:
    int dim;
    int v[250005];
public:
    Heap() : dim(0) {}
    Heap(int x) : dim(1) { v[1] = x; }

    void insert(int x){
        v[++dim] = x;
        int t = dim;
        while(t != 1 && v[t] > v[t >> 1]){
            std::swap(v[t], v[t >> 1]);
            t >>= 1;
        }
    }

    int top(){
        return v[1];
    }

    void pop(){
        if(dim == 0){
            throw std::runtime_error("Cannot perform pop on empty heap!");
            return;
        }
        std::swap(v[1], v[dim--]);
        v[dim + 1] = 0;
        int t = 1;
        while(t <= (dim >> 1) && !(v[t] >= v[t << 1] && v[t] >= v[t << 1 | 1])){
            int newT = (t << 1);
            if(v[newT + 1] > v[newT]){
                ++newT;
            }
            std::swap(v[t], v[newT]);
            t = newT;
        }
    }
};

std::ifstream fin("heap.in");
std::ofstream fout("heap.out");

int m;
int type, x;
Heap H;

int main(){
    fin >> m;

    for(;m--;){
        fin >> type;
        if(type == 1){
            fin >> x;
            H.insert(x);
        }
        else{
            int t = H.top();
            H.pop();
            fout << t << '\n';
        }
    }
}