#include <iostream>

template <typename T>
class Deque{
private:
    static constexpr int max_capacity = 1 << 20;
    int head, tail, sz;
    T d[max_capacity];

public:
    Deque() : head(0), tail(0), sz(0) {}

    void push_back(T x){
        if(sz == max_capacity){
            std::cout << "Deque is full!\n";
            return;
        }
        d[tail] = x;
        tail = (tail + 1) % max_capacity;
        ++sz;
    }

    void pop_back(){
        if(sz == 0){
            std::cout << "Deque is empty!\n";
            return;
        }
        tail = (tail - 1 + max_capacity) % max_capacity;
        --sz;
    }

    void push_front(T x){
        if(sz == max_capacity){
            std::cout << "Deque is full!\n";
            return;
        }
        head = (head - 1 + max_capacity) % max_capacity;
        d[head] = x;
        ++sz;
    }

    void pop_front(){
        if(sz == 0){
            std::cout << "Deque is empty!\n";
            return;
        }
        head = (head + 1) % max_capacity;
        --sz;
    }

    T element_at_index(int index){
        if(index < 0 || index >= sz){
            std::cout << "Index out of bounds!\n";
            return T{};
        }
        return d[(head + index) % max_capacity];
    }
};