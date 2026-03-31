#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

class HashTable{
private:
    int hashSize;
    int count;
    std::vector<std::list<std::string> > H;

    int hashFunction(const std::string& s, int modulo){
        int value = 0, n = s.length();
        
        for(int i = 0; i < n; ++i){
            value = (value * 31 + (s[i] - 'a')) % modulo;
        }

        return value;
    }

    void resize(){
        hashSize <<= 1;
        std::vector<std::list<std::string> > oldH = H;
        H.clear();
        H.resize(hashSize);
        for(auto& bucket : oldH){
            for(std::string x : bucket){
                H[hashFunction(x, hashSize)].push_back(x);
            }
        }
    }

public:
    HashTable() : hashSize(666013), count(0), H(std::vector<std::list<std::string> >(666013)){}

    void insert(std::string x){
        int index = hashFunction(x, hashSize);

        for(std::string el : H[index]){
            if(el == x){
                return;
            }
        }

        H[index].push_back(x);
        ++count;
        if(count * 10 > hashSize * 7){
            resize();
        }
    }

    bool exists(std::string x){
        int index = hashFunction(x, hashSize);
        std::list<std::string>::iterator it = std::find(H[index].begin(), H[index].end(), x);
        if(it != H[index].end()){
            return true;
        }

        return false;
    }

    void erase(std::string x){
        int index = hashFunction(x, hashSize);
        std::list<std::string>::iterator it = std::find(H[index].begin(), H[index].end(), x);
        
        if(it != H[index].end()){
            H[index].erase(it);
            --count;
        }
    }

    ~HashTable() = default;
};