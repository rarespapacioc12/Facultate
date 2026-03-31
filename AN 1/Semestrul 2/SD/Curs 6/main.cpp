// Heaps
// Structura de date
// adaugam elemente -> O(1)
// minimul in O(1)
// extragerea minimului -> O(n)

#include <iostream>
#include <vector>
#include <stdexcept>

class Heap{
    std::vector<int> H;
    int size;
public:
    Heap() : H({0}), size(0) {}
    Heap(int x) : H({0, x}), size(1) {}
    Heap(std::vector<int> newH) : H(newH), size(newH.size() - 1) {}
    Heap(const Heap& other) : H(other.H), size(other.H.size() - 1) {}

    void insert(int val){
        H.push_back(val);
        ++size;
        int t = size;
        while(H[t] < H[t >> 1]){
            std::swap(H[t], H[t >> 1]);
            t >>= 1;
        }
    }

    int get_min(){
        if(size == 0){
            throw std::runtime_error("Empty heap!\n");
            return -1;
        }
        return H[1];
    }

    void pop_min(){
        H[1] = H.back();
        --size;
        H.pop_back();
        int t = 1;
        while((t << 1) < size && (H[t] > H[t << 1] || H[t] > H[t << 1 | 1])){
            if(H[t] > H[t << 1] && H[t] > H[t << 1 | 1]){
                if(H[t << 1] < H[t << 1 | 1]){
                    std::swap(H[t], H[t << 1]);
                    t <<= 1;
                }
                else{
                    std::swap(H[t], H[t << 1 | 1]);
                    t = (t << 1 | 1);
                }
            }
            else if(H[t] > H[t << 1]){
                std::swap(H[t], H[t << 1]);
                t <<= 1;
            }
            else if(H[t] > H[t << 1 | 1]){
                std::swap(H[t], H[t << 1 | 1]);
                t = (t << 1 | 1);
            }
        }
    }

    ~Heap() = default;
};