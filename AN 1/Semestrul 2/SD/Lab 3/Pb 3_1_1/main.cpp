#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

class HashTable{
private:
    int hashSize;
    int count;
    std::vector<std::list<int> > H;

    void resize(){
        hashSize <<= 1;
        std::vector<std::list<int> > oldH = H;
        H.clear();
        H.resize(hashSize);
        for(auto& bucket : oldH){
            for(int x : bucket){
                H[x % hashSize].push_back(x);
            }
        }
    }

public:
    HashTable() : hashSize(666013), count(0), H(std::vector<std::list<int> >(666013)){}

    void insert(int x){
        int index = x % hashSize;

        for(int el : H[index]){
            if(el == x){
                return;
            }
        }

        H[x % hashSize].push_back(x);
        ++count;
        if(count * 10 > hashSize * 7){
            resize();
        }
    }

    bool exists(int x){
        int index = x % hashSize;
        std::list<int>::iterator it = std::find(H[index].begin(), H[index].end(), x);
        if(it != H[index].end()){
            return true;
        }

        return false;
    }

    void erase(int x){
        int index = x % hashSize;
        std::list<int>::iterator it = std::find(H[index].begin(), H[index].end(), x);
        
        if(it != H[index].end()){
            H[index].erase(it);
            --count;
        }
    }

    ~HashTable() = default;
};