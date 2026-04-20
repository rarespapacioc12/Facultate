#include <iostream>
#include <vector>

struct HashNode{
    int value;
    bool is_tombstone;

    HashNode() : value(-1), is_tombstone(false) {}
    HashNode(int value) : value(value), is_tombstone(false) {}
    ~HashNode() = default;
};

class HashTable{
private:
    int hashSize;
    int count;
    std::vector<HashNode> H;

    void resize(){
        hashSize <<= 1;
        std::vector<HashNode> oldH = H;
        H.clear();
        H.resize(hashSize);

        for(HashNode& hashNode : oldH){
            if(hashNode.value != -1 && !hashNode.is_tombstone){
                int index = hashNode.value % hashSize;

                while(H[index].value != -1 && !H[index].is_tombstone){
                    if(H[index].value == hashNode.value){
                        continue;
                    }
                    ++index;
                    if(index >= hashSize){
                        index -= hashSize;
                    }
                }

                H[index] = HashNode(hashNode.value);
            }
        }
    }

public:
    HashTable() : hashSize(666013), count(0), H(std::vector<HashNode>(666013)){}

    void insert(int x){
        int index = x % hashSize;

        while(H[index].value != -1 && !H[index].is_tombstone){
            if(H[index].value == x){
                return;
            }
            ++index;
            if(index >= hashSize){
                index -= hashSize;
            }
        }

        H[index] = HashNode(x);
        ++count;

        /* aici l-am pus pe gemini sa imi demonstreze matematic si on average 
        cu load factor <= 0.5 o operatie face 1.5 checkuri la succes si 2.5 la failure, ceea ce ramane O(1) cu constanta mica
        la load factor <= 0.75 o operatie face 2.5 checkuri la succes si 8.5 la failure, ceea ce e o constanta destul de mare
        */
        if(2 * count >= hashSize){ 
            resize();
        }
    }

    bool exists(int x){
        int index = x % hashSize;

        while(H[index].value != -1 && !H[index].is_tombstone){
            if(H[index].value == x){
                return true;
            }
            ++index;
            if(index >= hashSize){
                index -= hashSize;
            }
        }

        return false;
    }

    void erase(int x){
        int index = x % hashSize;
        
        while(H[index].value != -1 && !H[index].is_tombstone){
            if(H[index].value == x){
                H[index].is_tombstone = true;
                return;
            }
            ++index;
            if(index >= hashSize){
                index -= hashSize;
            }
        }
    }

    ~HashTable() = default;
};